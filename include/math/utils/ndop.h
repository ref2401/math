#ifndef MATH_NDOP_H_
#define MATH_NDOP_H_

#include <algorithm>
#include <array>
#include <limits>
#include <numeric>
#include <numbers>
#include <functional>
#include <optional>
#include <vector>

#include "math/math.h"

namespace math::utils {

struct DOP14_Traits
{
    constexpr static size_t get_num_axises() noexcept { return std::size(axises); }
    constexpr static size_t get_num_planes() noexcept { return get_num_axises() * 2; }

    constexpr size_t get_inverse_plane_index(size_t index) const noexcept {
        assert(index < get_num_planes());
        return index >= get_num_axises() ? index - get_num_axises() : index + get_num_axises();
    }

    constexpr static math::float3 get_axis(size_t index) noexcept {
        assert(index < axises.size());
        return axises[index];
    }

    constexpr static math::float3 get_plane_normal(size_t index) noexcept {
        assert(index < get_num_planes());
        return index >= get_num_axises() ? -axises[index - get_num_axises()] : axises[index];
     }

private:
    constexpr static auto sqrt3 = std::numbers::inv_sqrt3_v<float>;
    constexpr static std::array<math::float3, 7> axises {
        math::float3{1.0f, 0.0f, 0.0f},
        math::float3{0.0f, 1.0f, 0.0f},
        math::float3{0.0f, 0.0f, 1.0f},
        math::float3{sqrt3, sqrt3, sqrt3},
        math::float3{sqrt3, sqrt3, -sqrt3},
        math::float3{sqrt3, -sqrt3, sqrt3},
        math::float3{-sqrt3, sqrt3, sqrt3},
    };

    //static_assert(math::approx_equal(math::len_squared(axises[i]), 1.0f));
};

//template <auto Traits>
class DOP : DOP14_Traits {
   public:
    constexpr explicit DOP() noexcept = default;

    template <typename Iterator, typename UnaryFn>
    static DOP compute(
        Iterator vertices_begin, Iterator vertices_end, UnaryFn&& fn_get_position = std::identity{}) noexcept;

    std::vector<math::float3> get_points() const noexcept;
    constexpr std::optional<math::float3> get_center() const noexcept;
    constexpr bool is_empty() const noexcept;
    constexpr math::float3 get_size() const noexcept;

    constexpr DOP transformed(const math::float4x4& transform) const noexcept;
    constexpr DOP unite_with(const DOP& rhv) const noexcept;
    constexpr DOP unite_with(const math::float3& point) const noexcept;

    constexpr void expand (const math::float3& point) noexcept;
    
    constexpr bool contains(const math::float3& point) const noexcept;

   private:
    std::array<float, get_num_planes()> distances_ 
    {
        [](){
            std::array<float, get_num_planes()> result;
            std::fill(std::begin(result), std::end(result), std::numeric_limits<float>::lowest());
            return result;
        }()
    };
};

constexpr std::optional<math::float3> DOP::get_center() const noexcept {
    return is_empty() ? std::nullopt : std::optional{math::float3{std::midpoint(distances_[0], -distances_[get_inverse_plane_index(0)]),
                                                      std::midpoint(distances_[1], -distances_[get_inverse_plane_index(1)]),
                                                      std::midpoint(distances_[2], -distances_[get_inverse_plane_index(2)]),
    }};
}

constexpr bool DOP::is_empty() const noexcept { 
    return std::any_of(std::begin(distances_), std::end(distances_), [](const auto& d) { return d <= std::numeric_limits<float>::lowest(); });
}

constexpr math::float3 DOP::get_size() const noexcept {
    return is_empty() ? math::float3{} : math::float3{distances_[0] + distances_[get_inverse_plane_index(0)], distances_[1] + distances_[get_inverse_plane_index(1)], distances_[2] + distances_[get_inverse_plane_index(2)]} ;
}

template <typename Iterator, typename UnaryFn>
DOP DOP::compute(Iterator vertices_begin, Iterator vertices_end, UnaryFn&& fn_get_position) noexcept {
    return std::accumulate(vertices_begin, vertices_end, DOP{}, [fn_get_position = std::forward<UnaryFn>(fn_get_position)](DOP bounds, const auto& element) {
        const auto vertex = fn_get_position(element);
        return bounds.unite_with(vertex);
    });
}

constexpr DOP DOP::transformed(const math::float4x4& transform) const noexcept {
    auto&& points = get_points();
    return compute(points.begin(), points.end(), [&transform](const auto& pos) {
        const auto transformed_position = math::mul(transform, pos);
        return xyz(transformed_position) / transformed_position.w;
     });
}

constexpr DOP DOP::unite_with(const DOP& rhv) const noexcept {
    DOP result = *this;
    for (size_t i = 0; i < get_num_planes(); ++i) {
        result.distances_[i] = std::max(distances_[i], rhv.distances_[i]);
    }
    return result;
}

constexpr DOP DOP::unite_with(const math::float3& point) const noexcept {
    DOP result = *this;
    result.expand(point);
    return result;
}

constexpr void DOP::expand(const math::float3& point) noexcept {
    for (size_t i = 0; i < get_num_planes(); ++i) {
        const auto dot = math::dot(point, get_plane_normal(i));
        distances_[i] = std::max(distances_[i], dot);
    }
}

constexpr bool DOP::contains(const math::float3& point) const noexcept {
    for (size_t i = 0; i < get_num_planes(); ++i) {
        const auto dot = math::dot(point, get_plane_normal(i));
        if ( dot > distances_[i] + 1e-7) {
            return false;
        }
    }

    return true;
}

inline std::vector<math::float3> DOP::get_points() const noexcept {
    struct AdjacencyInfo {
        size_t i, j, k;
        math::float3x3 planes;
        float inv_determinant;

        auto compute_planes_intersection_point (const DOP& self) const noexcept {
            const math::float3 distances {self.distances_[i], self.distances_[j], self.distances_[k]};
            const auto substitute_row = [this, distances ](int i){
                auto m = planes;
                switch (i){
                case 0:
                    std::tie(m.m00, m.m10, m.m20) = std::tuple{distances.x, distances.y, distances.z}; break;
                case 1:
                    std::tie(m.m01, m.m11, m.m21) = std::tuple{distances.x, distances.y, distances.z}; break;
                case 2:
                    std::tie(m.m02, m.m12, m.m22) = std::tuple{distances.x, distances.y, distances.z}; break;
                }

                return math::det(m);
            };

            return math::float3{substitute_row(0) * inv_determinant, substitute_row(1) * inv_determinant, substitute_row(2) * inv_determinant};
        };
    };
    
    // precalculations, done once per traits type
    static const auto planes_adjacency = [](){
        std::vector<AdjacencyInfo> result;

        for (size_t i = 0; i < get_num_planes(); ++i) {
            for (size_t j = i + 1; j < get_num_planes(); ++j ) {
                for (size_t k = j + 1; k < get_num_planes(); ++k) {        
                    const auto i_normal = get_plane_normal(i);
                    const auto j_normal = get_plane_normal(j);
                    const auto k_normal = get_plane_normal(k);

                    if (dot(i_normal, j_normal) < 0.0f || dot(i_normal, k_normal) < 0.0f || dot(j_normal, k_normal) < 0.0f) {
                        continue;
                    }

                    const math::float3x3 planes{i_normal.x, i_normal.y, i_normal.z, j_normal.x, j_normal.y, j_normal.z, k_normal.x, k_normal.y, k_normal.z};
                    auto d = det(planes);
                    if (math::approx_equal(d, 0.0f)) {
                        continue;
                    }

                    result.push_back({i, j, k, planes, 1.0f / d});
                }
            }
        }
        
        return result;
    }();


    std::vector<math::float3> result;
    result.reserve(planes_adjacency.size());

    for (const auto adjacency : planes_adjacency) {
        const auto point = adjacency.compute_planes_intersection_point(*this);
        if (!contains(point)) {
            continue;
        }
        
        result.push_back(point);
    }

    return result;
}

}

#endif

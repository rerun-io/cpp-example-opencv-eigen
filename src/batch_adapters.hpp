#pragma once

#include <rerun.hpp>

// Adapters so we can log eigen vectors as rerun positions:
template <>
struct rerun::ComponentBatchAdapter<rerun::Position3D, std::vector<Eigen::Vector3f>> {
    ComponentBatch<rerun::Position3D> operator()(const std::vector<Eigen::Vector3f>& container) {
        return ComponentBatch<rerun::Position3D>::borrow(container.data(), container.size());
    }

    ComponentBatch<rerun::Position3D> operator()(std::vector<Eigen::Vector3f>&& container) {
        std::vector<rerun::Position3D> positions(container.size());
        memcpy(positions.data(), container.data(), container.size() * sizeof(Eigen::Vector3f));
        return ComponentBatch<rerun::Position3D>::take_ownership(std::move(positions));
    }
};

// Adapters so we can log an eigen matrix as rerun positions:
template <>
struct rerun::ComponentBatchAdapter<rerun::Position3D, Eigen::Matrix3Xf> {
    ComponentBatch<rerun::Position3D> operator()(const Eigen::Matrix3Xf& matrix) {
        // Sanity check that this is binary compatible.
        static_assert(
            sizeof(rerun::Position3D) ==
            sizeof(Eigen::Matrix3Xf::Scalar) * Eigen::Matrix3Xf::RowsAtCompileTime
        );
        static_assert(alignof(rerun::Position3D) <= alignof(Eigen::Matrix3Xf::Scalar));
        return ComponentBatch<rerun::Position3D>::borrow(
            // Cast to void because otherwise Rerun will try to do above sanity checks with the wrong type (scalar).
            reinterpret_cast<const void*>(matrix.data()),
            matrix.cols()
        );
    }

    ComponentBatch<rerun::Position3D> operator()(Eigen::Matrix3Xf&& matrix) {
        std::vector<rerun::Position3D> positions(matrix.cols());
        memcpy(positions.data(), matrix.data(), matrix.size() * sizeof(rerun::Position3D));
        return ComponentBatch<rerun::Position3D>::take_ownership(std::move(positions));
    }
};
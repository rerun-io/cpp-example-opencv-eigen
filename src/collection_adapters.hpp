#pragma once

#include <rerun.hpp>

#include <eigen3/Eigen/Core>
#include <opencv2/core.hpp>

// Adapters so we can log eigen vectors as rerun positions:
template <>
struct rerun::CollectionAdapter<rerun::Position3D, std::vector<Eigen::Vector3f>> {
    Collection<rerun::Position3D> operator()(const std::vector<Eigen::Vector3f>& container) {
        return Collection<rerun::Position3D>::borrow(container.data(), container.size());
    }

    Collection<rerun::Position3D> operator()(std::vector<Eigen::Vector3f>&& container) {
        std::vector<rerun::Position3D> positions(container.size());
        memcpy(positions.data(), container.data(), container.size() * sizeof(Eigen::Vector3f));
        return Collection<rerun::Position3D>::take_ownership(std::move(positions));
    }
};

// Adapters so we can log an eigen matrix as rerun positions:
template <>
struct rerun::CollectionAdapter<rerun::Position3D, Eigen::Matrix3Xf> {
    Collection<rerun::Position3D> operator()(const Eigen::Matrix3Xf& matrix) {
        // Sanity check that this is binary compatible.
        static_assert(
            sizeof(rerun::Position3D) ==
            sizeof(Eigen::Matrix3Xf::Scalar) * Eigen::Matrix3Xf::RowsAtCompileTime
        );
        static_assert(alignof(rerun::Position3D) <= alignof(Eigen::Matrix3Xf::Scalar));
        return Collection<rerun::Position3D>::borrow(
            // Cast to void because otherwise Rerun will try to do above sanity checks with the wrong type (scalar).
            reinterpret_cast<const void*>(matrix.data()),
            matrix.cols()
        );
    }

    Collection<rerun::Position3D> operator()(Eigen::Matrix3Xf&& matrix) {
        std::vector<rerun::Position3D> positions(matrix.cols());
        memcpy(positions.data(), matrix.data(), matrix.size() * sizeof(rerun::Position3D));
        return Collection<rerun::Position3D>::take_ownership(std::move(positions));
    }
};

// Adapters so we can borrow an OpenCV image easily into Rerun images without copying:
template <>
struct rerun::CollectionAdapter<uint8_t, cv::Mat> {
    Collection<uint8_t> operator()(const cv::Mat& img) {
        return Collection<uint8_t>::borrow(img.data, img.total() * img.channels());
    }

    Collection<uint8_t> operator()(cv::Mat&& img) {
        std::vector<uint8_t> img_vec(img.total() * img.channels());
        img_vec.assign(img.data, img.data + img.total() * img.channels());
        return Collection<uint8_t>::take_ownership(std::move(img_vec));
    }
};

// Adapter for extracting tensor dimensions from an OpenCV matrix.
template <>
struct rerun::CollectionAdapter<rerun::datatypes::TensorDimension, cv::Mat> {
    Collection<rerun::datatypes::TensorDimension> operator()(const cv::Mat& img) {
        // Only specify the const& operator since there is no way of borrowing the dimensions anyways.
        return {
            static_cast<size_t>(img.rows),
            static_cast<size_t>(img.cols),
            static_cast<size_t>(img.channels()),
        };
    }
};
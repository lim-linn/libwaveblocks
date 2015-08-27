#pragma once

#include <cmath>
#include <iostream>
#include <tuple>
#include <vector>

#include <Eigen/Core>
#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

#include "basic_types.hpp"
#include "hawp.hpp"
#include "basic_types.hpp"

namespace waveblocks {

template<dim_t D, class MultiIndex, class QR>
class HomogeneousInnerProduct
{
public:
    // TODO: make D-dimensional, replace Dynamic
    using CMatrixDD = CMatrix<Eigen::Dynamic, Eigen::Dynamic>;
    using CMatrix1D = CMatrix<1, Eigen::Dynamic>;
    using RMatrix1D = RMatrix<1, Eigen::Dynamic>;
    using NodeMatrix = typename QR::NodeMatrix;
    using WeightVector = typename QR::WeightVector;

    HomogeneousInnerProduct()
    {
    }

    CMatrixDD build_matrix(const HaWp<D, MultiIndex>& packet)
        const
    {
        const dim_t order = QR::order;
        const real_t eps = packet.basis.eps;
        const CMatrix<D,1>& q = complex_t(1, 0) * packet.basis.parameters->q;
        const CMatrix<D,D>& Q = packet.basis.parameters->Q;
        NodeMatrix nodes;
        WeightVector weights;
        std::tie(nodes, weights) = QR::nodes_and_weights();
        const CMatrix1D cnodes = complex_t(1, 0) * nodes;
        const CMatrix1D cweights = complex_t(1, 0) * weights;

        // Compute affine transformation.
        auto Qs = (Q * Q.adjoint()).inverse().sqrt().inverse();

        // Transform nodes.
        CMatrix1D transformed_nodes =
            q.replicate(1, order) + eps * (Qs * cnodes);

        // TODO: Apply operator.
        CMatrix1D values = CMatrix1D::Ones(1, order);

        Eigen::Array<complex_t, 1, Eigen::Dynamic>
            factor = std::pow(eps, D) * cweights.array() * values.array();
        std::cout << "factor: " << factor << std::endl;

        HaWpBasisVector<Eigen::Dynamic> bases = packet.basis.
            at(transformed_nodes).all();
        std::cout << "bases:\n" << bases << std::endl;

        // Build matrix.
        const dim_t N = bases.rows();
        CMatrixDD result = CMatrixDD::Zero(N, N);
        for(dim_t i = 0; i < N; ++i)
        {
            for(dim_t j = 0; j < N; ++j)
            {
                for (size_t k = 0; k < order; ++k)
                {
                    result(i, j) += factor(k) * conj(bases(i, k)) * bases(j, k);
                }
            }
        }

        return result;
    }
};

}

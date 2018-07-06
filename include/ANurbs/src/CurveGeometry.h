#pragma once

#include "CurveGeometryBase.h"

#include <vector>
#include <stdexcept>


namespace ANurbs {

template <typename TScalar, std::size_t TDimension>
class CurveGeometry
: public CurveGeometryBase<TScalar, Point<TScalar, TDimension>>
{
public:
    using CurveGeometryBaseType = CurveGeometryBase<TScalar, Point<TScalar,
        TDimension>>;
    using typename CurveGeometryBaseType::ScalarType;
    using typename CurveGeometryBaseType::VectorType;
    using typename CurveGeometryBaseType::KnotsType;

protected:
    std::vector<VectorType> m_poles;
    std::vector<ScalarType> m_weights;

public:
    CurveGeometry(
        const std::size_t& degree,
        const std::size_t& nbPoles,
        const bool& isRational
    )
    : CurveGeometryBaseType(degree, nbPoles)
    , m_poles(nbPoles)
    , m_weights(isRational ? nbPoles : 0)
    {
    }

    VectorType
    Pole(
        const std::size_t& index
    ) const override
    {
        return m_poles[index];
    }

    void
    SetPole(
        const std::size_t& index,
        const VectorType& value
    ) override
    {
        m_poles[index] = value;
    }

    bool
    IsRational(
    ) const override
    {
        return m_weights.size() > 0;
    }

    ScalarType
    Weight(
        const std::size_t& index
    ) const override
    {
        if (IsRational()) {
            return m_weights[index];
        } else {
            return 1;
        }
    }

    void
    SetWeight(
        const std::size_t& index,
        const ScalarType& value
    ) override
    {
        if (IsRational()) {
            m_weights[index] = value;
        } else {
            throw std::invalid_argument("Geometry is not rational"); 
        }
    }
};

using CurveGeometry1D = CurveGeometry<double, 1>;
using CurveGeometry2D = CurveGeometry<double, 2>;
using CurveGeometry3D = CurveGeometry<double, 3>;

} // namespace ANurbs
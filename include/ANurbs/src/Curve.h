#pragma once

#include "CurveBase.h"
#include "CurveGeometry.h"
#include "Pointer.h"

namespace ANurbs {

template <typename TCurveGeometry>
class Curve
: public CurveBase<typename TCurveGeometry::ScalarType,
    typename TCurveGeometry::VectorType>
{
private:
    using CurveGeometryType = TCurveGeometry;

public:
    using CurveBaseType = CurveBase<typename TCurveGeometry::ScalarType,
        typename TCurveGeometry::VectorType>;

    using CurveType = Curve<TCurveGeometry>;

    using typename CurveBaseType::ScalarType;
    using typename CurveBaseType::VectorType;
    using typename CurveBaseType::IntervalType;

private:
    Pointer<CurveGeometryType> m_curveGeometry;
    IntervalType m_domain;

public:

    Curve(
        Pointer<CurveGeometryType> geometry
    )
    : Curve(geometry, geometry->Domain())
    {
    }

    Curve(
        Pointer<CurveGeometryType> geometry,
        const ScalarType& t0,
        const ScalarType& t1
    )
    : m_curveGeometry(geometry)
    , m_domain(t0, t1)
    {
    }
    
    Curve(
        Pointer<CurveGeometryType> geometry,
        const IntervalType& domain
    )
    : m_curveGeometry(geometry)
    , m_domain(domain)
    {
    }

    Pointer<CurveGeometryType>
    CurveGeometry(
    ) const
    {
        return m_curveGeometry;
    }

    std::size_t
    Degree(
    ) const
    {
        return m_curveGeometry->Degree();
    }

    IntervalType
    Domain(
    ) const override
    {
        return m_domain;
    }

    VectorType
    PointAt(
        const ScalarType& t
    ) const
    {
        return m_curveGeometry->PointAt(t);
    }

    std::vector<VectorType>
    DerivativesAt(
        const ScalarType& t,
        const std::size_t& order
    ) const
    {
        return m_curveGeometry->DerivativesAt(t, order);
    }

    std::vector<IntervalType>
    Spans(
    ) override
    {
        auto knots = CurveGeometry()->Knots();

        std::size_t firstSpan = Knots::UpperSpan(Degree(), knots, Domain().T0());
        std::size_t lastSpan = Knots::LowerSpan(Degree(), knots, Domain().T1());

        std::size_t nbSpans = lastSpan - firstSpan + 1;

        std::vector<IntervalType> result(nbSpans);

        for (std::size_t i = 0; i < nbSpans; i++) {
            ScalarType t0 = CurveGeometry()->Knot(firstSpan + i);
            ScalarType t1 = CurveGeometry()->Knot(firstSpan + i + 1);

            result[i] = IntervalType(t0, t1);
        }

        return result;
    }
};

using Curve1d = Curve<CurveGeometry1D>;
using Curve2d = Curve<CurveGeometry2D>;
using Curve3d = Curve<CurveGeometry3D>;

} // namespace ANurbs
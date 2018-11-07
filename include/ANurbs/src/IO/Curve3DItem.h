#pragma once

#include "Item.h"
#include "../Curve.h"
#include "../CurveGeometry.h"
#include "CurveGeometry3DItem.h"

#include <string>
#include <memory>
#include <map>

namespace ANurbs {
namespace IO {

struct Curve3DItem : public ItemBase<Curve3DItem>
{
    static const std::string&
    Type()
    {
        return "Curve3D";
    }

    std::string m_geometryKey;

    Curve3DItem(
        Model& model,
        const std::string& key,
        const std::string& geometryKey)
    : ItemBase<Curve3DItem>(model, key)
    , m_geometryKey(geometryKey)
    {
    }

    Curve3D
    Curve()
    {
        return Curve3D(Geometry());
    }

    std::shared_ptr<CurveGeometry3D>
    Geometry()
    {
        return m_model.Get<CurveGeometry3DItem>(m_geometryKey).m_geometry;
    }
};

} // namespace IO
} // namespace ANurbs
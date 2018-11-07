#pragma once

#include "Item.h"
#include "../CurveGeometry.h"

#include <string>
#include <memory>
#include <map>

namespace ANurbs {
namespace IO {

struct CurveGeometry3DItem : public ItemBase<CurveGeometry3DItem>
{
    static const std::string&
    Type()
    {
        return "CurveGeometry3D";
    }

    std::shared_ptr<CurveGeometry3D> m_geometry;

    CurveGeometry3DItem(
        Model& model,
        const std::string& key,
        std::shared_ptr<CurveGeometry3D> geometry)
    : ItemBase<CurveGeometry3DItem>(model, key)
    , m_geometry(geometry)
    {
    }
};

} // namespace IO
} // namespace ANurbs
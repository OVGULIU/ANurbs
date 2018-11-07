#include "catch.hpp"

#include <ANurbs/Core>
#include <ANurbs/IO>

using namespace ANurbs;


TEST_CASE( "Test model", "[Model]" ) {
    using namespace ANurbs::IO;

    Model model;

    Pointer<CurveGeometry3D> geometry = New<CurveGeometry3D>(2, 3, false);

    model.Add<CurveGeometry3DItem>("Curve3D<0>.CurveGeometry<0>", geometry);

    model.Add<Curve3DItem>("Curve3D<0>", "Curve3D<0>.CurveGeometry<0>");

    SECTION( "Access data" ) {
        CHECK( model.Get<Curve3DItem>("Curve3D<0>").Geometry()->Degree() == 2 );
        CHECK( model.Get<Curve3DItem>("Curve3D<0>").Curve().Degree() == 2 );
    }
}

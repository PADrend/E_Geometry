/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "ELibGeometry.h"
#include "E_Box.h"
#include "E_Frustum.h"
#include "E_Line3.h"
#include "E_Matrix3x3.h"
#include "E_Matrix4x4.h"
#include "E_Plane.h"
#include "E_PointOctree.h"
#include "E_Quaternion.h"
#include "E_Ray3.h"
#include "E_Rect.h"
#include "E_Segment3.h"
#include "E_Sphere.h"
#include "E_SRT.h"
#include "E_Tetrahedron.h"
#include "E_Triangle.h"
#include "E_Vec2.h"
#include "E_Vec3.h"
#include "E_Vec4.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Definitions.h>
#include <Geometry/Vec3.h>
#include <Geometry/Tools.h>

namespace E_Geometry {

void init(EScript::Namespace * globals) {
	using namespace Geometry;
	
	EScript::Namespace * lib = new EScript::Namespace();
	declareConstant(globals, "Geometry", lib);
	E_Box::init(*lib);
	E_Frustum::init(*lib);
	E_Line3::init(*lib);
	E_Matrix3x3::init(*lib);
	E_Matrix4x4::init(*lib);
	E_Plane::init(*lib);
	E_PointOctree::init(*lib);
	E_Quaternion::init(*lib);
	E_Ray3::init(*lib);
	E_Rect::init(*lib);
	E_Segment3::init(*lib);
	E_Sphere::init(*lib);
	E_SRT::init(*lib);
	E_Tetrahedron::init(*lib);
	E_Triangle::init(*lib);
	E_Vec2::init(*lib);
	E_Vec3::init(*lib);
	E_Vec4::init(*lib);

	declareConstant(lib,"CORNER_xyz", CORNER_xyz);
	declareConstant(lib,"CORNER_Xyz", CORNER_Xyz);
	declareConstant(lib,"CORNER_xYz", CORNER_xYz);
	declareConstant(lib,"CORNER_XYz", CORNER_XYz);
	declareConstant(lib,"CORNER_xyZ", CORNER_xyZ);
	declareConstant(lib,"CORNER_XyZ", CORNER_XyZ);
	declareConstant(lib,"CORNER_xYZ", CORNER_xYZ);
	declareConstant(lib,"CORNER_XYZ", CORNER_XYZ);

	declareConstant(lib,"SIDE_X_NEG", SIDE_X_NEG);
	declareConstant(lib,"SIDE_Y_NEG", SIDE_Y_NEG);
	declareConstant(lib,"SIDE_Z_NEG", SIDE_Z_NEG);
	declareConstant(lib,"SIDE_X_POS", SIDE_X_POS);
	declareConstant(lib,"SIDE_Y_POS", SIDE_Y_POS);
	declareConstant(lib,"SIDE_Z_POS", SIDE_Z_POS);

	//! [ESF] Vec3 getClosestPointOnLineToRay(Vec3 linePos, Vec3 lineDir, Vec3 rayPos, Vec3 rayDir)
	ES_FUNCTION(lib,"getClosestPointOnLineToRay",4,4,{
		const Vec3 & linePos = parameter[0].to<Vec3>(rt);
		const Vec3 & lineDir = parameter[1].to<Vec3>(rt);
		const Vec3 & rayPos = parameter[2].to<Vec3>(rt);
		const Vec3 & rayDir = parameter[3].to<Vec3>(rt);
		return EScript::create(std::move(getClosestPointOnLineToRay(linePos, lineDir, rayPos, rayDir)));
	})

	//! [ESF] Vec3|false rayPlaneIntersection(Vec3 planePos, Vec3 planeNormal, Vec3 rayPos, Vec3 rayDir)
	ES_FUNCTION(lib,"rayPlaneIntersection",4,4,{
		const Vec3 & planePos = parameter[0].to<Vec3>(rt);
		const Vec3 & planeNormal = parameter[1].to<Vec3>(rt);
		const Vec3 & rayPos = parameter[2].to<Vec3>(rt);
		const Vec3 & rayDir = parameter[3].to<Vec3>(rt);
		Vec3 intersection;
		bool result = rayPlaneIntersection(planePos, planeNormal, rayPos, rayDir, intersection);
		if (result) {
			return EScript::create(std::move(intersection));
		} else {
			return EScript::create(false);
		}
	})
	
	//! [ESF] [Number,Number]|false lineSphereIntersections(Line3 line, Sphere sphere)
	ES_FUNCTION(lib,"lineSphereIntersections",2,2,{
		const Line3 line = parameter[0].to<Line3>(rt);
		auto result = lineSphereIntersections(line,parameter[1].to<Sphere_f>(rt));
		if(std::get<0>(result)) {
			EScript::Array* arr = EScript::Array::create();
			arr->pushBack( EScript::create( std::get<1>(result) ) );
			arr->pushBack( EScript::create( std::get<2>(result) ) );
			return arr;
		} else {
			return EScript::create(false);
		}
	})
	

	//! [ESF] Frustum calcEnclosingOrthoFrustum(Box, Matrix4x4)
	ES_FUNCTION(lib, "calcEnclosingOrthoFrustum", 2, 2, {
		const Box & box = parameter[0].to<const Box&>(rt);
		const Matrix4x4f & modelView = parameter[1].to<const Matrix4x4&>(rt);
		return new E_Frustum(calcEnclosingOrthoFrustum(box, modelView));
	})
}

}

/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Triangle.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Triangle.h>
#include <Geometry/Vec3.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Triangle::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Triangle::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Triangle::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] line new Triangle(Vec3 a, Vec3 b, Vec3 c)
	ES_CONSTRUCTOR(typeObject, 3, 3, {
		return new E_Triangle(Triangle<Vec3f>(
								parameter[0].to<Vec3>(rt),
								parameter[1].to<Vec3>(rt),
								parameter[2].to<Vec3>(rt)));
	})

	//! [ESF] Number Triangle.calcArea()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcArea", 0, 0,	thisObj->calcArea())

	//! [ESF] Vec3 Triangle.calcNormal()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcNormal", 0, 0,std::move(thisObj->calcNormal()))

	//! [ESF] Vec3 Triangle.calcBarycentricCoordinates(Vec3 p)
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcBarycentricCoordinates", 1, 1,
			std::move(thisObj->calcBarycentricCoordinates(parameter[0].to<Vec3>(rt))))

	//! [ESF] Array Triangle.closestPoint(Vec3 p)
	ES_MFUNCTION(typeObject,const Triangle<Vec3f>, "closestPoint", 1, 1, {
			const Vec3f & p = parameter[0].to<Vec3>(rt);
			Vec3f barycentric;
			Vec3f result = thisObj->closestPoint(p, barycentric);

			EScript::Array * array = EScript::Array::create();
			array->pushBack(EScript::create(std::move(result)));
			array->pushBack(EScript::create(std::move(barycentric)));
			return array;
	})

	//! [ESF] Number Triangle.distanceSquared(Vec3 p)
	ES_MFUN(typeObject,const Triangle<Vec3f>, "distanceSquared", 1, 1,
			thisObj->distanceSquared(parameter[0].to<Vec3>(rt)))

}

std::string E_Triangle::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

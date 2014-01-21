/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Tetrahedron.h"
#include "E_Plane.h"
#include "E_Triangle.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Tetrahedron.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Tetrahedron::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Tetrahedron::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Tetrahedron::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace Geometry;
	
	//!	[ESMF] line new Tetrahedron(Vec3 a, Vec3 b, Vec3 c, Vec3 d)
	ES_CONSTRUCTOR(typeObject, 4, 4, {
		return new E_Tetrahedron(Tetrahedron<float>(
								parameter[0].to<Vec3>(rt),
								parameter[1].to<Vec3>(rt),
								parameter[2].to<Vec3>(rt),
								parameter[3].to<Vec3>(rt)));
	})

	//! [ESF] Number Triangle.calcVolume()
	ES_MFUN(typeObject,const Tetrahedron<float>, "calcVolume", 0, 0,thisObj->calcVolume())
	
	//! [ESF] Bool Tetrahedron.containsPoint(Vec3 p, Number epsilon)
	ES_MFUN(typeObject,const Tetrahedron<float>, "containsPoint", 2, 2,
			thisObj->containsPoint(parameter[0].to<Vec3>(rt), parameter[1].to<float>(rt)))

	//! [ESF] Number Tetrahedron.distanceSquared(Vec3 p)
	ES_MFUN(typeObject,const Tetrahedron<float>, "distanceSquared", 1, 1,
			thisObj->distanceSquared(parameter[0].to<Vec3>(rt)))

	//! [ESF] Triangle Tetrahedron.getFaceA()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getFaceA", 0, 0, thisObj->getFaceA())

	//! [ESF] Triangle Tetrahedron.getFaceB()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getFaceB", 0, 0, thisObj->getFaceB())

	//! [ESF] Triangle Tetrahedron.getFaceC()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getFaceC", 0, 0, thisObj->getFaceC())

	//! [ESF] Triangle Tetrahedron.getFaceD()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getFaceD", 0, 0, thisObj->getFaceD())

	//! [ESF] Plane Tetrahedron.getPlaneA()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getPlaneA", 0, 0, thisObj->getPlaneA())

	//! [ESF] Plane Tetrahedron.getPlaneB()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getPlaneB", 0, 0, thisObj->getPlaneB())

	//! [ESF] Plane Tetrahedron.getPlaneC()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getPlaneC", 0, 0, thisObj->getPlaneC())

	//! [ESF] Plane Tetrahedron.getPlaneD()
	ES_MFUN(typeObject,const Tetrahedron<float>, "getPlaneD", 0, 0, thisObj->getPlaneD())
}

std::string E_Tetrahedron::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

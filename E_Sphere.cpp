/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Sphere.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Sphere.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Sphere::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Sphere::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Sphere::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace Geometry;
	
	//! [ESMF] Sphere new Sphere([| Vec3 center, Number radius | Sphere source])
	ES_CONSTRUCTOR(typeObject, 0, 2, {
		if(parameter.count() == 1) {
			return new E_Sphere(parameter[0].to<const Sphere_f&>(rt));
		} else if(parameter.count() == 2) {
			return new E_Sphere(Sphere_f(
					parameter[0].to<Vec3>(rt),
					parameter[1].to<float>(rt)));
		} else {
			return new E_Sphere;
		}
	})

	//! @name Information

	//! [ESMF] Vec3 Sphere.getCenter()
	ES_MFUN(typeObject,const Sphere_f, "getCenter", 0, 0,
				std::move(thisObj->getCenter()))

	//! [ESMF] Number Sphere.getRadius()
	ES_MFUN(typeObject,const Sphere_f, "getRadius", 0, 0,
				thisObj->getRadius())

	//! [ESMF] Number Sphere.distance(Vec3)
	ES_MFUN(typeObject,const Sphere_f, "distance", 1, 1,
				thisObj->distance(parameter[0].to<Vec3>(rt)))

	//! [ESMF] Bool Sphere.isOutside(Vec3)
	ES_MFUN(typeObject,const Sphere_f, "isOutside", 1, 1,
				thisObj->isOutside(parameter[0].to<Vec3>(rt)))

	//! [ESMF] Vec3 Sphere.calcCartesianCoordinate(Number, Number)
	ES_MFUN(typeObject,const Sphere_f, "calcCartesianCoordinate", 2, 2,
				std::move(thisObj->calcCartesianCoordinate(parameter[0].to<float>(rt) ,parameter[1].to<float>(rt))))

	//! [ESF] Vec3 Sphere.calcCartesianCoordinateUnitSphere(Number, Number)
	ES_FUN(typeObject, "calcCartesianCoordinateUnitSphere", 2, 2,
				std::move(Sphere_f::calcCartesianCoordinateUnitSphere(parameter[0].to<float>(rt) ,parameter[1].to<float>(rt))))

	//! @name Modification

	//! [ESMF] self Sphere.setCenter(Vec3)
	ES_MFUN(typeObject,Sphere_f, "setCenter", 1, 1,
				(thisObj->setCenter(parameter[0].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self Sphere.setRadius(Vec3)
	ES_MFUN(typeObject,Sphere_f, "setRadius", 1, 1,
				(thisObj->setRadius(parameter[0].to<float>(rt)),thisEObj))
}

std::string E_Sphere::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

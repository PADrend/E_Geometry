/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Line3.h"
#include "E_Ray3.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Line.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Line3::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Line3::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Line3::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] line new Line3([ Vec3 origin,Vec3 direction| Line3 ])
	ES_CONSTRUCTOR(typeObject,0,2,{
		if(parameter.count()==1){
			return new E_Line3(parameter[0].to<const Line3&>(rt));
		}else if(parameter.count()==2){
			return new E_Line3(
					parameter[0].to<Vec3>(rt),
					parameter[1].to<Vec3>(rt));
		}else{
			return new E_Line3;
		}
	})

	//!	[ESMF] Number line3.distance(Vec3)
	ES_MFUN(typeObject,const Line3,"distance",1,1,
				thisObj->distance(parameter[0].to<Vec3>(rt)))

	//!	[ESMF] Vec3 line3.getDirection()
	ES_MFUN(typeObject,const Line3,"getDirection",0,0,
				std::move(thisObj->getDirection()))

	//!	[ESMF] Vec3 line3.getClosestPoint(Vec3)
	ES_MFUN(typeObject,const Line3,"getClosestPoint",1,1,
				std::move(thisObj->getClosestPoint(parameter[0].to<Vec3>(rt))))

	//!	[ESMF] Array Line3.getClosestValues(Line3)
	ES_MFUNCTION(typeObject, const Line3, "getClosestValues", 1, 1, {
		const Line3 & lineA = *thisObj;
		const Line3 & lineB = parameter[0].to<const Line3&>(rt);
		auto parameterPair = lineA.getClosestValues(lineB);
		EScript::Array * array = EScript::Array::create();
		array->pushBack(EScript::create(parameterPair.first));
		array->pushBack(EScript::create(parameterPair.second));
		return array;
	})

	//!	[ESMF] Vec3 line3.getClosestPointToRay(Ray3)
	ES_MFUN(typeObject,const Line3,"getClosestPointToRay",1,1,
				std::move(thisObj->getClosestPointToRay(parameter[0].to<const Ray3&>(rt))))
	
	//!	[ESMF] Vec3 line3.getOrigin()
	ES_MFUN(typeObject,const Line3,"getOrigin",0,0,	std::move(thisObj->getOrigin()))

	//!	[ESMF] Vec3 line3.getPoint(Number)
	ES_MFUN(typeObject,const Line3,"getPoint",1,1,std::move(thisObj->getPoint(parameter[0].to<float>(rt))))

	//!	[ESMF] self line3.normalize()
	ES_MFUN(typeObject,Line3,"normalize",0,0,
				(thisObj->normalize(),thisEObj))

	//!	[ESMF] self line3.setDirection(Vec3)
	ES_MFUN(typeObject,Line3,"setDirection",1,1,
				(thisObj->setDirection(parameter[0].to<Vec3>(rt)),thisEObj))

	//!	[ESMF] self line3.setOrigin(Vec3)
	ES_MFUN(typeObject,Line3,"setOrigin",1,1,
				(thisObj->setOrigin(parameter[0].to<Vec3>(rt)),thisEObj))
}

std::string E_Line3::toString() const {
	std::ostringstream stream;
	stream << getClassName() << "([" << (**this).getOrigin() << "] + [" << (**this).getDirection() << "] * t)";
	return stream.str();
}

}

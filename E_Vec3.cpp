/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>

#include <cstddef>
#include <sstream>
#include <limits>

namespace EScript{
template<> Geometry::Vec3 convertTo<Geometry::Vec3>(Runtime & rt,ObjPtr obj){
	Array * arr = obj.toType<Array>();
	if(arr){
		return Geometry::Vec3( arr->at(0).toDouble(), arr->at(1).toDouble(), arr->at(2).toDouble() );
	}
	return Geometry::Vec3(**assertType<E_Geometry::E_Vec3>(rt,obj));
}
}
namespace E_Geometry {

//! (static)
EScript::Type * E_Vec3::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Vec3::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] Vec3 new Vec3([ x,y,z | Vec3 | Array])
	ES_CONSTRUCTOR(typeObject,0,3,{
		if(parameter.count()==1){
			return EScript::create(parameter[0].to<Vec3>(rt));
		}else if(parameter.count()==3){
			return new E_Vec3(parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt));
		}else {
			if(parameter.count()!=0){
				rt.warn("new Vec3(): Wrong parameter count!");
			}
			return new E_Vec3;
		}
	})

	//!	[ESMF] Vec3 Vec3.*(Number)
	ES_MFUN(typeObject,const Vec3,"*",1,1,		std::move( (*thisObj)*parameter[0].to<float>(rt) ))

	//!	[ESMF] Vec3 -Vec3()
	ES_MFUN(typeObject,const Vec3,"_-_pre",0,0,	std::move(-(*thisObj)))

	//!	[ESMF] Vec3 Vec3.+(Vec3)
	ES_MFUN(typeObject,const Vec3,"+",1,1,		std::move((*thisObj) + (parameter[0].to<Vec3>(rt))))

	//!	[ESMF] Vec3 Vec3.-(Vec3)
	ES_MFUN(typeObject,const Vec3,"-",1,1,		std::move((*thisObj) - (parameter[0].to<Vec3>(rt))))

	//!	[ESMF] Vec3 Vec3./(number)
	ES_MFUN(typeObject,const Vec3,"/",	1,1,	std::move((*thisObj) / parameter[0].to<float>(rt)))

	//!	[ESMF] Vec3 Vec3.+=(Vec3)
	ES_MFUN(typeObject,Vec3,"+=",1,1,			((*thisObj) +=  (parameter[0].to<Vec3>(rt)),thisEObj))

	//!	[ESMF] Vec3 Vec3.-=(Vec3)
	ES_MFUN(typeObject,Vec3,"-=",1,1,			((*thisObj) -=  (parameter[0].to<Vec3>(rt)),thisEObj))

	//!	[ESMF] Vec3 Vec3.*=(Number)
	ES_MFUN(typeObject,Vec3,"*=",1,1,			((*thisObj) *=  parameter[0].to<float>(rt),thisEObj))

	//!	[ESMF] Vec3 Vec3./=(Number)
	ES_MFUN(typeObject,Vec3,"/=",1,1,			((*thisObj) /=  parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] Vec3 Vec3.cross(Vec3)
	ES_MFUN(typeObject, const Vec3,"cross", 1, 1, thisObj->cross(parameter[0].to<Vec3>(rt)))

	//!	[ESMF] Number Vec3.distance(Vec3)
	ES_MFUN(typeObject,const Vec3,"distance",1,1,	thisObj->distance(parameter[0].to<Vec3>(rt)))

	//!	[ESMF] Number Vec3.distanceSquared(Vec3)
	ES_MFUN(typeObject, const Vec3,"distanceSquared", 1, 1, thisObj->distanceSquared(parameter[0].to<Vec3>(rt)))

	//!	[ESMF] Number Vec3.dot(Vec3)
	ES_MFUN(typeObject,const Vec3,"dot",	1,1,	thisObj->dot(parameter[0].to<Vec3>(rt)))
	
	//!	[ESMF] Bool Vec3.equals(Vec3, Number epsilon)
	ES_MFUN(typeObject,const Vec3,"equals",1,2,thisObj->equals(parameter[0].to<Vec3>(rt), parameter[1].toFloat(std::numeric_limits<float>::epsilon())))
	
	//!	[ESMF] Vec3 Vec3.getNormalized()
	ES_MFUN(typeObject,const Vec3,"getNormalized",0,0,thisObj->getNormalized())

	//!	[ESMF] Vec3 Vec3.getProjection(Vec3 planeBase,Vec3 planeNormal)
	ES_MFUN(typeObject,const Vec3,"getProjection",2,2,thisObj->getProjection(
								parameter[0].to<Vec3>(rt),parameter[1].to<Vec3>(rt)))

	//!	[ESMF] Number Vec3.getX()
	ES_MFUN(typeObject,const Vec3,"getX",0,0,		thisObj->getX())

	//!	[ESMF] Number Vec3.getY()
	ES_MFUN(typeObject,const Vec3,"getY",0,0,		thisObj->getY())

	//!	[ESMF] Number Vec3.getZ()
	ES_MFUN(typeObject,const Vec3,"getZ",0,0,		thisObj->getZ())

	//!	[ESMF] bool Vec3.isZero()
	ES_MFUN(typeObject,const Vec3,"isZero",0,0,	thisObj->isZero())

	//!	[ESMF] number Vec3.length()
	ES_MFUN(typeObject,const Vec3,"length",0,0,	thisObj->length())

	//!	[ESMF] Number Vec3.lengthSquared()
	ES_MFUN(typeObject, const Vec3, "lengthSquared", 0, 0, thisObj->lengthSquared())

	//!	[ESMF] Number Vec3.maxAbsValue()
	ES_MFUN(typeObject,const Vec3,"maxAbsValue",0,0,thisObj->maxAbsValue())

	//!	[ESMF] thisObj Vec3.normalize()
	ES_MFUN(typeObject,Vec3,"normalize",	0,0,	(thisObj->normalize(),thisEObj))

	//!	[ESMF] caller Vec3.reflect(Vec3)
	ES_MFUN(typeObject,Vec3,"reflect",1,1,			(thisObj->reflect(parameter[0].to<Vec3>(rt)),thisEObj))

	//!	[ESMF] thisObj Vec3.setValue( Number,Number,Number | Array | Vec3)
	ES_MFUNCTION(typeObject,Vec3,"setValue",0,3,{
		if(parameter.count()==1){
			E_Vec3 * v2=parameter[0].toType<E_Vec3>();
			if(v2){
				(*thisObj) = (**v2);
			}else {
				const EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
				thisObj->setValue(a->at(0).toFloat(), a->at(1).toFloat(), a->at(2).toFloat());
			}
		}else {
			assertParamCount(rt,parameter,3,3);
			thisObj->setValue(parameter[0].to<float>(rt),parameter[1].to<float>(rt),parameter[2].to<float>(rt));
		}
		return thisEObj;
	})
	
	//!	[ESMF] thisObj Vec3.setX(Number)
	ES_MFUN(typeObject,Vec3,"setX",1,1,			(thisObj->setX(parameter[0].to<float>(rt)),thisEObj))

	//!	[ESMF] thisObj Vec3.setY(Number)
	ES_MFUN(typeObject,Vec3,"setY",1,1,			(thisObj->setY(parameter[0].to<float>(rt)),thisEObj))

	//!	[ESMF] thisObj Vec3.setZ(Number)
	ES_MFUN(typeObject,Vec3,"setZ",1,1,			(thisObj->setZ(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] Array Vec3.toArray()
	ES_MFUNCTION(typeObject,const Vec3,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		a->pushBack(EScript::create(thisObj->x()));
		a->pushBack(EScript::create(thisObj->y()));
		a->pushBack(EScript::create(thisObj->z()));
		return a;
	})
	
	//! [ESMF] Number|thisObj Vec3.x([value])
	ES_MFUNCTION(typeObject,Vec3,"x",0,1,{
		if(parameter.count()==1){
			thisObj->setX(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getX();
		}
	})

	//! [ESMF] Number|thisObj Vec3.y([value])
	ES_MFUNCTION(typeObject,Vec3,"y",0,1,{
		if(parameter.count()==1){
			thisObj->setY(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getY();
		}
	})

	//! [ESMF] Number|thisObj Vec3.z([value])
	ES_MFUNCTION(typeObject,Vec3,"z",0,1,{
		if(parameter.count()==1){
			thisObj->setZ(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getZ();
		}
	})
}

//---


std::string E_Vec3::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

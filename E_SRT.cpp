/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_SRT.h"
#include "E_Matrix3x3.h"
#include "E_Quaternion.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/SRT.h>
#include <Geometry/Vec3.h>
#include <sstream>
#include <array>

namespace E_Geometry {

//! (static)
EScript::Type * E_SRT::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_SRT::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_SRT::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace Geometry;
	typedef std::array<float,8> arr8_t; // no template inside macro...
	
	//! [ESF] SRT new Geometry.SRT( [SRT] | pos, dir, up[, scale] | srt1, srt2, blend | Array[8] )
	ES_CONSTRUCTOR(typeObject, 0, 4, {
		if(parameter.count() == 0) {
			return new E_SRT;
		} else if(parameter.count() == 1) {
			if(parameter[0].toType<EScript::Array>()) {
				arr8_t arr;
				size_t i=0;
				for(const EScript::ObjPtr obj : **parameter[0].toType<EScript::Array>() )
					arr[i++] = obj.toFloat();
				return EScript::create( SRT(arr) );
			}else{
				return EScript::create(parameter[0].to<const SRT&>(rt));
			}
		} else if(parameter[0].toType<E_SRT>()) {
			assertParamCount(rt, parameter, 3, 3);
			return new E_SRT(	parameter[0].to<const SRT&>(rt),
								parameter[1].to<const SRT&>(rt),
								parameter[2].to<float>(rt));
		} else {
			const Vec3 & pos = parameter[0].to<Vec3>(rt);
			const Vec3 & dir = parameter[1].to<Vec3>(rt);
			const Vec3 & up = parameter[2].to<Vec3>(rt);
			return new E_SRT(pos, dir, up, parameter[3].toFloat(1.0f));
		}
	})
	
	//! [ESMF] Vec3 SRT.applyRotation(Vec3)
	ES_MFUN(typeObject,SRT, "applyRotation", 1, 1, std::move(thisObj->getRotation() * (parameter[0].to<Vec3>(rt))))

	//! [ESMF] Vec3 SRT.getDirVector()
	ES_MFUN(typeObject,SRT, "getDirVector", 0, 0, std::move(thisObj->getDirVector()))
	
	//! [ESMF] Matrix3x3 SRT.getRotation( )
	ES_MFUN(typeObject,const SRT, "getRotation", 0, 0, std::move( thisObj->getRotation()))

	//! [ESMF] Vec3 SRT.getTranslation()
	ES_MFUN(typeObject,SRT, "getTranslation", 0, 0, std::move(thisObj->getTranslation()))

	//! [ESMF] Vec3 SRT.getUpVector()
	ES_MFUN(typeObject,SRT, "getUpVector", 0, 0, std::move(thisObj->getUpVector()))

	//! [ESMF] Number SRT.getScale()
	ES_MFUN(typeObject,SRT, "getScale", 0, 0, thisObj->getScale())

	//! [ESMF] Vec3 SRT.inverse()
	ES_MFUN(typeObject,const SRT, "inverse", 0, 0, std::move(thisObj->inverse()))

	//! [ESMF] self SRT.resetRotation()
	ES_MFUN(typeObject,SRT, "resetRotation", 0, 0, (thisObj->resetRotation(),thisEObj))

	//! [ESMF] self SRT.rotateLocal_deg(Number, Vec3 axis)
	ES_MFUN(typeObject,SRT, "rotateLocal_deg", 2, 2, (thisObj->rotateLocal_deg(
			parameter[0].to<float>(rt),
			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self SRT.rotateLocal_rad(Number, Vec3 axis)
	ES_MFUN(typeObject,SRT, "rotateLocal_rad", 2, 2, (thisObj->rotateLocal_rad(
			parameter[0].to<float>(rt),
			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self SRT.rotateRel_deg(Number, Vec3 axis)
	ES_MFUN(typeObject,SRT, "rotateRel_deg", 2, 2, (thisObj->rotateRel_deg(
			parameter[0].to<float>(rt),
			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self SRT.rotateRel_rad(Number, Vec3 axis)
	ES_MFUN(typeObject,SRT, "rotateRel_rad", 2, 2, (thisObj->rotateRel_rad(
			parameter[0].to<float>(rt),
			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self SRT.scale(Number)
	ES_MFUN(typeObject,SRT, "scale", 1, 1, (thisObj->scale(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self SRT.setRotation( (Vec3 dir, Vec3 up) | Quaternion | Matrix3x3 )
	ES_MFUN(typeObject,SRT, "setRotation", 1, 2, (
		parameter.count() == 2 ?
			thisObj->setRotation(parameter[0].to<Vec3>(rt), parameter[1].to<Vec3>(rt)) :
			(parameter[0].toType<E_Matrix3x3>() ?
					thisObj->setRotation(parameter[0].to<const Matrix3x3&>(rt)) :
					thisObj->setRotation((parameter[0].to<Quaternion&>(rt)).toMatrix()))
		,thisEObj))

	//! [ESMF] self SRT.setScale(Number)
	ES_MFUN(typeObject,SRT, "setScale", 1, 1, (thisObj->setScale(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self SRT.setTranslation(Vec3 pos)
	ES_MFUN(typeObject,SRT, "setTranslation", 1, 1, (thisObj->setTranslation(
		parameter[0].to<Vec3>(rt)),thisEObj))

	//! [ESF] self SRT.setValue( [SRT] | pos, dir, up[, scale] | srt1, srt2, blend )
	ES_MFUNCTION(typeObject, SRT, "setValue", 0, 4, {
		if(parameter.count() == 0) {
			*thisObj = SRT();
		} else if(parameter.count() == 1) {
			if(parameter[0].toType<EScript::Array>()) {
				arr8_t arr;
				size_t i=0;
				for(const EScript::ObjPtr obj : **parameter[0].toType<EScript::Array>() )
					arr[i++] = obj.toFloat();
				*thisObj = SRT(arr);
			}else{
				*thisObj = parameter[0].to<const SRT&>(rt);
			}
		} else if(parameter[0].toType<E_SRT>()) {
			assertParamCount(rt, parameter, 3, 3);
			*thisObj = SRT(	parameter[0].to<const SRT&>(rt),
								parameter[1].to<const SRT&>(rt),
								parameter[2].to<float>(rt));
		} else {
			const Vec3 & pos = parameter[0].to<Vec3>(rt);
			const Vec3 & dir = parameter[1].to<Vec3>(rt);
			const Vec3 & up = parameter[2].to<Vec3>(rt);
			*thisObj = SRT(pos, dir, up, parameter[3].toFloat(1.0f));
		}
		return thisEObj;
	})
	
	//! [ESMF] Array Vec3.toArray()
	ES_MFUNCTION(typeObject,const SRT,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		for(const auto& n : thisObj->toArray())
			a->pushBack(EScript::create(n));
		return a;
	})
	

	//! [ESMF] self SRT.translate(Vec3)
	ES_MFUN(typeObject,SRT, "translate", 1, 1, (thisObj->translate(parameter[0].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self SRT.translateLocal(Vec3)
	ES_MFUN(typeObject,SRT, "translateLocal", 1, 1, (thisObj->translateLocal(parameter[0].to<Vec3>(rt)),thisEObj))

	//! [ESMF] Vec3|SRT SRT.mul(Vec3|SRT)
	ES_MFUNCTION(typeObject,const SRT, "*", 1, 1, {
		E_Vec3 * ev = parameter[0].toType<E_Vec3>();
		if(ev) {
			return EScript::create(std::move(*thisObj * (**ev)));
		} else {
			return EScript::create(std::move(*thisObj * (parameter[0].to<const SRT&>(rt))));
		}
	})

}

std::string E_SRT::toString() const {
	std::ostringstream stream;
	stream << getClassName() << "(s=" << (**this).getScale() << ",r=" << (**this).getRotation() << ",t=" << (**this).getTranslation() << ')';
	return stream.str();
}

}

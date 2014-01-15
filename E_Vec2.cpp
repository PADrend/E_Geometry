/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Vec2.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Vec2.h>
#include <sstream>


namespace EScript{
template<> Geometry::Vec2 convertTo<Geometry::Vec2>(Runtime & rt,ObjPtr obj){
	Array * arr = obj.toType<Array>();
	if(arr){
		return Geometry::Vec2( arr->at(0).toDouble(), arr->at(1).toDouble() );
	}
	return Geometry::Vec2(**assertType<E_Geometry::E_Vec2>(rt,obj));
}
}

namespace E_Geometry {

//! (static)
EScript::Type * E_Vec2::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Vec2::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Vec2::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESMF] Vec2 new Vec2([ x,y | Vec2])
	ES_CONSTRUCTOR(typeObject,0,2, {
		assertParamCount(rt,parameter,0,2);

		if(parameter.count()==1){
			return EScript::create(parameter[0].to<Vec2>(rt));
		}else if(parameter.count()==2){
			return new E_Vec2(Vec2(parameter[0].to<float>(rt),parameter[1].to<float>(rt)));
		}else {
			if(parameter.count()!=0){
				rt.warn("new Vec2(): Wrong parameter count!");
			}
			return new E_Vec2;
		}
	})

	//! [ESMF] E_Vec2 -E_Vec2()
	ES_MFUN(typeObject,Vec2,"_-_pre",0,0, - (*thisObj))

	//! [ESMF] E_Vec2 E_Vec2.+(E_Vec2)
	ES_MFUN(typeObject,Vec2,"+",1,1, (*thisObj) + (parameter[0].to<Vec2>(rt)))

	//! [ESMF] E_Vec2 E_Vec2.-(E_Vec2)
	ES_MFUN(typeObject,Vec2,"-",1,1, (*thisObj) - (parameter[0].to<Vec2>(rt)))

	//! [ESMF] E_Vec2 E_Vec2.*(number)
	ES_MFUN(typeObject,Vec2,"*",1,1,(*thisObj) * parameter[0].to<float>(rt))

	//! [ESMF] E_Vec2 E_Vec2./(number)
	ES_MFUN(typeObject,Vec2,"/",1,1,(*thisObj) / parameter[0].to<float>(rt))

	//! [ESMF] E_Vec2 E_Vec2.+=(E_Vec2)
	ES_MFUN(typeObject,Vec2,"+=",1,1,(*thisObj += (parameter[0].to<Vec2>(rt)),thisEObj))

	//! [ESMF] E_Vec2 E_Vec2.-=(E_Vec2)
	ES_MFUN(typeObject,Vec2,"-=",1,1,(*thisObj -= (parameter[0].to<Vec2>(rt)),thisEObj))

	//! [ESMF] E_Vec2 E_Vec2.*=(Number)
	ES_MFUN(typeObject,Vec2,"*=",1,1,(*thisObj *= parameter[0].to<double>(rt),thisEObj))

	//! [ESMF] E_Vec2 E_Vec2./=(Number)
	ES_MFUN(typeObject,Vec2,"/=",1,1,(*thisObj /= parameter[0].to<double>(rt),thisEObj))

	//! [ESMF] bool E_Vec2.isZero()
	ES_MFUN(typeObject,Vec2,"isZero",0,0,thisObj->isZero())

	//! [ESMF] Number E_Vec2.distance(E_Vec2)
	ES_MFUN(typeObject,Vec2,"distance",1,1,thisObj->distance(parameter[0].to<Vec2>(rt)))

	//! [ESMF] Number E_Vec2.dot(E_Vec2)
	ES_MFUN(typeObject,Vec2,"dot",1,1,thisObj->dot(parameter[0].to<Vec2>(rt)))

	//! [ESMF] self E_Vec2.normalize()
	ES_MFUN(typeObject,Vec2,"normalize",0,0,(thisObj->normalize(),thisEObj))

	//! [ESMF] number E_Vec2.length()
	ES_MFUN(typeObject,Vec2,"length",0,0,thisObj->length())

	//! [ESMF] number E_Vec2.getX()
	ES_MFUN(typeObject,Vec2,"getX",0,0,thisObj->getX())

	//! [ESMF] number E_Vec2.getY()
	ES_MFUN(typeObject,Vec2,"getY",0,0,thisObj->getY())

	//!	[ESMF] self E_Vec2.setValue( Number,Number | Array | Vec2)
	ES_MFUNCTION(typeObject,Vec2,"setValue",0,2,{
		if(parameter.count()==1){
			E_Vec2 * v2=parameter[0].toType<E_Vec2>();
			if(v2){
				*thisObj = (**v2);
			}else {
				const EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
				thisObj->setValue(a->at(0).toFloat(), a->at(1).toFloat());
			}
		}else {
			assertParamCount(rt,parameter,2,2);
			thisObj->setValue(parameter[0].to<float>(rt),parameter[1].to<float>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] self E_Vec2.setX(number)
	ES_MFUN(typeObject,Vec2,"setX",1,1,(thisObj->setX(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Vec2.setY(number)
	ES_MFUN(typeObject,Vec2,"setY",1,1,(thisObj->setY(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] Array E_Vec2.toArray()
	ES_MFUNCTION(typeObject,const Vec2,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		a->pushBack(EScript::create(thisObj->x()));
		a->pushBack(EScript::create(thisObj->y()));
		return a;
	})
	
	//! [ESMF] Number|self E_Vec2.x([value])
	ES_MFUNCTION(typeObject,Vec2,"x",0,1,{
		if(parameter.count()==1){
			thisObj->setX(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getX();
		}
	})

	//! [ESMF] Number|self E_Vec2.y([value])
	ES_MFUNCTION(typeObject,Vec2,"y",0,1,{
		if(parameter.count()==1){
			thisObj->setY(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getY();
		}
	})

}

//---

std::string E_Vec2::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

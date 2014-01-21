/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Vec4.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Vec4.h>
#include <sstream>

namespace EScript{
template<> Geometry::Vec4 convertTo<Geometry::Vec4>(Runtime & rt,ObjPtr obj){
	Array * arr = obj.toType<Array>();
	if(arr){
		return Geometry::Vec4( arr->at(0).toDouble(), arr->at(1).toDouble(), arr->at(2).toDouble(), arr->at(3).toDouble());
	}
	return Geometry::Vec4(**assertType<E_Geometry::E_Vec4>(rt,obj));
}
}

namespace E_Geometry {

//! (static)
EScript::Type * E_Vec4::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Vec4::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Vec4::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESMF] Vec4 new Vec4([ x,y,z,w | Vec4 | Array | Vec3,w])
	ES_CONSTRUCTOR(typeObject,0,4,{

		if(parameter.count()==1){

			E_Vec4 * v2=parameter[0].toType<E_Vec4>();
			if(v2){
				return new E_Vec4(**v2);
			}else {
				const EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
				return new E_Vec4(Vec4(a->at(0).toFloat(), a->at(1).toFloat(), a->at(2).toFloat(), a->at(3).toFloat()));
			}

		}else if(parameter.count()==4){
			return new E_Vec4(Vec4(parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt),parameter[3].to<double>(rt)));
		}else if(parameter.count()==2){
			return new E_Vec4(Vec4(parameter[0].to<Vec3>(rt), parameter[1].to<double>(rt) ));
		}else {
			if(parameter.count()!=0){
				rt.warn("new Vec4: Wrong parameter count!");
			}
			return new E_Vec4;
		}
	})

	//! [ESMF] E_Vec4 -E_Vec4()
	ES_MFUN(typeObject,Vec4,"_-_pre",0,0,-*thisObj)

	//! [ESMF] E_Vec4 E_Vec4.+(E_Vec4)
	ES_MFUN(typeObject,Vec4,"+",1,1,*thisObj + (parameter[0].to<const Vec4&>(rt)))

	//! [ESMF] E_Vec4 E_Vec4.-(E_Vec4)
	ES_MFUN(typeObject,Vec4,"-",1,1,*thisObj - (parameter[0].to<const Vec4&>(rt)))

	//! [ESMF] E_Vec4 E_Vec4.*(number)
	ES_MFUN(typeObject,Vec4,"*",1,1,*thisObj * parameter[0].to<float>(rt))

	//! [ESMF] E_Vec4 E_Vec4./(number)
	ES_MFUN(typeObject,Vec4,"/",1,1,*thisObj / parameter[0].to<float>(rt))

	//! [ESMF] E_Vec4 E_Vec4.+=(E_Vec4)
	ES_MFUN(typeObject,Vec4,"+=",1,1,(*thisObj +=  (parameter[0].to<const Vec4&>(rt)),thisEObj))

	//! [ESMF] E_Vec4 E_Vec4.-=(E_Vec4)
	ES_MFUN(typeObject,Vec4,"-=",1,1,(*thisObj -=  (parameter[0].to<const Vec4&>(rt)),thisEObj))

	//! [ESMF] E_Vec4 E_Vec4.*=(Number)
	ES_MFUN(typeObject,Vec4,"*=",1,1,(*thisObj *=  parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] E_Vec4 E_Vec4./=(Number)
	ES_MFUN(typeObject,Vec4,"/=",1,1,(*thisObj /=  parameter[0].to<float>(rt),thisEObj))


	//! [ESMF] Number E_Vec4.dot(E_Vec4)
	ES_MFUN(typeObject,Vec4,"dot",1,1,thisObj->dot(parameter[0].to<const Vec4&>(rt)))


	//! [ESMF] E_Vec4 E_Vec4.getNormalized()
	ES_MFUN(typeObject,Vec4,"getNormalized",0,0,new E_Vec4(thisObj->getNormalized()))

	//! [ESMF] number E_Vec4.getW()
	ES_MFUN(typeObject,Vec4,"getW",0,0,thisObj->getW())

	//! [ESMF] number E_Vec4.getX()
	ES_MFUN(typeObject,Vec4,"getX",0,0,thisObj->getX())

	//! [ESMF] number E_Vec4.getY()
	ES_MFUN(typeObject,Vec4,"getY",0,0,thisObj->getY())

	//! [ESMF] number E_Vec4.getZ()
	ES_MFUN(typeObject,Vec4,"getZ",0,0,thisObj->getZ())

	//! [ESMF] bool E_Vec4.isZero()
	ES_MFUN(typeObject,Vec4,"isZero",0,0,thisObj->isZero())

	//! [ESMF] number E_Vec4.length()
	ES_MFUN(typeObject,Vec4,"length",0,0,thisObj->length())

	//! [ESMF] self E_Vec4.normalize()
	ES_MFUN(typeObject,Vec4,"normalize",0,0,(thisObj->normalize(),thisEObj))

	//!	[ESMF] self E_Vec4.setValue( Number,Number,Number,Number | Array | Vec4 | Vec3,Number)
	ES_MFUNCTION(typeObject,Vec4,"setValue",0,4,{
		if(parameter.count()==1){
			E_Vec4 * v2=parameter[0].toType<E_Vec4>();
			if(v2){
				*thisObj = (**v2);
			}else {
				const EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
				thisObj->setValue(a->at(0).toFloat(), a->at(1).toFloat(), a->at(2).toFloat(), a->at(3).toFloat());
			}
		}else if(parameter.count()==2){
			*thisObj = Vec4(parameter[0].to<Vec3>(rt), parameter[1].to<double>(rt) );
		}else {
			assertParamCount(rt,parameter,4,4);
			thisObj->setValue(parameter[0].to<float>(rt),parameter[1].to<float>(rt),parameter[2].to<float>(rt),parameter[3].to<float>(rt));
		}
		return thisEObj;
	})
	//! [ESMF] self E_Vec4.setW(Number)
	ES_MFUN(typeObject,Vec4,"setW",1,1,(thisObj->setW(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Vec4.setX(Number)
	ES_MFUN(typeObject,Vec4,"setX",1,1,(thisObj->setX(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Vec4.setY(Number)
	ES_MFUN(typeObject,Vec4,"setY",1,1,(thisObj->setY(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Vec4.setZ(Number)
	ES_MFUN(typeObject,Vec4,"setZ",1,1,(thisObj->setZ(parameter[0].to<float>(rt)),thisEObj))


	//! [ESMF] Array E_Vec4.toArray()
	ES_MFUNCTION(typeObject,const Vec4,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		a->pushBack(EScript::create(thisObj->x()));
		a->pushBack(EScript::create(thisObj->y()));
		a->pushBack(EScript::create(thisObj->z()));
		a->pushBack(EScript::create(thisObj->w()));
		return a;
	})

	//!	[ESMF] Number|self E_Vec4.w([value])
	ES_MFUNCTION(typeObject,Vec4,"w",0,1,{
		if(parameter.count()==1){
			thisObj->setW(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getW();
		}
	})
	
	//! [ESMF] E_Vec3 E_Vec4.xyz()
	ES_MFUN(typeObject,Vec4,"xyz",0,0,std::move(thisObj->xyz()))

	//!	[ESMF] Number|self E_Vec4.x([value])
	ES_MFUNCTION(typeObject,Vec4,"x",0,1,{
		if(parameter.count()==1){
			thisObj->setX(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getX();
		}
	})

	//!	[ESMF] Number|self E_Vec4.y([value])
	ES_MFUNCTION(typeObject,Vec4,"y",0,1,{
		if(parameter.count()==1){
			thisObj->setY(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getY();
		}
	})

	//!	[ESMF] Number|self E_Vec4.z([value])
	ES_MFUNCTION(typeObject,Vec4,"z",0,1,{
		if(parameter.count()==1){
			thisObj->setZ(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getZ();
		}
	})
}

//---

std::string E_Vec4::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

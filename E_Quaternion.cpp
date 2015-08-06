/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>

	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Quaternion.h"
#include "E_Matrix3x3.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Quaternion.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Quaternion::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Quaternion::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Quaternion::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;

	//! [ESMF] Quaternion new Quaternion([ x,y,z,w | Quaternion | Mat3x3|  Array(x,y,z,w) ])
	ES_CONSTRUCTOR(typeObject,0,4,{
		if(parameter.count()==1){
			if(E_Quaternion * v2=parameter[0].toType<E_Quaternion>()){
				return new E_Quaternion( **v2 );
			}else if(E_Matrix3x3 * emat=parameter[0].toType<E_Matrix3x3>()){
				return new E_Quaternion( Quaternion::matrixToQuaternion(**emat) );
			}else {
				const EScript::Array * a = parameter[0].to<EScript::Array*>(rt);
				return new E_Quaternion(a->at(0).toFloat(), a->at(1).toFloat(), a->at(2).toFloat(), a->at(3).toFloat());
			}

		}else if(parameter.count()==4){
			return new E_Quaternion(parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt),parameter[3].to<double>(rt));
		}else {
			if(parameter.count()!=0){
				rt.warn("new Quaternion(): Wrong parameter count!");
			}
			return new E_Quaternion;
		}
	})

	//! [ESMF] self E_Quaternion.makeRotate(deg, (Vec3 axis | x,y,z) )
	ES_MFUN(typeObject,Quaternion,"makeRotate",2,4,(parameter.count() < 4 ?
			thisObj->makeRotate_deg(
				parameter[0].to<float>(rt),parameter[1].to<Vec3>(rt)) :
			thisObj->makeRotate_deg(
				parameter[0].to<float>(rt),parameter[1].to<float>(rt),parameter[2].to<float>(rt),parameter[3].to<float>(rt)),thisEObj))

	//!	[ESMF] E_Quaternion E_Quaternion.*(number)
	ES_MFUN(typeObject,const Quaternion,"*",1,1,*thisObj * parameter[0].to<float>(rt))

	//! [ESMF] E_Quaternion E_Quaternion./(number)
	ES_MFUN(typeObject,const Quaternion,"/",1,1,*thisObj / parameter[0].to<float>(rt))

	//! [ESMF] E_Quaternion E_Quaternion.*=(Number)
	ES_MFUN(typeObject,Quaternion,"*=",1,1,(*thisObj *=  parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] E_Quaternion E_Quaternion./=(Number)
	ES_MFUN(typeObject,Quaternion,"/=",1,1,(*thisObj /=  parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] E_Quaternion E_Quaternion.inverse()
	ES_MFUN(typeObject,Quaternion,"inverse",0,0,new E_Quaternion(thisObj->inverse()))

	//! [ESMF] E_Quaternion E_Quaternion.conjugate()
	ES_MFUN(typeObject,Quaternion,"conjugate",0,0,new E_Quaternion(thisObj->conjugate()))

	//! [ESMF] Number E_Quaternion.dot(Quaternion)
	ES_MFUN(typeObject,const Quaternion,"dot",1,1,thisObj->dot(parameter[0].to<const Quaternion&>(rt)))

	//! [ESMF] Array E_Quaternion.toArray()
	ES_MFUNCTION(typeObject,const Quaternion,"toArray",0,0,{
		EScript::Array* arr = EScript::Array::create();
		arr->pushBack( EScript::create(thisObj->x()) );
		arr->pushBack( EScript::create(thisObj->y()) );
		arr->pushBack( EScript::create(thisObj->z()) );
		arr->pushBack( EScript::create(thisObj->w()) );
		return arr;
	})

	//! [ESMF] E_Matrix3x3 E_Quaternion.toMatrix()
	ES_MFUN(typeObject,const Quaternion,"toMatrix",0,0,std::move(thisObj->toMatrix()))

	//! [ESF] (static) E_Quaternion lerp(Quaternion, Quaternion, float)
	ES_FUN(typeObject,"lerp",3,3,Quaternion::lerp(parameter[0].to<const Quaternion&>(rt),
			parameter[1].to<const Quaternion&>(rt), parameter[2].to<float>(rt)))

	//! [ESF] (static) E_Quaternion slerp(Quaternion, Quaternion, float)
	ES_FUN(typeObject,"slerp",3,3,Quaternion::slerp(parameter[0].to<const Quaternion&>(rt),
			parameter[1].to<const Quaternion&>(rt), parameter[2].to<float>(rt)))

	//! [ESF] (static) E_Quaternion matrixToQuaternion(Matrix3x3)
	ES_FUN(typeObject,"matrixToQuaternion",1,1,new E_Quaternion(Quaternion::matrixToQuaternion(parameter[0].to<const Matrix3x3&>(rt))))

	//! [ESMF] number E_Quaternion.length()
	ES_MFUN(typeObject,const Quaternion,"length",0,0,thisObj->length())

	//! [ESMF] self E_Quaternion.normalize()
	ES_MFUN(typeObject,Quaternion,"normalize",0,0,(thisObj->normalize(),thisEObj))

	//! [ESMF] number E_Quaternion.getX()
	ES_MFUN(typeObject,const Quaternion,"getX",0,0,thisObj->x())

	//! [ESMF] number E_Quaternion.getY()
	ES_MFUN(typeObject,const Quaternion,"getY",0,0,thisObj->y())

	//! [ESMF] number E_Quaternion.getZ()
	ES_MFUN(typeObject,const Quaternion,"getZ",0,0,thisObj->z())

	//! [ESMF] number E_Quaternion.getW()
	ES_MFUN(typeObject,const Quaternion,"getW",0,0,thisObj->w())

	//! [ESMF] self E_Quaternion.setX(Number)
	ES_MFUN(typeObject,Quaternion,"setX",1,1,(thisObj->x()=parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] self E_Quaternion.setY(Number)
	ES_MFUN(typeObject,Quaternion,"setY",1,1,(thisObj->y()=parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] self E_Quaternion.setZ(Number)
	ES_MFUN(typeObject,Quaternion,"setZ",1,1,(thisObj->z()=parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] self E_Quaternion.setW(Number)
	ES_MFUN(typeObject,Quaternion,"setW",1,1,(thisObj->w()=parameter[0].to<float>(rt),thisEObj))

	//! [ESMF] E_Vec3 E_Quaternion.toEuler()
	ES_MFUN(typeObject,const Quaternion,"toEuler",0,0,std::move(thisObj->toEuler()))
	
	//! [ESF] (static) E_Quaternion eulerToQuaternion(Vec3)
	ES_FUN(typeObject,"eulerToQuaternion",1,1,new E_Quaternion(Quaternion::eulerToQuaternion(parameter[0].to<const Vec3&>(rt))))

}

std::string E_Quaternion::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Matrix3x3.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Matrix3x3.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Matrix3x3::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Matrix3x3::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Matrix3x3::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] new Geometry.Matrix3x3([Matrix3x3 | Array | (Matrix3x3, Matrix3x3, Number)])
	ES_CONSTRUCTOR(typeObject,0,3, {
		if(parameter.count() == 1) {
			E_Matrix3x3 * em=parameter[0].toType<E_Matrix3x3>();
			if(em)
				return new E_Matrix3x3(**em);

			EScript::Array * a=parameter[0].toType<EScript::Array>();
			if(!a){
				rt.setException("Matrix3x3: Wrong argument for constructor.");
				return nullptr;
			}
			float f[9];
			for(unsigned int i=0;i<9;i++){
				Object * num=a->get(i);
				if(num){
					f[i]=static_cast<float>(num->toDouble());
				}else{
					f[i]=0;
				}
			}
			return new E_Matrix3x3(f);
		} else
			return parameter.count() == 0 ? new E_Matrix3x3 :
			new E_Matrix3x3(parameter[0].to<const Matrix3x3&>(rt),
			parameter[1].to<const Matrix3x3&>(rt), parameter[2].to<float>(rt));
	})


	//! [ESMF] Matrix3x3 Matrix3x3 + Matrix3x3
	ES_MFUN(typeObject,Matrix3x3, "+", 1, 1, std::move(*thisObj + parameter[0].to<const Matrix3x3&>(rt)))

	//!	[ESMF] Matrix3x3 Matrix3x3 - Matrix3x3
	ES_MFUN(typeObject,Matrix3x3, "-", 1, 1,std::move(*thisObj - parameter[0].to<const Matrix3x3&>(rt)))

	//!	[ESF] (Matrix3x3 | Vec3) Matrix3x3 * (Matrix | Number | Vec3)
	ES_MFUNCTION(typeObject,Matrix3x3,"*",1,1,{
		const Matrix3x3 & m=*thisObj;
		if(parameter[0].toType<E_Matrix3x3>()){
			return new E_Matrix3x3( m*(**parameter[0].toType<E_Matrix3x3>()) );
		}else if(parameter[0].toType<E_Vec3>()){
			return EScript::create(std::move(( m*(**parameter[0].toType<E_Vec3>()) )));
		}else{
			return EScript::create(std::move( m*parameter[0].to<float>(rt) ));
		}
	})

	//! [ESMF] Number Matrix3x3.at(row,column)
	ES_MFUN(typeObject,Matrix3x3, "at", 2, 2, thisObj->at(parameter[0].toInt(), parameter[1].toInt()))

	//! [ESF] Matrix3x3 Matrix3x3.createRotation(Number deg, Vec3 axis)
	ES_FUN(typeObject, "createRotation", 2, 2,
				 std::move((Matrix3x3::createRotation(Angle::deg(parameter[0].to<float>(rt)),parameter[1].to<Vec3>(rt)))))

	//! [ESMF] Number Matrix3x3.det()
	ES_MFUN(typeObject,const Matrix3x3, "det", 0, 0, thisObj->det())

	//! [ESMF] Vec3 Matrix3x3.getCol(column)
	ES_MFUN(typeObject,const Matrix3x3, "getCol", 1, 1, std::move(thisObj->getCol(parameter[0].toInt())))

	//! [ESMF] Matrix3x3 Matrix3x3.getInverse()
	ES_MFUN(typeObject,const Matrix3x3, "getInverse", 0, 0, std::move(thisObj->getInverse()))

	//! [ESMF] Vec3 Matrix3x3.getRow(row)
	ES_MFUN(typeObject,const Matrix3x3, "getRow", 1, 1, std::move(thisObj->getRow(parameter[0].toInt())))

	//! [ESMF] Matrix3x3 Matrix3x3.getTransposed()
	ES_MFUN(typeObject,const Matrix3x3, "getTransposed", 0, 0, std::move(thisObj->getTransposed()))

	//! [ESMF] self Matrix3x3.rotateLocal_deg(Number degrees, Vec3 axis)
	ES_MFUN(typeObject,Matrix3x3, "rotateLocal_deg", 2, 2,
				 (*thisObj = *thisObj * Matrix3x3::createRotation(Angle::deg(parameter[0].to<float>(rt)),
																			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self Matrix3x3.rotateLocal_rad(Number radians, Vec3 axis)
	ES_MFUN(typeObject,Matrix3x3, "rotateLocal_rad", 2, 2,
				 (*thisObj = *thisObj * Matrix3x3::createRotation(Angle::rad(parameter[0].to<float>(rt)), 
																			parameter[1].to<Vec3>(rt)),thisEObj))

	/*!	[ESF] self Matrix3x3.set( [Matrix3x3 | row,column,value | v0,...,v8])	*/
	ES_MFUNCTION(typeObject,Matrix3x3,"set",1,9,{
		if(parameter.count()==1){
			*thisObj =
				parameter[0].to<const Matrix3x3&>(rt);
		}else if(parameter.count()==3){
			thisObj->set(
				parameter[0].toInt(),parameter[1].toInt(),parameter[2].to<float>(rt));
		}else {
			assertParamCount(rt,parameter,9,9);
			thisObj->set(
				parameter[0].to<float>(rt),parameter[1].to<float>(rt),parameter[2].to<float>(rt),
				parameter[3].to<float>(rt),parameter[4].to<float>(rt),parameter[5].to<float>(rt),
				parameter[6].to<float>(rt),parameter[7].to<float>(rt),parameter[8].to<float>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] Matrix3x3 Matrix3x3.setIdentity()
	ES_MFUN(typeObject,Matrix3x3, "setIdentity", 0, 0, (thisObj->setIdentity(),thisEObj))

	//! [ESMF] self Matrix3x3.setRotation(Vec3 dir, Vec3 up)
	ES_MFUN(typeObject,Matrix3x3, "setRotation", 2, 2, (thisObj->setRotation(
			parameter[0].to<Vec3>(rt),
			parameter[1].to<Vec3>(rt)),thisEObj))

	//! [ESMF] Array Matrix3x3.toArray()
	ES_MFUNCTION(typeObject,const Matrix3x3,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		for(unsigned int i=0;i<3;i++)
			for(unsigned int j=0;j<3;j++)
				a->pushBack(EScript::create(thisObj->at(i,j)));
		return a;
	})
}

std::string E_Matrix3x3::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

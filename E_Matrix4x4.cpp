/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Matrix4x4.h"
#include "E_SRT.h"
#include "E_Vec3.h"
#include "E_Vec4.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Matrix4x4.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Matrix4x4::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Matrix4x4::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Matrix4x4::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESMF] new Geometry.Matrix4x4([Matrix4x4 | Array | SRT])
	ES_CONSTRUCTOR(typeObject,0,1,{
		if(parameter.count()==0){
			return new E_Matrix4x4;
		}else{
			E_Matrix4x4 * em=parameter[0].toType<E_Matrix4x4>();
			if(em)
				return new E_Matrix4x4(**em);

			E_SRT * srt = parameter[0].toType<E_SRT>();
			if(srt)
				return new E_Matrix4x4(**srt);

			EScript::Array * a=parameter[0].toType<EScript::Array>();
			if(!a){
				rt.setException("Matrix4x4: Wrong argument for constructor.");
				return nullptr;
			}
			float f[16];
			for(unsigned int i=0;i<16;i++){
				Object * num=a->get(i);
				if(num){
					f[i]=static_cast<float>(num->toDouble());
				}else{
					f[i]=0;
				}
			}
			return new E_Matrix4x4(f);
		}
	})

	//! [ESMF] Vec3|Matrix|SRT Matrix4x4.*(Vec3|Vec4|Matrix|SRT|Number)
	ES_MFUNCTION(typeObject,Matrix4x4,"*",1,1,{
		if(E_Vec3 * evt=parameter[0].toType<E_Vec3>()){
			rt.warn("Matrix4x4.*(Vec3) is deprecated. Use Matrix4x4.transformPosition(...) instead");
			return EScript::create(std::move(thisObj->transformPosition(**evt)));
		}else if(E_Vec4 * evf=parameter[0].toType<E_Vec4>()){
			return EScript::create(std::move(*thisObj * (**evf)));
		}else if(E_Matrix4x4 * em=parameter[0].toType<E_Matrix4x4>()){
			return EScript::create(std::move(*thisObj * (**em)));
		}else if(E_SRT * es=parameter[0].toType<E_SRT>()){
			return EScript::create(std::move(*thisObj * (**es)));
		}else return EScript::create(std::move(*thisObj * parameter[0].to<float>(rt)));
	})

	//! [ESMF] Matrix4x4 Matrix4x4.inverse()
	ES_MFUN(typeObject,Matrix4x4,"inverse",0,0,std::move(thisObj->inverse()))

	 //! [ESMF] Matrix4x4 Matrix4x4.getTransposed()
	ES_MFUN(typeObject,Matrix4x4,"getTransposed",0,0,std::move(thisObj->getTransposed()))

	//! [ESMF] self Matrix4x4.lookAt(E_Vec3 pos,E_Vec3 target,E_Vec3 up)
	ES_MFUN(typeObject,Matrix4x4,"lookAt",3,3,( thisObj->lookAt(
		 parameter[0].to<Vec3>(rt),
		 parameter[1].to<Vec3>(rt),
		 parameter[2].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self Matrix4x4.rotate(deg,x,y,z)
	ES_MFUN(typeObject,Matrix4x4,"rotate",4,4,(thisObj->
			rotate_deg(parameter[0].to<double>(rt),parameter[1].to<double>(rt),
					   parameter[2].to<double>(rt),parameter[3].to<double>(rt)),thisEObj))

	//! [ESMF] self Matrix4x4.rotate_deg(deg,  (x,y,z)| Vec3 )
	ES_MFUNCTION(typeObject,Matrix4x4,"rotate_deg",2,4,{
		if(parameter.count()==2){
			thisObj->rotate_deg(parameter[0].to<double>(rt),parameter[1].to<Geometry::Vec3>(rt));
		}else{
			assertParamCount(rt,parameter.count(),4,4);
			thisObj->rotate_deg(parameter[0].to<double>(rt),parameter[1].to<double>(rt),
					   parameter[2].to<double>(rt),parameter[3].to<double>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] self Matrix4x4.rotate_rad(deg,  (x,y,z)| Vec3 )
	ES_MFUNCTION(typeObject,Matrix4x4,"rotate_rad",2,4,{
		if(parameter.count()==2){
			thisObj->rotate_rad(parameter[0].to<double>(rt),parameter[1].to<Geometry::Vec3>(rt));
		}else{
			assertParamCount(rt,parameter.count(),4,4);
			thisObj->rotate_rad(parameter[0].to<double>(rt),parameter[1].to<double>(rt),
					   parameter[2].to<double>(rt),parameter[3].to<double>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] Matrix4x4 Matrix4x4.scale(x,y,z)
	ES_MFUNCTION(typeObject,Matrix4x4,"scale",3,3,{
		thisObj->scale(
			parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt));
		return thisEObj;
	})

	//! [ESF] Matrix4x4 Matrix4x4.setIdentity()
	ES_MFUNCTION(typeObject,Matrix4x4,"setIdentity",0,0,{
		thisObj->setIdentity();
		return thisEObj;
	})

	//! [ESMF] Vec3 Matrix4x4.transformDirection(E_Vec3|x,y,z)
	ES_MFUNCTION(typeObject,const Matrix4x4,"transformDirection",1,3,{
		if(parameter.count() == 3){
			return EScript::create(thisObj->transformDirection(parameter[0].to<double>(rt),
										parameter[1].to<double>(rt),parameter[2].to<double>(rt)));
		}
		return EScript::create(thisObj->transformDirection(parameter[0].to<Vec3>(rt)));
	})
	
	//! [ESMF] Vec3 Matrix4x4.transformPosition(E_Vec3|x,y,z)
	ES_MFUNCTION(typeObject,const Matrix4x4,"transformPosition",1,3,{
		if(parameter.count() == 3){
			return EScript::create(thisObj->transformPosition(parameter[0].to<double>(rt),
										parameter[1].to<double>(rt),parameter[2].to<double>(rt)));
		}
		return EScript::create(thisObj->transformPosition(parameter[0].to<Vec3>(rt)));
	})

	//! [ESMF] Array Matrix4x4.toArray()
	ES_MFUNCTION(typeObject,Matrix4x4,"toArray",0,0,{
		EScript::Array * a = EScript::Array::create();
		for(unsigned int i=0;i<16;i++)
			a->pushBack(EScript::create((*thisObj)[i]));
		return a;
	})

	//! [ESMF] Bool Matrix4x4.convertsSafelyToSRT()
	ES_MFUN(typeObject,Matrix4x4, "convertsSafelyToSRT", 0, 0, thisObj->convertsSafelyToSRT())

	//! [ESMF] SRT Matrix4x4.toSRT()
	ES_MFUN(typeObject,Matrix4x4,"toSRT",0,0,std::move(thisObj->toSRT()))

	//! [ESMF] SRT Matrix4x4._toSRT()
	ES_MFUN(typeObject,Matrix4x4,"_toSRT",0,0,std::move(thisObj->_toSRT()))

	//! [ESMF] Matrix4x4 Matrix4x4.translate(E_Vec3|x,y,z)
	ES_MFUNCTION(typeObject,Matrix4x4,"translate",1,3,{
		if(parameter.count() == 3){
			thisObj->translate(
			parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt));
		}
		else{
			thisObj->translate(parameter[0].to<Vec3>(rt));
		}
		return thisEObj;
	})

}

std::string E_Matrix4x4::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

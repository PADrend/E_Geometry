/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Plane.h"
#include "E_Line3.h"
#include "E_Ray3.h"
#include "E_Segment3.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Plane.h>
#include <Geometry/Vec3.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Plane::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Plane::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Plane::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESMF] Plane new Plane( [ Vec3 normal,float offset ||  Vec3 pos, Vec3 normal || Vec3,Vec3,Vec3 ])
	ES_CONSTRUCTOR(typeObject,0,3,{
		if(parameter.count()==0){
			return new E_Plane;
		}else if(parameter.count()==2){

			// Vec3 pos, Vec3 normal
			E_Vec3 * eNormal = parameter[1].toType<E_Vec3>();
			if(eNormal){
				return new E_Plane(parameter[0].to<Vec3>(rt),**eNormal);
			}else{ // Vec3 normal, Number distance
				return new E_Plane(parameter[0].to<Vec3>(rt),parameter[1].to<float>(rt));
			}
		}else{ // Vec3,Vec3,Vec3
			assertParamCount(rt,parameter,3,3);
			return new E_Plane(	parameter[0].to<Vec3>(rt),
								parameter[1].to<Vec3>(rt),
								parameter[2].to<Vec3>(rt));
		}
	})

	//! [ESMF] Vec3|false Plane.getIntersection( Line3|Ray3|Segment3 )
	ES_MFUNCTION(typeObject,Plane,"getIntersection",1,1,{
		Vec3 intersection;
		bool doesIntersect;
		if(E_Line3 * eLine = parameter[0].toType<E_Line3>()){
			doesIntersect = thisObj->getIntersection(**eLine,intersection);
		}else if(E_Ray3 * eRay = parameter[0].toType<E_Ray3>()){
			doesIntersect = thisObj->getIntersection(**eRay,intersection);
		}else {
			doesIntersect = thisObj->getIntersection(parameter[0].to<const Segment3&>(rt),intersection);
		}
		if(doesIntersect){
			return EScript::create(std::move(intersection));
		}else{
			return false;
		}
	})

	//! [ESMF] Vec3 Plane.getNormal()
	ES_MFUN(typeObject,Plane,"getNormal",0,0,	std::move(thisObj->getNormal()))

	//! [ESMF] Number Plane.getOffset()
	ES_MFUN(typeObject,Plane,"getOffset",0,0,	thisObj->getOffset())

	//! [ESMF] Vec3 Plane.getProjection(Vec3)
	ES_MFUN(typeObject,Plane,"getProjection",1,1,std::move(thisObj->getProjection(parameter[0].to<Vec3>(rt))))

	//! [ESMF] Bool Plane.isUndefined()
	ES_MFUN(typeObject,Plane,"isUndefined",0,0,	thisObj->isUndefined())

		//! [ESMF] Numer Plane.planeTest(Vec3)
	ES_MFUN(typeObject,Plane,"planeTest",1,1,	thisObj->planeTest(parameter[0].to<Vec3>(rt)))

	//! [ESMF] self Plane.setNormal(Vec3)
	ES_MFUN(typeObject,Plane,"setNormal",1,1,	(thisObj->setNormal(parameter[0].to<Vec3>(rt)),thisEObj))

	//! [ESMF] self Plane.setOffset(Number)
	ES_MFUN(typeObject,Plane,"setOffset",1,1,	(thisObj->setOffset(parameter[0].to<float>(rt)),thisEObj))
	//@}
}

std::string E_Plane::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this).getNormal() << ',' << (**this).getOffset() << ')';
	return stream.str();
}

}

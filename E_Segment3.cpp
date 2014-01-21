/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Segment3.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Line.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Segment3::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Segment3::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Segment3::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] line new Segment3([ Vec3 posA,Vec3 posB| Segment3 ])
	ES_CONSTRUCTOR(typeObject,0,2,{
		if(parameter.count()==1){
			return new E_Segment3(parameter[0].to<const Segment3&>(rt));
		}else if(parameter.count()==2){
			return new E_Segment3(Segment3(
					parameter[0].to<Vec3>(rt),
					parameter[1].to<Vec3>(rt)));
		}else{
			return new E_Segment3;
		}
	})

	//!	[ESMF] Number line3.distance(Vec3)
	ES_MFUN(typeObject,const Segment3,"distance",1,1,
				thisObj->distance(parameter[0].to<Vec3>(rt)))

	//!	[ESMF] Vec3 line3.getDirection()
	ES_MFUN(typeObject,const Segment3,"getDirection",0,0,
				std::move(thisObj->getDirection()))

	//!	[ESMF] Vec3 line3.getClosestPoint(Vec3)
	ES_MFUN(typeObject,const Segment3,"getClosestPoint",1,1,
				std::move(thisObj->getClosestPoint(parameter[0].to<Vec3>(rt))))

	//!	[ESMF] Vec3 line3.getFirstPoint()
	ES_MFUN(typeObject,const Segment3,"getFirstPoint",0,0,
				std::move(thisObj->getFirstPoint()))

	//!	[ESMF] Vec3 line3.getOrigin()
	ES_MFUN(typeObject,const Segment3,"getOrigin",0,0,
				std::move(thisObj->getOrigin()))

	//!	[ESMF] Vec3 line3.getPoint(Number)
	ES_MFUN(typeObject,const Segment3,"getPoint",1,1,
				std::move(thisObj->getPoint(parameter[0].to<float>(rt))))

	//!	[ESMF] Vec3 line3.getSecondPoint()
	ES_MFUN(typeObject,const Segment3,"getSecondPoint",0,0,
				std::move(thisObj->getSecondPoint()))

	//!	[ESMF] Number line3.length()
	ES_MFUN(typeObject,const Segment3,"length",0,0,
				thisObj->length())

	//!	[ESMF] self line3.setFirstPoint(Vec3)
	ES_MFUN(typeObject,Segment3,"setFirstPoint",1,1,
				(thisObj->setFirstPoint(parameter[0].to<Vec3>(rt)),thisEObj))

	//!	[ESMF] self line3.setSecondPoint(Vec3)
	ES_MFUN(typeObject,Segment3,"setSecondPoint",1,1,
				(thisObj->setSecondPoint(parameter[0].to<Vec3>(rt)),thisEObj))
}

std::string E_Segment3::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this).getFirstPoint() << ',' << (**this).getSecondPoint() << ')';
	return stream.str();
}

}

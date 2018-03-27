/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Rect.h"
#include "E_Vec2.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Rect.h>
#include <Geometry/Vec2.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Rect::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Rect::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Rect::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESMF] Rect new Rect( [rect] | [x,y,width,height] )
	ES_CONSTRUCTOR(typeObject,0,4, {
		if(parameter.count()==1){
			return new E_Rect(parameter[0].to<const Rect&>(rt));
		}else if(parameter.count()==4){
			return new E_Rect(parameter[0].to<float>(rt),parameter[1].to<float>(rt),
					parameter[2].to<float>(rt),parameter[3].to<float>(rt));
		}else {
			if(parameter.count()!=0){
				rt.warn("new Rect(): Wrong parameter count!");
			}
			return new E_Rect;
		}
	})

	// information
	
	//! [ESMF] Number Rect.getArea()
	ES_MFUN(typeObject,const Rect,"getArea",0,0,thisObj->getArea())
	
	//! [ESMF] Number Rect.getX()
	ES_MFUN(typeObject,const Rect,"getX",0,0,thisObj->getX())

	//! [ESMF] Number Rect.getMinX()
	ES_MFUN(typeObject,const Rect,"getMinX",0,0,thisObj->getMinX())

	//! [ESMF] Number Rect.getMaxX()
	ES_MFUN(typeObject,const Rect,"getMaxX",0,0,thisObj->getMaxX())

	//! [ESMF] Number Rect.getY()
	ES_MFUN(typeObject,const Rect,"getY",0,0,thisObj->getY())

	//! [ESMF] Number Rect.getMinY()
	ES_MFUN(typeObject,const Rect,"getMinY",0,0,thisObj->getMinY())

	//! [ESMF] Number Rect.getMaxY()
	ES_MFUN(typeObject,const Rect,"getMaxY",0,0,thisObj->getMaxY())

	//! [ESMF] Number Rect.getWidth()
	ES_MFUN(typeObject,const Rect,"getWidth",0,0,thisObj->getWidth())

	//! [ESMF] Number Rect.getHeight()
	ES_MFUN(typeObject,const Rect,"getHeight",0,0,thisObj->getHeight())

	//! [ESMF] Number Rect.getHeight()
	ES_MFUN(typeObject,const Rect,"getCenter",0,0,std::move(thisObj->getCenter()))

	//! [ESMF] Bool Rect.isInvalid()
	ES_MFUN(typeObject,const Rect,"isInvalid",0,0,thisObj->isInvalid())

	//! [ESMF] Bool Rect.isValid()
	ES_MFUN(typeObject,const Rect,"isValid",0,0,thisObj->isValid())

		//! [ESMF] bool Rect.intersects(Rect)
	ES_MFUN(typeObject,Rect,"intersects",1,1,thisObj->intersects(
			parameter[0].to<const Rect&>(rt)))

	//!	[ESMF] bool E_Rect.contains( (x,y)|vec2|E_Rect )
	ES_MFUNCTION(typeObject,const Rect,"contains",1,2, {
		const Rect & r=*thisObj;
		if(parameter.count()>1){
			return r.contains(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else if(E_Rect * er2=parameter[0].toType<E_Rect>()){
			return r.contains(**er2);
		}else{
			return r.contains(parameter[0].to<Vec2>(rt));
		}
	})

	// modification

	//!	[ESMF] self E_Rect.setPosition( (x,y)|vec2 )
	ES_MFUNCTION(typeObject,Rect,"setPosition",1,2, {
		if(parameter.count()>1){
			thisObj->setPosition(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else {
			thisObj->setPosition(parameter[0].to<Vec2>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] self Rect.setX(Number)
	ES_MFUN(typeObject,Rect,"setX",1,1,(thisObj->setX(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Rect.setY(Number)
	ES_MFUN(typeObject,Rect,"setY",1,1,(thisObj->setY(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Rect.setWidth(Number)
	ES_MFUN(typeObject,Rect,"setWidth",1,1,(thisObj->setWidth(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Rect.setHeight(Number)
	ES_MFUN(typeObject,Rect,"setHeight",1,1,(thisObj->setHeight(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self Rect.setSize(Number,EScript::Number)
	ES_MFUN(typeObject,Rect,"setSize",2,2,(thisObj->setSize(parameter[0].to<float>(rt),parameter[1].to<float>(rt)),thisEObj))

	//! [ESMF] self Rect.invalidate()
	ES_MFUN(typeObject,Rect,"invalidate",0,0,(thisObj->invalidate(),thisEObj))

	//!	[ESMF] self E_Rect.moveRel( (x,y)|vec2 )
	ES_MFUNCTION(typeObject,Rect,"moveRel",1,2, {
		if(parameter.count()>1){
			thisObj->moveRel(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else {
			thisObj->moveRel(parameter[0].to<Vec2>(rt));
		}
		return thisEObj;
	})

	//! [ESMF] self Rect.+=(Vec2)
	ES_MFUN(typeObject,Rect,"+=",1,1,(*thisObj += parameter[0].to<Vec2>(rt),thisEObj))

	//! [ESMF] self Rect.-=(Vec2)
	ES_MFUN(typeObject,Rect,"-=",1,1,(*thisObj -= parameter[0].to<Vec2>(rt),thisEObj))

	//!	[ESMF] self E_Rect.changeSize( (x,y)|vec2 )
	ES_MFUNCTION(typeObject,Rect,"changeSize",1,2, {
		if(parameter.count()>1){
			thisObj->changeSize(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else {
			const Vec2 & pos=parameter[0].to<Vec2>(rt);
			thisObj->changeSize(pos);
		}
		return thisEObj;
	})

	//!	[ESMF] self E_Rect.changeSizeCentered( (x,y)|vec2 )
	ES_MFUNCTION(typeObject,Rect,"changeSizeCentered",1,2, {
		if(parameter.count()>1){
			thisObj->changeSizeCentered(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else {
			const Vec2 & pos=parameter[0].to<Vec2>(rt);
			thisObj->changeSizeCentered(pos);
		}
		return thisEObj;
	})

	//!	[ESMF] self E_Rect.include( (x,y)|vec2 )
	ES_MFUNCTION(typeObject,Rect,"include",1,2, {
		if(parameter.count()>1){
			thisObj->include(parameter[0].to<double>(rt),parameter[1].to<double>(rt));
		}else {
			const Vec2 & pos=parameter[0].to<Vec2>(rt);
			thisObj->include(pos);
		}
		return thisEObj;
	})

	//! [ESMF] self Rect.clipBy(Rect)
	ES_MFUN(typeObject,Rect,"clipBy",1,1,(thisObj->clipBy(parameter[0].to<const Rect&>(rt)),thisEObj))



	//!	[ESMF] Number|self E_Rect.x([value])
	ES_MFUNCTION(typeObject,Rect,"x",0,1,{
		if(parameter.count()==1){
			thisObj->setX(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getX();
		}
	})

	//!	[ESMF] Number|self E_Rect.y([value])
	ES_MFUNCTION(typeObject,Rect,"y",0,1,{
		if(parameter.count()==1){
			thisObj->setY(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getY();
		}
	})

	//!	[ESMF] Number|self E_Rect.width([value])
	ES_MFUNCTION(typeObject,Rect,"width",0,1,{
		if(parameter.count()==1){
			thisObj->setWidth(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getWidth();
		}
	})

	//!	[ESMF] Number|self E_Rect.height([value])
	ES_MFUNCTION(typeObject,Rect,"height",0,1,{
		if(parameter.count()==1){
			thisObj->setHeight(parameter[0].to<float>(rt));
			return thisEObj;
		}else{
			return thisObj->getHeight();
		}
	})

	// creation

	//! [ESMF] Rect Rect.+(Vec2)
	ES_MFUN(typeObject,const Rect,"+",1,1,std::move(*thisObj + parameter[0].to<Vec2>(rt)))

	//! [ESMF] Rect Rect.-(Vec2)
	ES_MFUN(typeObject,const Rect,"-",1,1,std::move(*thisObj - parameter[0].to<Vec2>(rt)))

}

//---

std::string E_Rect::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

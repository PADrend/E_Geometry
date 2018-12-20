/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Box.h"
#include "E_Matrix4x4.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Box.h>
#include <Geometry/BoxHelper.h>
#include <Geometry/BoxIntersection.h>
#include <Geometry/Definitions.h>
#include <Geometry/Vec3.h>
#include <cstddef>
#include <deque>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Box::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//! initMembers
void E_Box::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Box::getTypeObject();
	declareConstant(&lib, getClassName(), typeObject);

	using namespace Geometry;

	//! [ESMF] Box new Box([ vec3,width,height,depth | x,y,z,width,height,depth | Box])
	ES_CONSTRUCTOR(typeObject,0,6,{
		E_Vec3 * ev=parameter[0].toType<E_Vec3>();
		if(ev){
			return new E_Box(**ev, parameter[1].toFloat(0),parameter[2].toFloat(0),parameter[3].toFloat(0));
		}else if(parameter.count()==1){
			return new E_Box(parameter[0].to<const Box&>(rt));
		}else if(parameter.count()==6){
			return new E_Box(	Vec3(parameter[0].to<float>(rt), parameter[1].to<float>(rt), parameter[2].to<float>(rt)),
								parameter[3].to<float>(rt), parameter[4].to<float>(rt), parameter[5].to<float>(rt));
		}else {
			if(parameter.count()!=0)
				rt.warn("new Box(): Wrong parameter count!");
			return new E_Box;
		}
	})

	//! [ESMF] bool E_Box.contains( (x,y,z)|vec3|E_Box )
	ES_MFUNCTION(typeObject,Box,"contains",1,3,{
		if(parameter.count()>1){
			return thisObj->contains(parameter[0].to<double>(rt),parameter[1].to<double>(rt),parameter[2].to<double>(rt));
		}
		E_Vec3 * ev3=parameter[0].toType<E_Vec3>();
		if(ev3){
			return thisObj->contains(**ev3);
		}
		E_Box * er2=parameter[0].toType<E_Box>();
		if(er2){
			return thisObj->contains(**er2);
		}
		 rt.warn("E_Box.contains(x): Wrong parameter type x!");
		return false;
	})

	//! [ESMF] number E_Box.getCorner( Number CornerNumber )
	ES_MFUN(typeObject,Box,"getCorner",1,1,	std::move(thisObj->getCorner(static_cast<corner_t>(parameter[0].toInt()))))

	//! [ESMF] Number E_Box.getBoundingSphereRadius()
	ES_MFUN(typeObject,Box, "getBoundingSphereRadius", 0, 0,thisObj->getBoundingSphereRadius())

	//! [ESMF] float E_Box.getDistance( Vec3 )
	ES_MFUN(typeObject,Box,"getDistance",1,1,thisObj->getDistance(parameter[0].to<Vec3>(rt)))

	//! [ESMF] float E_Box.getDistanceSquared( Vec3 )
	ES_MFUN(typeObject,Box,"getDistanceSquared",1,1,thisObj->getDistanceSquared(parameter[0].to<Vec3>(rt)))

	//! [ESMF] number E_Box.getExtentMax( )
	ES_MFUN(typeObject,Box,"getExtentMax",0,0,thisObj->getExtentMax())

	//! [ESMF] number E_Box.getExtentMin( )
	ES_MFUN(typeObject,Box,"getExtentMin",0,0,thisObj->getExtentMin())
		
	//! [ESMF] number E_Box.getDiameter( )
	ES_MFUN(typeObject,Box,"getDiameter",0,0,thisObj->getDiameter())

	//! [ESMF] Vec3 E_Box.getCenter( )
	ES_MFUN(typeObject,Box,"getCenter",0,0,	thisObj->getCenter())

	//! [ESMF] float E_Box.getExtentX( )
	ES_MFUN(typeObject,Box,"getExtentX",0,0,	thisObj->getExtentX())

	//! [ESMF] float E_Box.getExtentY( )
	ES_MFUN(typeObject,Box,"getExtentY",0,0,	thisObj->getExtentY())

	//! [ESMF] float E_Box.getExtentZ( )
	ES_MFUN(typeObject,Box,"getExtentZ",0,0,	thisObj->getExtentZ())

	//! [ESMF] Box E_Box.getIntersection( Box )
	ES_MFUN(typeObject,const Box, "getIntersection", 1, 1,
				 Intersection::getBoxBoxIntersection(*thisObj, parameter[0].to<const Box &>(rt)))
	 
 	//! [ESMF] Vec3 E_Box.getMax( )
 	ES_MFUN(typeObject,Box,"getMax",0,0, thisObj->getMax())
				
	//! [ESMF] float E_Box.getMaxX( )
	ES_MFUN(typeObject,Box,"getMaxX",0,0,	thisObj->getMaxX())

	//! [ESMF] float E_Box.getMaxY( )
	ES_MFUN(typeObject,Box,"getMaxY",0,0,	thisObj->getMaxY())

	//! [ESMF] float E_Box.getMaxZ( )
	ES_MFUN(typeObject,Box,"getMaxZ",0,0,	thisObj->getMaxZ())
	
	//! [ESMF] Vec3 E_Box.getMin( )
	ES_MFUN(typeObject,Box,"getMin",0,0, thisObj->getMin())
	
	//! [ESMF] float E_Box.getMinX( )
	ES_MFUN(typeObject,Box,"getMinX",0,0,	thisObj->getMinX())

	//! [ESMF] float E_Box.getMinY( )
	ES_MFUN(typeObject,Box,"getMinY",0,0,	thisObj->getMinY())

	//! [ESMF] float E_Box.getMinZ( )
	ES_MFUN(typeObject,Box,"getMinZ",0,0,	thisObj->getMinZ())

	//! [ESMF] float E_Box.getVolume( )
	ES_MFUN(typeObject,Box,"getVolume",0,0,	thisObj->getVolume())

	//! [ESMF] self E_Box.include(Box|vec3 )
	ES_MFUNCTION(typeObject,Box,"include",1,1,{
		if(E_Vec3 * ev=parameter[0].toType<E_Vec3>()){
			thisObj->include(**ev);
		}else if(E_Box * eb=parameter[0].toType<E_Box>()){
			thisObj->include(**eb);
		}else{
			rt.warn("Wrong object type:"+parameter[0].toString());
		}
		return thisEObj;
	})

	//! [ESMF] bool E_Box.intersects( E_Box )
	ES_MFUN(typeObject,const Box, "intersects", 1, 1,
				 Intersection::isBoxIntersectingBox(*thisObj, parameter[0].to<const Box &>(rt)))

	//! [ESMF] self E_Box.invalidate( )
	ES_MFUN(typeObject,Box,"invalidate",0,0,	(thisObj->invalidate(),thisEObj))

	//! [ESMF] Bool E_Box.isValid( )
	ES_MFUN(typeObject,Box,"isValid",0,0,	thisObj->isValid())

	//! [ESMF] Bool E_Box.isInvalid( )
	ES_MFUN(typeObject,Box,"isInvalid",0,0,	thisObj->isInvalid())
	
	//! [ESMF] self E_Box.resizeAbs( float x [, float y, float z] )
	ES_MFUN(typeObject,Box,"resizeAbs",1,3,
				 (thisObj->resizeAbs(parameter[0].to<float>(rt), parameter[1].toFloat(parameter[0].to<float>(rt)), parameter[2].toFloat(parameter[0].to<float>(rt))),thisEObj))
	
	//! [ESMF] self E_Box.resizeRel( float x [, float y, float z] )
	ES_MFUN(typeObject,Box,"resizeRel",1,3,
				 (thisObj->resizeRel(parameter[0].to<float>(rt), parameter[1].toFloat(parameter[0].to<float>(rt)), parameter[2].toFloat(parameter[0].to<float>(rt))),thisEObj))

	//! [ESMF] self E_Box.setMaxX( float v )
	ES_MFUN(typeObject,Box,"setMaxX",1,1,
				(thisObj->setMaxX(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Box.setMaxY( float v )
	ES_MFUN(typeObject,Box,"setMaxY",1,1,
				(thisObj->setMaxY(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Box.setMaxZ( float v )
	ES_MFUN(typeObject,Box,"setMaxZ",1,1,
				(thisObj->setMaxZ(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Box.setMinX( float v )
	ES_MFUN(typeObject,Box,"setMinX",1,1,
				(thisObj->setMinX(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Box.setMinY( float v )
	ES_MFUN(typeObject,Box,"setMinY",1,1,
				(thisObj->setMinY(parameter[0].to<float>(rt)),thisEObj))

	//! [ESMF] self E_Box.setMinZ( float v )
	ES_MFUN(typeObject,Box,"setMinZ",1,1,
				(thisObj->setMinZ(parameter[0].to<float>(rt)),thisEObj))


	//! [ESMF] self Box.setValue([ vec3,width,height,depth | x,y,z,width,height,depth | Box])
	ES_MFUNCTION(typeObject,Box,"setValue",0,6,{
		E_Vec3 * ev=parameter[0].toType<E_Vec3>();
		if(ev){
			(*thisObj) = Box(**ev, parameter[1].toFloat(0),parameter[2].toFloat(0),parameter[3].toFloat(0));
		}else if(parameter.count()==1){
			(*thisObj) = parameter[0].to<const Box&>(rt);
		}else if(parameter.count()==6){
			(*thisObj) = Box(	Vec3(parameter[0].to<float>(rt), parameter[1].to<float>(rt), parameter[2].to<float>(rt)),
								parameter[3].to<float>(rt), parameter[4].to<float>(rt), parameter[5].to<float>(rt));
		}else {
			if(parameter.count()!=0)
				rt.warn("Box.setValue(...): Wrong parameter count!");
			(*thisObj) = Box();
		}
		return thisEObj;
	})

	//! [ESMF] self E_Box.splitUp( int partsX, int partsY, int partsZ )
	ES_MFUNCTION(typeObject,const Box, "splitUp", 3, 3, {
		const auto newBoxes = Helper::splitUpBox(*thisObj, 
														   parameter[0].toUInt(), 
														   parameter[1].toUInt(), 
														   parameter[2].toUInt());
		return EScript::Array::create(newBoxes);
	})

	//! [ESMF] self E_Box.transform( E_Matrix4x4 transMat )
	ES_MFUNCTION(typeObject,Box, "transform", 1, 1, {
		*thisObj = Helper::getTransformedBox(*thisObj,parameter[0].to<const Matrix4x4 &>(rt));
		return thisEObj;
	})

	//! [ESMF] self E_Box.translate( E_Vec3  )
	ES_MFUN(typeObject,Box,"translate",1,1,	(thisObj->translate(parameter[0].to<Vec3>(rt)),thisEObj))

	// TODO!!!!

}

std::string E_Box::toString() const {
	std::ostringstream stream;
	stream << getClassName() << "(c=" << (**this).getCenter() <<
		",w=" << (**this).getExtentX() <<
		",h=" << (**this).getExtentY() <<
		",d=" << (**this).getExtentZ() << ')';
	return stream.str();
}

}

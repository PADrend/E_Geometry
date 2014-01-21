/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_PointOctree.h"
#include "E_Box.h"
#include "E_Sphere.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Point.h>
#include <Geometry/PointOctree.h>
#include <deque>

namespace E_Geometry {


typedef std::deque<ObjRefPoint> pointQueue_t;

static EScript::Object * convertToEScriptObject(const ObjRefPoint & point) {
	EScript::ERef<EScript::ExtObject> ePoint = EScript::ExtObject::create();

	static const EScript::StringId posId("pos");
	static const EScript::StringId dataId("data");

	ePoint->setAttribute(posId, EScript::create(std::move(point.getPosition())));
	ePoint->setAttribute(dataId, point.data);
	EScript::initPrintableName(ePoint.get(),"PointOctree::Point");

	return ePoint.detachAndDecrease();
}

static EScript::Array * convertToEScriptArray(const pointQueue_t & points) {
	EScript::Array * array = EScript::Array::create();
	for(const auto & point : points) {
		array->pushBack(convertToEScriptObject(point));
	}
	return array;
}



//! (static)
EScript::Type * E_PointOctree::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_PointOctree::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_PointOctree::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//! [ESF] PointOctree new PointOctree( const Box & boundingBox, float minimumBoxSize, unsigned int maximumPoints )
	ES_CTOR(typeObject,3,3,
			new E_PointOctree(parameter[0].to<const Box&>(rt),parameter[1].to<float>(rt),parameter[2].toUInt()))

	//! [ESMF] self PointOctree.clear()
	ES_MFUN(typeObject,PointOctree_EObj,"clear",0,0,(thisObj->clear(),thisEObj))

	//! [ESMF] Box PointOctree.getBox()
	ES_MFUN(typeObject,const PointOctree_EObj,"getBox",0,0,thisObj->getBox())

	//! [ESMF] self PointOctree.insert(Vec3 pos, Object data)
	ES_MFUN(typeObject,PointOctree_EObj,"insert",2,2,(thisObj->insert(ObjRefPoint(parameter[0].to<Vec3>(rt), parameter[1])),thisEObj))

	//! [ESMF] Array PointOctree.collectPoints()
	ES_MFUNCTION(typeObject,const PointOctree_EObj,"collectPoints",0,0,{
		pointQueue_t points;
		thisObj->collectPoints(points);
		return convertToEScriptArray(points);
	})

	//! [ESMF] Array PointOctree.collectPointsWithinBox(Box)
	ES_MFUNCTION(typeObject,const PointOctree_EObj,"collectPointsWithinBox",1,1,{
		pointQueue_t points;
		thisObj->collectPointsWithinBox(parameter[0].to<const Box&>(rt),points);
		return convertToEScriptArray(points);
	})

	//! [ESMF] Array PointOctree.collectPointsWithinSphere(Sphere)
	ES_MFUNCTION(typeObject,const PointOctree_EObj,"collectPointsWithinSphere",1,1,{
		pointQueue_t points;
		thisObj->collectPointsWithinSphere(parameter[0].to<const Sphere_f&>(rt),points);
		return convertToEScriptArray(points);
	})

	//! [ESMF] Array PointOctree.getClosestPoints(Vec3 center, int count)
	ES_MFUNCTION(typeObject,const PointOctree_EObj,"getClosestPoints",2,2,{
		pointQueue_t points;
		thisObj->getClosestPoints(parameter[0].to<Vec3>(rt),parameter[1].toUInt(),points);
		return convertToEScriptArray(points);
	})
}

}

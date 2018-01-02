/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Frustum.h"
#include "E_Box.h"
#include "E_Matrix4x4.h"
#include "E_Plane.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Frustum.h>

namespace E_Geometry {

//! (static)
EScript::Type * E_Frustum::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Frustum::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Frustum::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	declareConstant(typeObject,"INSIDE", 	static_cast<int>(Frustum::intersection_t::INSIDE));
	declareConstant(typeObject,"INTERSECT", static_cast<int>(Frustum::intersection_t::INTERSECT));
	declareConstant(typeObject,"OUTSIDE", 	static_cast<int>(Frustum::intersection_t::OUTSIDE));

	// information

	//! [ESMF] Frustum new Frustum( [float angle=60,float ratio=1.0,float nearD=0.1,float farD=1000.0] )
	ES_CTOR(typeObject,0,4,
			Frustum(Angle::deg(parameter[0].toFloat(60.0)),
											parameter[1].toFloat(1.0),parameter[2].toFloat(0.1),parameter[3].toFloat(1000.0)))

	//! [ESMF] Vec3 Frustum.getPos()
	ES_MFUN(typeObject,const Frustum,"getPos",0,0,std::move(thisObj->getPos()))

	//! [ESMF] Vec3 Frustum.getDir()
	ES_MFUN(typeObject,const Frustum,"getDir",0,0,std::move(thisObj->getDir()))

	//! [ESMF] Vec3 Frustum.getUp()
	ES_MFUN(typeObject,const Frustum,"getUp",0,0,std::move(thisObj->getUp()))

	//! [ESMF] float Frustum.getLeft()
	ES_MFUN(typeObject,const Frustum,"getLeft",0,0, thisObj->getLeft())

	//! [ESMF] float Frustum.getRight()
	ES_MFUN(typeObject,const Frustum,"getRight",0,0, thisObj->getRight())

	//! [ESMF] float Frustum.getBottom()
	ES_MFUN(typeObject,const Frustum,"getBottom",0,0, thisObj->getBottom())

	//! [ESMF] float Frustum.getTop()
	ES_MFUN(typeObject,const Frustum,"getTop",0,0, thisObj->getTop())

	//! [ESMF] float Frustum.getNear()
	ES_MFUN(typeObject,const Frustum,"getNear",0,0, thisObj->getNear())

	//! [ESMF] float Frustum.getFar()
	ES_MFUN(typeObject,const Frustum,"getFar",0,0, thisObj->getFar())

	//! [ESMF] Plane Frustum.getPlane( int PlaneId )
	ES_MFUN(typeObject,const Frustum,"getPlane",1,1,std::move(thisObj->getPlane(static_cast<Geometry::side_t>(parameter[0].toUInt()))))

	//! [ESMF] Matrix4x4 Frustum.getProjectionMatrix()
	ES_MFUN(typeObject,const Frustum,"getProjectionMatrix",0,0,std::move(thisObj->getProjectionMatrix()))

	//! [ESMF] (INSIDE|INTERSECT|OUTSIDE) Frustum.isBoxInFrustum(Box)
	ES_MFUN(typeObject,const Frustum,"isBoxInFrustum",1,1,
			static_cast<int>(thisObj->isBoxInFrustum( parameter[0].to<const Box&>(rt))))

	//! [ESMF] bool Frustum.pointInFrustum(Vec3)
	ES_MFUN(typeObject,const Frustum,"pointInFrustum",1,1,
			thisObj->pointInFrustum( parameter[0].to<Vec3>(rt) ))

	// modification

	//! [ESMF] self Frustum.setPerspective(float angleDeg, float ratio, float nearD, float farD)
	ES_MFUN(typeObject,Frustum,"setPerspective",4,4,
			(thisObj->setPerspective( Angle::deg(parameter[0].to<float>(rt)), 
										parameter[1].to<float>(rt), parameter[2].to<float>(rt), parameter[3].to<float>(rt)) ,thisEObj))

	//! [ESMF] self Frustum.setFrustum(float left,float right,float bottom,float top,float nearD,float farD)
	ES_MFUN(typeObject,Frustum,"setFrustum",6,6,
			(thisObj->setFrustum( parameter[0].to<float>(rt), parameter[1].to<float>(rt), parameter[2].to<float>(rt),
									parameter[3].to<float>(rt), parameter[4].to<float>(rt), parameter[5].to<float>(rt)) ,thisEObj))

	//! [ESMF] self Frustum.setFrustumFromAngles(float fovLeftDeg,float fovRightDeg,float fovBottomDeg,float fovTopDeg,float nearD,float farD)
	ES_MFUN(typeObject,Frustum,"setFrustumFromAngles",6,6,
			(thisObj->setFrustumFromAngles( Angle::deg(parameter[0].to<float>(rt)), 
											Angle::deg(parameter[1].to<float>(rt)), 
											Angle::deg(parameter[2].to<float>(rt)),
											Angle::deg(parameter[3].to<float>(rt)), 
											parameter[4].to<float>(rt), parameter[5].to<float>(rt)) ,thisEObj))

	//! [ESMF] self Frustum.setOrthogonal(float left,float right,float bottom,float top,float nearD,float farD)
	ES_MFUN(typeObject,Frustum,"setOrthogonal",6,6,
			(thisObj->setOrthogonal( parameter[0].to<float>(rt), parameter[1].to<float>(rt), parameter[2].to<float>(rt),
												parameter[3].to<float>(rt), parameter[4].to<float>(rt), parameter[5].to<float>(rt)) ,thisEObj))


	//! [ESMF] self Frustum.setPosition(Vec3 pos, Vec3 dir, Vec3 up)
	ES_MFUN(typeObject,Frustum,"setPosition",3,3,
			(thisObj->setPosition( 	parameter[0].to<Vec3>(rt),
									parameter[1].to<Vec3>(rt),
									parameter[2].to<Vec3>(rt)),thisEObj))

}

}

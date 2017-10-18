/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#include "E_Triangle.h"
#include "E_Vec3.h"
#include <EScript/Basics.h>
#include <EScript/StdObjects.h>
#include <Geometry/Triangle.h>
#include <Geometry/Vec3.h>
#include <sstream>

namespace E_Geometry {

//! (static)
EScript::Type * E_Triangle::getTypeObject(){
	static EScript::Type * typeObject = new EScript::Type(EScript::Object::getTypeObject()); // ---|> Object
	return typeObject;
}

//!	(static) init members
void E_Triangle::init(EScript::Namespace & lib) {
	EScript::Type * typeObject = E_Triangle::getTypeObject();
	declareConstant(&lib,getClassName(),typeObject);

	using namespace Geometry;
	
	//!	[ESMF] line new Triangle(Vec3 a, Vec3 b, Vec3 c)
	ES_CONSTRUCTOR(typeObject, 3, 3, {
		return new E_Triangle(Triangle<Vec3f>(
								parameter[0].to<Vec3>(rt),
								parameter[1].to<Vec3>(rt),
								parameter[2].to<Vec3>(rt)));
	})

	//! [ESF] Number Triangle.calcArea()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcArea", 0, 0,	thisObj->calcArea())

	//! [ESF] Vec3 Triangle.calcNormal()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcNormal", 0, 0,thisObj->calcNormal())

	//! [ESF] Vec3 Triangle.calcPoint(Number u, Number v)
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcPoint", 2, 2,thisObj->calcPoint(parameter[0].toFloat(),parameter[1].toFloat()))

	//! [ESF] Vec3 Triangle.calcBarycentricCoordinates(Vec3 p)
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcBarycentricCoordinates", 1, 1,
			thisObj->calcBarycentricCoordinates(parameter[0].to<Vec3>(rt)))

	//! [ESF] Array Triangle.closestPoint(Vec3 p)
	ES_MFUNCTION(typeObject,const Triangle<Vec3f>, "closestPoint", 1, 1, {
			const Vec3f & p = parameter[0].to<Vec3>(rt);
			Vec3f barycentric;
			Vec3f result = thisObj->closestPoint(p, barycentric);

			EScript::Array * array = EScript::Array::create();
			array->pushBack(EScript::create(std::move(result)));
			array->pushBack(EScript::create(std::move(barycentric)));
			return array;
	})

	//! [ESF] Vec3 Triangle.calcBarycentricCoordinates()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "calcCircumcenter", 0, 0,
			thisObj->calcCircumcenter())

	//! [ESF] Number Triangle.distanceSquared(Vec3 p)
	ES_MFUN(typeObject,const Triangle<Vec3f>, "distanceSquared", 1, 1,
			thisObj->distanceSquared(parameter[0].to<Vec3>(rt)))


	//! [ESF] Vec3 Triangle.getVertexA()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getVertexA", 0, 0,std::move(thisObj->getVertexA()))
	//! [ESF] Vec3 Triangle.getVertexB()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getVertexB", 0, 0,std::move(thisObj->getVertexB()))
	//! [ESF] Vec3 Triangle.getVertexC()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getVertexC", 0, 0,std::move(thisObj->getVertexC()))

	//! [ESF] Vec3 Triangle.setVertexA()
	ES_MFUN(typeObject,Triangle<Vec3f>, "setVertexA", 1, 1,(thisObj->setVertexA(parameter[0].to<Vec3>(rt)), thisEObj))
	//! [ESF] Vec3 Triangle.setVertexB()
	ES_MFUN(typeObject,Triangle<Vec3f>, "setVertexB", 1, 1,(thisObj->setVertexB(parameter[0].to<Vec3>(rt)), thisEObj))
	//! [ESF] Vec3 Triangle.setVertexC()
	ES_MFUN(typeObject,Triangle<Vec3f>, "setVertexC", 1, 1,(thisObj->setVertexC(parameter[0].to<Vec3>(rt)), thisEObj))

	//! [ESF] Vec3 Triangle.getEdgeAB()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeAB", 0, 0,thisObj->getEdgeAB())	
	//! [ESF] Vec3 Triangle.getEdgeAC()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeAC", 0, 0,thisObj->getEdgeAC())
	//! [ESF] Vec3 Triangle.getEdgeBA()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeBA", 0, 0,thisObj->getEdgeBA())	
	//! [ESF] Vec3 Triangle.getEdgeBC()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeBC", 0, 0,thisObj->getEdgeBC())
	//! [ESF] Vec3 Triangle.getEdgeCA()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeCA", 0, 0,thisObj->getEdgeCA())	
	//! [ESF] Vec3 Triangle.getEdgeCB()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "getEdgeCB", 0, 0,thisObj->getEdgeCB())
	
	//! [ESF] Bool Triangle.isDegenerate()
	ES_MFUN(typeObject,const Triangle<Vec3f>, "isDegenerate", 0, 0,thisObj->isDegenerate())
}

std::string E_Triangle::toString() const {
	std::ostringstream stream;
	stream << getClassName() << '(' << (**this) << ')';
	return stream.str();
}

}

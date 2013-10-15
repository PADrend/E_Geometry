/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EPointOctree_H
#define __EPointOctree_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Point.h>
#include <Geometry/PointOctree.h>
#include <Geometry/Vec3.h>
#include <cstddef>
#include <string>

namespace E_Geometry {

struct ObjRefPoint : public Geometry::Point<Geometry::Vec3f> {
	EScript::ObjRef data;

	ObjRefPoint(const Geometry::Vec3f & pos, const EScript::ObjRef & object) :
			Geometry::Point<Geometry::Vec3f>(pos), data(object) {
	}
};

typedef Geometry::PointOctree<ObjRefPoint> PointOctree_EObj; // Point octree for storing EScript objects.

//! E_PointOctree ---|> ReferenceObject<Geometry::PointOctree<ObjRefPoint> >
class E_PointOctree : public EScript::ReferenceObject<PointOctree_EObj, 
													  EScript::Policies::SameEObjects_ComparePolicy>  {
		ES_PROVIDES_TYPE_NAME(PointOctree)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ... Types>
		explicit E_PointOctree(Types && ... params) :
			ReferenceObject_t(E_PointOctree::getTypeObject(), std::forward<Types>(params) ...) {
		}
		virtual ~E_PointOctree() {
		}
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_PointOctree,				E_Geometry::PointOctree_EObj,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_PointOctree,				E_Geometry::PointOctree_EObj&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_PointOctree,				E_Geometry::PointOctree_EObj*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const E_Geometry::PointOctree_EObj&, 	E_Geometry::E_PointOctree,			new E_Geometry::E_PointOctree(obj))
ES_CONV_OBJ_TO_EOBJ(E_Geometry::PointOctree_EObj&&, 		E_Geometry::E_PointOctree,			new E_Geometry::E_PointOctree(obj))

#endif // __EPointOctree_H

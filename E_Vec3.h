/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EVec3_H
#define __EVec3_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Vec3.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Vec3 ---|> [EScript::ReferenceObject]
 *    				|
 *     				------> Geometry::E_Vec3
 */
class E_Vec3 : public EScript::ReferenceObject<Geometry::Vec3> {
		ES_PROVIDES_TYPE_NAME(Vec3)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Vec3(args&&... params) :
			ReferenceObject_t(E_Vec3::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Vec3() {}

		E_Vec3 * clone() const override		{	return new E_Vec3(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec3,		Geometry::_Vec3<int32_t>, Geometry::_Vec3<int32_t>(	(**eObj).x(), (**eObj).y(), (**eObj).z()))
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec3,		Geometry::Vec3&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec3,		Geometry::Vec3*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Vec3&, 	E_Geometry::E_Vec3,		new E_Geometry::E_Vec3(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Vec3&&, 		E_Geometry::E_Vec3,		new E_Geometry::E_Vec3(obj))

namespace EScript{ // automatic conversion functions
template<> Geometry::Vec3 convertTo<Geometry::Vec3>(Runtime & rt,ObjPtr obj);
}

#endif // __EVec3_H

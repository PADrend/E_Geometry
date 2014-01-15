/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EVec2_H
#define __EVec2_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Vec2.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Vec2 ---|> [EScript::ReferenceObject]
 *     				|
 *     				------> Geometry::Vec2
 */
class E_Vec2 : public EScript::ReferenceObject<Geometry::Vec2> {
		ES_PROVIDES_TYPE_NAME(Vec2)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Vec2(args&&... params) :
			ReferenceObject_t(E_Vec2::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Vec2() {}

		E_Vec2 * clone() const override		{	return new E_Vec2(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec2,		Geometry::_Vec2<int32_t>, Geometry::_Vec2<int32_t>(	(**eObj).x(), (**eObj).y()))
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec2,		Geometry::Vec2&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec2,		Geometry::Vec2*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Vec2&, 	E_Geometry::E_Vec2,		new E_Geometry::E_Vec2(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Vec2&&, 		E_Geometry::E_Vec2,		new E_Geometry::E_Vec2(obj))

namespace EScript{ // automatic conversion functions
template<> Geometry::Vec2 convertTo<Geometry::Vec2>(Runtime & rt,ObjPtr obj);
}

#endif // __EVec2_H

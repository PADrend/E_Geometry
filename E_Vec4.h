/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EVec4_H
#define __EVec4_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Vec4.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Vec4 ---|> [EScript::Object]
 *    				 |
 *    				 ------> Geometry::E_Vec4
 */
class E_Vec4 : public EScript::ReferenceObject<Geometry::Vec4>  {
		ES_PROVIDES_TYPE_NAME(Vec4)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Vec4(args&&... params) :
			ReferenceObject_t(E_Vec4::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Vec4() {}

		E_Vec4 * clone() const override		{	return new E_Vec4(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec4,		Geometry::_Vec4<int32_t>, Geometry::_Vec4<int32_t>(	(**eObj).x(), (**eObj).y(), (**eObj).z(), (**eObj).w()))
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec4,		Geometry::Vec4&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Vec4,		Geometry::Vec4*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Vec4&, 	E_Geometry::E_Vec4,		new E_Geometry::E_Vec4(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Vec4&&, 		E_Geometry::E_Vec4,		new E_Geometry::E_Vec4(obj))

namespace EScript{ // automatic conversion functions
template<> Geometry::Vec4 convertTo<Geometry::Vec4>(Runtime & rt,ObjPtr obj);
}

#endif // __EVec4_H

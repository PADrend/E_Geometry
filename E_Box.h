/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EBox_H
#define __EBox_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Box.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Box ---|> [EScript::ReferenceObject]
 *     				|
 *     				------> Geometry::Box
 */
class E_Box : public EScript::ReferenceObject<Geometry::Box> {
		ES_PROVIDES_TYPE_NAME(Box)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Box(args&&... params) :
			ReferenceObject_t(E_Box::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Box() {}

		E_Box * clone() const override		{	return new E_Box(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Box,		Geometry::_Box<int32_t>,
					Geometry::_Box<int32_t>(	Geometry::_Vec3<int32_t>((**eObj).getMin()),
												Geometry::_Vec3<int32_t>((**eObj).getMax())))
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Box,		Geometry::Box,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Box,		Geometry::Box&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Box,		Geometry::Box*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::_Box<int32_t>&,		E_Geometry::E_Box,	
					new E_Geometry::E_Box( Geometry::Vec3(obj.getMin()),Geometry::Vec3(obj.getMax())))
ES_CONV_OBJ_TO_EOBJ(const Geometry::Box&,				E_Geometry::E_Box,	new E_Geometry::E_Box(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Box&&, 					E_Geometry::E_Box,	new E_Geometry::E_Box(obj))

#endif // __EBox_H

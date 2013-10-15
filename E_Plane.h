/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EPlane_H
#define __EPlane_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Plane.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Plane ---|> [EScript::ReferenceObject]
 *     						|
 *     						------> Geometry::E_Plane
 */
class E_Plane : public EScript::ReferenceObject<Geometry::Plane> {
		ES_PROVIDES_TYPE_NAME(Plane)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Plane(args&&... params) :
			ReferenceObject_t(E_Plane::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Plane()	{}

		E_Plane * clone() const override		{	return new E_Plane(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Plane,		Geometry::Plane,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Plane,		Geometry::Plane&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Plane,		Geometry::Plane*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Plane&, 	E_Geometry::E_Plane,	new E_Geometry::E_Plane(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Plane&&, 			E_Geometry::E_Plane,	new E_Geometry::E_Plane(obj))

#endif // __EPlane_H

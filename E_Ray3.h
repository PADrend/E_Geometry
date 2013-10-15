/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __ERay3_H
#define __ERay3_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Line.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Ray3 ---|> [EScript::ReferenceObject]
 *    				|
 *     				------> Geometry::E_Ray3
 */
class E_Ray3 : public EScript::ReferenceObject<Geometry::Ray3> {
		ES_PROVIDES_TYPE_NAME(Ray3)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Ray3(args&&... params) :
			ReferenceObject_t(E_Ray3::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Ray3() {}

		E_Ray3 * clone() const override		{	return new E_Ray3(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Ray3,		Geometry::Ray3,			**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Ray3,		Geometry::Ray3&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Ray3,		Geometry::Ray3*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Ray3&, 	E_Geometry::E_Ray3,		new E_Geometry::E_Ray3(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Ray3&&, 		E_Geometry::E_Ray3,		new E_Geometry::E_Ray3(obj))

#endif // __ERay3_H

/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __ETriangle_H
#define __ETriangle_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Triangle.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Triangle ---|> [EScript::ReferenceObject]
 *    				|
 *     				------> Geometry::Triangle
 */
class E_Triangle : public EScript::ReferenceObject<Geometry::Triangle<Geometry::Vec3f> > {
		ES_PROVIDES_TYPE_NAME(Triangle)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Triangle(args&&... params) :
			ReferenceObject_t(E_Triangle::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Triangle() {}

		E_Triangle * clone() const override	{	return new E_Triangle(**this);		}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Triangle,							Geometry::Triangle<Geometry::Vec3f>,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Triangle,							Geometry::Triangle<Geometry::Vec3f>&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Triangle,							Geometry::Triangle<Geometry::Vec3f>*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Triangle<Geometry::Vec3f>&, 	E_Geometry::E_Triangle,						new E_Geometry::E_Triangle(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Triangle<Geometry::Vec3f>&&, 			E_Geometry::E_Triangle,						new E_Geometry::E_Triangle(obj))

#endif // __ETriangle_H

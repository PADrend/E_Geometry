/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GEOMETRY_E_SPHERE_H
#define E_GEOMETRY_E_SPHERE_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Sphere.h>
#include <string>

namespace E_Geometry {

/**
 * E_Sphere ---|> [EScript::ReferenceObject]
 *                 |
 *                 ------> Geometry::Sphere
 */
class E_Sphere : public EScript::ReferenceObject<Geometry::Sphere_f> {
		ES_PROVIDES_TYPE_NAME(Sphere)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Sphere(args&&... params) :
			ReferenceObject_t(E_Sphere::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Sphere() {}

		E_Sphere * clone() const override 		{	return new E_Sphere(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Sphere,		Geometry::Sphere_f,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Sphere,		Geometry::Sphere_f&,	**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Sphere,		Geometry::Sphere_f*,	&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Sphere_f&, 	E_Geometry::E_Sphere,	new E_Geometry::E_Sphere(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Sphere_f&&, 		E_Geometry::E_Sphere,	new E_Geometry::E_Sphere(obj))

#endif /* E_GEOMETRY_E_SPHERE_H */

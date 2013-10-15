/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef E_GEOMETRY_E_TETRAHEDRON_H
#define E_GEOMETRY_E_TETRAHEDRON_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Tetrahedron.h>
#include <string>

namespace E_Geometry {

/**
 * E_Tetrahedron ---|> [EScript::ReferenceObject]
 *                 |
 *                 ------> Geometry::Tetrahedron<float>
 */
class E_Tetrahedron : public EScript::ReferenceObject<Geometry::Tetrahedron<float> > {
		ES_PROVIDES_TYPE_NAME(Tetrahedron)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Tetrahedron(args&&... params) :
			ReferenceObject_t(E_Tetrahedron::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Tetrahedron() {
		}

		E_Tetrahedron * clone() const override 	{	return new E_Tetrahedron(**this);	}
		std::string toString() const override;
};

}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Tetrahedron,				Geometry::Tetrahedron<float>,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Tetrahedron,				Geometry::Tetrahedron<float>&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Tetrahedron,				Geometry::Tetrahedron<float>*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Tetrahedron<float>&, 	E_Geometry::E_Tetrahedron,			new E_Geometry::E_Tetrahedron(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Tetrahedron<float>&&, 		E_Geometry::E_Tetrahedron,			new E_Geometry::E_Tetrahedron(obj))

#endif /* E_GEOMETRY_E_TETRAHEDRON_H */

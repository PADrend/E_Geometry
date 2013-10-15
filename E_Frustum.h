/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EFrustum_H
#define __EFrustum_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Frustum.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Frustum ---|> [EScript::ReferenceObject]
 *     					|
 *     					------> Geometry::Frustum
 */
class E_Frustum : public EScript::ReferenceObject<Geometry::Frustum> {
		ES_PROVIDES_TYPE_NAME(Frustum)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Frustum(args&&... params) :
			ReferenceObject_t(E_Frustum::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Frustum() {}

		E_Frustum * clone() const override	{	return new E_Frustum(**this);	}
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Frustum,		Geometry::Frustum,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Frustum,		Geometry::Frustum&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Frustum,		Geometry::Frustum*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Frustum&, 	E_Geometry::E_Frustum,	new E_Geometry::E_Frustum(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Frustum&&, 		E_Geometry::E_Frustum,	new E_Geometry::E_Frustum(obj))

#endif // __EFrustum_H

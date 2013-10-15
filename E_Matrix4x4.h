/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef EMATRIX4X4_H
#define EMATRIX4X4_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Matrix4x4.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Matrix4x4 ---|> [EScript::Object]
 *     |
 *     ------> Geometry::Matrix4x4
 */
class E_Matrix4x4 : public EScript::ReferenceObject<Geometry::Matrix4x4>  {
		ES_PROVIDES_TYPE_NAME(Matrix4x4)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename ...args> explicit E_Matrix4x4(args&&... params) :
			ReferenceObject_t(E_Matrix4x4::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Matrix4x4() {}

		E_Matrix4x4 * clone() const override	{	return new E_Matrix4x4(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix4x4,		Geometry::Matrix4x4,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix4x4,		Geometry::Matrix4x4&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix4x4,		Geometry::Matrix4x4*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Matrix4x4&, 	E_Geometry::E_Matrix4x4,	new E_Geometry::E_Matrix4x4(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Matrix4x4&&, 			E_Geometry::E_Matrix4x4,	new E_Geometry::E_Matrix4x4(obj))

#endif // EMATRIX4X4_H

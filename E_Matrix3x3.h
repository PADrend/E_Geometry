/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef EMATRIX3X3_H
#define EMATRIX3X3_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Matrix3x3.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Matrix3x3 ---|> [EScript::ReferenceObject]
 *     					|
 *     					------> Geometry::Matrix3x3
 */
class E_Matrix3x3 : public EScript::ReferenceObject<Geometry::Matrix3x3> {
		ES_PROVIDES_TYPE_NAME(Matrix3x3)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Matrix3x3(args&&... params) :
			ReferenceObject_t(E_Matrix3x3::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Matrix3x3() {}

		E_Matrix3x3 * clone() const override	{	return new E_Matrix3x3(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix3x3,		Geometry::Matrix3x3,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix3x3,		Geometry::Matrix3x3&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Matrix3x3,		Geometry::Matrix3x3*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Matrix3x3&, 	E_Geometry::E_Matrix3x3,	new E_Geometry::E_Matrix3x3(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Matrix3x3&&, 			E_Geometry::E_Matrix3x3,	new E_Geometry::E_Matrix3x3(obj))

#endif // EMATRIX3X3_H

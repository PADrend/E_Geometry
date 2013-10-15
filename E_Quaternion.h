/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __EQuaternion_H
#define __EQuaternion_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Quaternion.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Quaternion ---|> [EScript::ReferenceObject]
 *     						|
 *     						------> Geometry::E_Quaternion
 */
class E_Quaternion : public EScript::ReferenceObject<Geometry::Quaternion> {
		ES_PROVIDES_TYPE_NAME(Quaternion)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Quaternion(args&&... params) :
			ReferenceObject_t(E_Quaternion::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Quaternion()	{}

		E_Quaternion * clone() const override	{	return new E_Quaternion(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Quaternion,		Geometry::Quaternion,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Quaternion,		Geometry::Quaternion&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Quaternion,		Geometry::Quaternion*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Quaternion&, 	E_Geometry::E_Quaternion,	new E_Geometry::E_Quaternion(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Quaternion&&, 		E_Geometry::E_Quaternion,	new E_Geometry::E_Quaternion(obj))

#endif // __EQuaternion_H

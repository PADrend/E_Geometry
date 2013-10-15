/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __ESRT_H
#define __ESRT_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/SRT.h>
#include <string>

namespace E_Geometry {

/**
 *    E_SRT ---|> [Object]
 *     				|
 *     				------> Geometry::SRT
 */
class E_SRT : public EScript::ReferenceObject<Geometry::SRT> {
		ES_PROVIDES_TYPE_NAME(SRT)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_SRT(args&&... params) :
			ReferenceObject_t(E_SRT::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_SRT() {}

		E_SRT * clone() const override		{	return new E_SRT(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_SRT,		Geometry::SRT,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_SRT,		Geometry::SRT&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_SRT,		Geometry::SRT*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::SRT&, 	E_Geometry::E_SRT,	new E_Geometry::E_SRT(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::SRT&&, 		E_Geometry::E_SRT,	new E_Geometry::E_SRT(obj))

#endif // __ESRT_H

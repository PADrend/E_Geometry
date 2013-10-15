/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __ERect_H
#define __ERect_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Rect.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Rect ---|> [EScript::ReferenceObject]
 *     				|
 *     				------> Geometry::Rect
 */
class E_Rect : public EScript::ReferenceObject<Geometry::Rect>  {
		ES_PROVIDES_TYPE_NAME(Rect)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Rect(args&&... params) :
			ReferenceObject_t(E_Rect::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Rect() {}

		E_Rect * clone() const override		{	return new E_Rect(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Rect,		Geometry::Rect,			**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Rect,		Geometry::Rect&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Rect,		Geometry::Rect*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Rect&, 	E_Geometry::E_Rect,		new E_Geometry::E_Rect(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Rect&&, 		E_Geometry::E_Rect,		new E_Geometry::E_Rect(obj))

#endif // __ERect_H

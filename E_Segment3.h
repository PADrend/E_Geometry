/*
	This file is part of the E_Geometry library.
	Copyright (C) 2007-2012 Benjamin Eikel <benjamin@eikel.org>
	Copyright (C) 2007-2012 Claudius Jähn <claudius@uni-paderborn.de>
	Copyright (C) 2007-2012 Ralf Petring <ralf@petring.net>
	
	This library is subject to the terms of the Mozilla Public License, v. 2.0.
	You should have received a copy of the MPL along with this library; see the 
	file LICENSE. If not, you can obtain one at http://mozilla.org/MPL/2.0/.
*/
#ifndef __ESegment3_H
#define __ESegment3_H

#include <EScript/Objects/ReferenceObject.h>
#include <Geometry/Line.h>
#include <string>

namespace E_Geometry {

/**
 *  E_Segment3 ---|> [EScript::ReferenceObject]
 *    				|
 *     				------> Geometry::E_Segment3
 */
class E_Segment3 : public EScript::ReferenceObject<Geometry::Segment3> {
		ES_PROVIDES_TYPE_NAME(Segment3)
	public:
		static EScript::Type * getTypeObject();
		static void init(EScript::Namespace & lib);

		template<typename...args> explicit E_Segment3(args&&... params) :
			ReferenceObject_t(E_Segment3::getTypeObject(),std::forward<args>(params)...) {}
		virtual ~E_Segment3() {}

		E_Segment3 * clone() const override		{	return new E_Segment3(**this);	}
		std::string toString() const override;
};
}

ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Segment3,		Geometry::Segment3,			**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Segment3,		Geometry::Segment3&,		**eObj)
ES_CONV_EOBJ_TO_OBJ(E_Geometry::E_Segment3,		Geometry::Segment3*,		&**eObj)
ES_CONV_OBJ_TO_EOBJ(const Geometry::Segment3&, 	E_Geometry::E_Segment3,		new E_Geometry::E_Segment3(obj))
ES_CONV_OBJ_TO_EOBJ(Geometry::Segment3&&, 		E_Geometry::E_Segment3,		new E_Geometry::E_Segment3(obj))

#endif // __ESegment3_H

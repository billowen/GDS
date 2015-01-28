/*
 * This file is part of GDSII.
 *
 * elements.h -- The header file which declare the elements in GDSII format.
 *
 * Copyright (c) 2015 Kangpeng Shao <billowen035@gmail.com>
 *
 * GDSII is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at you option) any later version.
 *
 * GDSII is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABLILTY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GDSII. If not, see <http://www.gnu.org/licenses/>.
 **/

#ifndef ELEMENTS_H
#define ELEMENTS_H
#include "tags.h"
#include <vector>
#include <string>
#include <fstream>

namespace GDS {
	class Structure;

	class Element {
		Record_type Tag;
		Structure* Parent;

	public:
		Element(Structure* parent = nullptr);
		Element(Record_type tag, Structure* parent = nullptr);
		virtual ~Element();

		Record_type tag() const;
		std::string type() const;
		/*!
		 * Get a rect which can enclose the element.
		 *
		 * \param [out] x1,y1,x2,y2	
		 * \return		Return false if can not get a valid rect.
		 */
		virtual bool boundaryRect(int& x1, int& y1, int& x2, int& y2) const;

		virtual bool read(std::ifstream &in);
		virtual bool write(std::ofstream &out);
		virtual bool printASCII(std::ofstream &out);

	protected:
		void setTag(Record_type tag);
	};

}
#endif // ELEMENTS_H


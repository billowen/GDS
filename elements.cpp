/*
 * This file is part of GDSII.
 *
 * elements.cpp -- The source file which defines the elements of GDSII format.
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

#include "elements.h"
#include "structures.h"


namespace GDS
{

	Element::Element(Structure* parent)
	{
		Tag = RECORD_UNKNOWN;
		Parent = parent;
	}

	Element::Element(Record_type tag, Structure* parent)
	{
		Tag = tag;
		Parent = parent;
	}

	Element::~Element()
	{
		if (Parent != nullptr)
		{
			for (int i = 0; i < Parent->size(); i++)
			{
				if (Parent->get(i) == this)
				{
					Parent->set(i, nullptr);
					break;
				}
			}
		}
	}

	std::string Element::type() const
	{
		if (Record_name.find(Tag) == Record_name.end())
			return "RECORD_UNKNOWN";
		else
			return Record_name[Tag];
	}

	Record_type Element::tag() const
	{
		return Tag;
	}

	Structure* Element::parent()
	{
		return Parent;
	}

	void Element::setParent(Structure* parent)
	{
		Parent = parent;
	}

	bool Element::boundaryRect(int& x1, int& y1, int& x2, int& y2) const
	{
		return false;
	}

	void Element::setTag(Record_type tag)
	{
		Tag = tag;
	}

	bool Element::read(std::ifstream &in)
	{
		return true;
	}

	bool Element::write(std::ofstream &out)
	{
		return true;
	}

	bool Element::printASCII(std::ofstream &out)
	{
		return true;
	}

}


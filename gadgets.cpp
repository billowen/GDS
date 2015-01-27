/*
* This file is part of GDSII.
*
* gadgets.cpp -- The header file which implement some functions to handler the data of GDS.
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

#include <assert.h>
#include "library.h"
#include "structures.h"
#include "elements.h"
#include "sref.h"
#include "aref.h"

namespace GDS
{
	void buildCellLinks(Library* lib)
	{
		if (lib == nullptr)
			return;

		for (size_t i = 0; i < lib->size(); i++)
		{
			Structure* node = lib->get(i);
			if (node == nullptr)
				continue;
			node->clearReferredList();
		}

		for (size_t i = 0; i < lib->size(); i++)
		{
			Structure* node = lib->get(i);
			if (node == nullptr)
				continue;
			for (size_t j = 0; j < node->size(); j++)
			{
				Element* e = node->get(j);
				if (e == nullptr)
					continue;
				switch (e->tag())
				{
				case SREF:
					if (SRef* sref = dynamic_cast<SRef*>(e))
					{
						std::string ref_name = sref->structName();
						Structure* reference = lib->get(ref_name);
						if (reference != nullptr)
						{
							sref->setReference(reference);
							reference->addReferred(sref);
						}
					}
					break;
				case AREF:
					if (ARef* aref = dynamic_cast<ARef*>(e))
					{
						std::string ref_name = aref->structName();
						Structure* reference = lib->get(ref_name);
						if (reference != nullptr)
						{
							aref->setReference(reference);
							reference->addReferred(aref);
						}
					}
					break;
				default:
					break;
				}

			}
		}
	}
}
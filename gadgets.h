/*
* This file is part of GDSII.
*
* gadgets.h -- The header file which declare some functions to handler the data of GDS.
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

#ifndef GDS_GADGETS_H
#define GDS_GADGETS_H

namespace GDS
{
	
	class Library;
	class Structure;
	class Element;
	class Techfile;
	
	void collectLayers(Library*lib, Techfile* techfile);
}

#endif

/*
* This file is part of GDSII.
*
* techfile.h -- The header file which declare the techfile.
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

#ifndef GDS_TECHFILE_H
#define GDS_TECHFILE_H

#include <string>
#include <vector>
#include <map>

namespace GDS
{
	class LayerNode
	{
		int Number;
		int Data_type;

	public:
		LayerNode(int num, int dt);

		int number() const;
		int dataType() const;

		void setNumber(int num);
		void setDataType(int dt);

	};

	class Techfile
	{
	public:
		static Techfile* getInstance();

		bool getLayer(std::string name, LayerNode& layer);
		bool getLayer(int num, int dt, LayerNode& layer);

	private:
		Techfile();
		
		std::map<std::string, LayerNode> Layers;
	};
}

#endif
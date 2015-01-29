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
	class Stipple
	{
		std::string							Name;
		std::vector<std::vector<bool > >	Bitmap;

	public:
		Stipple();
		Stipple(std::string name);
		~Stipple();

		std::string name() const;
		int row() const;
		int col() const;
		bool bit(int row, int col);

	};
	class LayerNode
	{
		int			Number;
		int			Data_type;
		int			Color_r;
		int			Color_g;
		int			Color_b;
		std::string Stipple;

	public:
		LayerNode();
		LayerNode(int num, int dt);


		int number() const;
		int dataType() const;
		void color(int& r, int& g, int& b) const;
		std::string stipple() const;

		void setNumber(int num);
		void setDataType(int dt);
		void setColor(int r, int g, int b);

	};

	class Techfile
	{
	public:
		static Techfile* getInstance();

		void clear();

		bool haveLayer(int num, int dt) const;
		bool getLayer(std::string name, LayerNode& layer);
		bool getLayer(int num, int dt, LayerNode& layer);
		bool getStipple(std::string name, Stipple& stipple);

		bool addLayer(int num, int dt);

	private:
		Techfile();
		
		std::map<std::string, LayerNode> Layers;
		std::vector<Stipple> Stipples;
	};
}

#endif
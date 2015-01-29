/*
* This file is part of GDSII.
*
* techfile.cpp -- The source file which defines the techfile.
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

#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "techfile.h"

namespace GDS
{
	Techfile::Techfile()
	{

	}

	void Techfile::clear()
	{
		Layers.clear();
		Stipples.clear();
	}

	Techfile* Techfile::getInstance()
	{
		static Techfile instance;
		return &instance;
	}

	bool Techfile::haveLayer(int num, int dt) const
	{
		for (auto node : Layers)
		{
			if (node.second.number() == num && node.second.dataType() == dt)
			{
				return true;
			}
		}
		return false;
	}

	bool Techfile::getLayer(std::string name, LayerNode& layer)
	{
		if (Layers.find(name) != Layers.end())
		{
			layer = Layers[name];
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Techfile::getLayer(int num, int dt, LayerNode& layer)
	{
		for (auto node : Layers)
		{
			if (node.second.number() == num && node.second.dataType() == dt)
			{
				layer = node.second;
				return true;
			}
		}
		return false;
	}

	bool Techfile::getStipple(std::string name, Stipple& stipple)
	{
		bool existed = false;
		for (size_t i = 0; i < Stipples.size(); i++)
		{
			if (Stipples[i].name() == name)
			{
				stipple = Stipples[i];
				existed = true;
				break;
			}
		}

		return existed;
	}

	bool Techfile::addLayer(int num, int dt)
	{
		if (haveLayer(num, dt))
			return false;
		LayerNode layer(num, dt);
		std::stringstream ss;
		ss << "L_" << num << "_" << dt;
		std::string name = ss.str();
		Layers[name] = layer;
		return true;
	}

	LayerNode::LayerNode()
	{
		Number = 0;
		Data_type = 0;

		srand(time(NULL));
		Color_r = rand() % 256;
		Color_g = rand() % 256;
		Color_b = rand() % 256;
	}

	LayerNode::LayerNode(int num, int dt)
	{
		Number = num;
		Data_type = dt;

		srand(time(NULL));
		Color_r = rand() % 256;
		Color_g = rand() % 256;
		Color_b = rand() % 256;
	}

	int LayerNode::number() const
	{
		return Number;
	}

	int LayerNode::dataType() const
	{
		return Data_type;
	}

	void LayerNode::color(int& r, int& g, int& b) const
	{
		r = Color_r;
		g = Color_g;
		b = Color_b;
	}

	std::string LayerNode::stipple() const
	{
		return Stipple;
	}

	void LayerNode::setNumber(int num)
	{
		Number = num;
	}

	void LayerNode::setDataType(int dt)
	{
		Data_type = dt;
	}

	void LayerNode::setColor(int r, int g, int b)
	{
		Color_r = r;
		Color_g = g;
		Color_b = b;
	}

	Stipple::Stipple()
	{

	}

	Stipple::Stipple(std::string name)
	{
		Name = name;
	}

	Stipple::~Stipple()
	{

	}

	std::string Stipple::name() const
	{
		return Name;
	}

	int Stipple::row() const
	{
		return Bitmap.size();
	}

	int Stipple::col() const
	{
		int col = -1;
		for (auto e : Bitmap)
		{
			if (col == -1)
				col = e.size();
			else if (e.size() < col)
				col = e.size();
		}

		return (col == -1) ? 0 : col;
	}

	bool Stipple::bit(int row, int col)
	{
		if (row >= 0 && row < Bitmap.size())
		{
			std::vector<bool> line = Bitmap[row];
			if (col >= 0 && col < line.size())
				return line[col];
		}

		return false;
	}

	
}
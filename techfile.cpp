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

#include "techfile.h"

namespace GDS
{
	Techfile::Techfile()
	{

	}

	Techfile* Techfile::getInstance()
	{
		static Techfile instance;
		return &instance;
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

	LayerNode::LayerNode(int num, int dt)
	{
		Number = num;
		Data_type = dt;
	}

	int LayerNode::number() const
	{
		return Number;
	}

	int LayerNode::dataType() const
	{
		return Data_type;
	}

	void LayerNode::setNumber(int num)
	{
		Number = num;
	}

	void LayerNode::setDataType(int dt)
	{
		Data_type = dt;
	}
}
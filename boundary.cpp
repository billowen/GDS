/*
 * This file is part of GDSII.
 *
 * boundary.cpp -- The source file which defines the BOUNDARY of GDSII format.
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
#include "boundary.h"
#include "exceptions.h"
#include <sstream>
#include "gdsio.h"

namespace GDS
{

	Boundary::Boundary(Structure* parent) :Element(BOUNDARY, parent)
	{
		Eflags = 0;
		Layer = -1;
		Data_type = -1;
	}

	Boundary::~Boundary()
	{

	}

	short Boundary::layer() const
	{
		return Layer;
	}

	short Boundary::dataType() const
	{
		return Data_type;
	}

	void Boundary::xy(std::vector<int> &x, std::vector<int> &y) const
	{
		x = X;
		y = Y;
	}

	bool Boundary::boundaryRect(int& x1, int& y1, int& x2, int& y2) const
	{
		assert(X.size() > 3 && X.size() == Y.size());
		if (X.size() > 3 && X.size() == Y.size())
		{
			x1 = y1 = INT_MAX;
			x2 = y2 = INT_MIN;
			for (int i = 0; i < X.size(); i++)
			{
				x1 = (X[i] < x1) ? X[i] : x1;
				x2 = (X[i] > x2) ? X[i] : x2;
				y1 = (Y[i] < y1) ? Y[i] : y1;
				y2 = (Y[i] > y2) ? Y[i] : y2;
			}
			return true;
		}
		else
			return false;
	}

	void Boundary::setLayer(short layer)
	{
		Layer = layer;
	}

	void Boundary::setDataType(short data_type)
	{
		Data_type = data_type;
	}

	void Boundary::setXY(std::vector<int> &x, std::vector<int> &y)
	{
		X = x;
		Y = y;
	}

	bool Boundary::read(std::ifstream &in)
	{
		bool finished = false;
		while (!finished)
		{
			short record_size = readShort(in);
			Byte record_type = readByte(in);
			Byte data_type = readByte(in);
			switch (record_type)
			{
			case ENDEL:
				finished = true;
				break;
			case EFLAGS:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of EFLAGS (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Eflags = readShort(in);
				break;
			case LAYER:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of LAYER (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Layer = readShort(in);
				break;
			case DATATYPE:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of DATATYPE (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Data_type = readShort(in);
				break;
			case XY:
			{
				record_size -= 4;
				int num = record_size / 8;
				if (record_size % 8 != 0 || num < 4)
				{
					std::stringstream ss;
					ss << "wrong record size of XY for BOUNDARY (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				for (int i = 0; i < num; i++)
				{
					int x = readInteger(in);
					int y = readInteger(in);
					X.push_back(x);
					Y.push_back(y);
				}
				break;
			}
			default:
				break;
			}
		}

		return true;
	}

	bool Boundary::write(std::ofstream &out)
	{
		short record_size;

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, BOUNDARY);
		writeByte(out, NoData);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, EFLAGS);
		writeByte(out, Integer_2);
		writeShort(out, Eflags);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, LAYER);
		writeByte(out, Integer_2);
		writeShort(out, Layer);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, DATATYPE);
		writeByte(out, Integer_2);
		writeShort(out, Data_type);

		record_size = 4 + 8 * X.size();
		writeShort(out, record_size);
		writeByte(out, XY);
		writeByte(out, Integer_4);
		for (size_t i = 0; i < X.size(); i++)
		{
			writeInteger(out, X[i]);
			writeInteger(out, Y[i]);
		}

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, ENDEL);
		writeByte(out, NoData);

		return true;
	}

	bool Boundary::printASCII(std::ofstream &out)
	{
		out << "BOUNDARY" << std::endl;
		out << "EFLAGS " << Eflags << std::endl;
		out << "LAYER " << Layer << std::endl;
		out << "DATATYPE " << Data_type << std::endl;
		out << "XY ";
		for (size_t i = 0; i < X.size(); i++)
		{
			out << X[i] << " " << Y[i] << " ";
		}
		out << std::endl;
		out << "ENDEL" << std::endl;
		return true;
	}

}



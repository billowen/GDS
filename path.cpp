/*
 * This file is part of GDSII.
 *
 * path.cpp -- The source file which defines the PATH of GDSII format.
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
#include "path.h"
#include "exceptions.h"
#include <sstream>
#include <algorithm>
#include "gdsio.h"

namespace GDS
{

	Path::Path(Structure* parent) :Element(PATH, parent)
	{
		Eflags = 0;
		Layer = -1;
		Data_type = -1;
		Width = 0;
		Begin_extn = 0;
		End_extn = 0;
		Path_type = 0;
	}

	Path::~Path()
	{

	}

	short Path::layer() const
	{
		return Layer;
	}

	short Path::dataType() const
	{
		return Data_type;
	}

	int Path::width() const
	{
		return Width;
	}

	void Path::extension(int &begin, int &end) const
	{
		begin = Begin_extn;
		end = End_extn;
	}

	int Path::pathType() const
	{
		return Path_type;
	}

	void Path::xy(std::vector<int> &x, std::vector<int> &y) const
	{
		x = X;
		y = Y;
	}

	bool Path::boundingRect(int& x1, int& y1, int& x2, int& y2) const
	{
		assert(X.size() >= 2 && X.size() == Y.size() && Width > 0);
		
		if (X.size() >= 2 && X.size() == Y.size() && Width > 0)
		{
			x1 = y1 = std::numeric_limits<int>::max();
			x2 = y2 = std::numeric_limits<int>::min();
			for (int i = 0; i < X.size(); i++)
			{
				x1 = (X[i] < x1) ? X[i] : x1;
				x2 = (X[i] > x2) ? X[i] : x2;
				y1 = (Y[i] < y1) ? Y[i] : y1;
				y2 = (Y[i] > y2) ? Y[i] : y2;
			}

			int beg = 0, end = 0;
			if (Path_type == 2)
			{
				beg = end = ceil(Width / 2.0);
			}
			else if (Path_type == 4)
			{
				beg = Begin_extn;
				end = End_extn;
			}
			for (int i = 1; i < X.size(); i++)
			{
				if (X[i - 1] == X[i])		// vertical
				{
					x1 = (X[i] - ceil(Width / 2.0) < x1) ? X[i] - ceil(Width / 2.0) : x1;
					x2 = (X[i] + ceil(Width / 2.0) > x2) ? X[i] + ceil(Width / 2.0) : x2;
					if (i == 1)		// first point
					{
						if (Y[i - 1] >= Y[i])
						{
							y2 = (Y[i - 1] + beg > y2) ? Y[i - 1] + beg : y2;
						}
						else
						{
							y1 = (Y[i - 1] - beg < y1) ? Y[i - 1] - beg : y1;
						}
					}
					if (i == X.size() - 1)	// last point
					{
						if (Y[i - 1] >= Y[i])
						{
							y1 = (Y[i] - end < y1) ? Y[i] - end : y1;
						}
						else
						{
							y2 = (Y[i] + end > y2) ? Y[i] + end : y2;
						}
					}
				}
				else   // horizontal
				{
					y1 = (Y[i] - ceil(Width / 2.0) < y1) ? Y[i] - ceil(Width / 2.0) : y1;
					y2 = (Y[i] + ceil(Width / 2.0) > y2) ? Y[i] + ceil(Width / 2.0) : y2;
					if (i == 1)
					{
						if (X[i - 1] >= X[i])
						{
							x2 = (X[i - 1] + beg > x2) ? X[i - 1] + beg : x2;
						}
						else
						{
							x1 = (X[i - 1] - beg < x1) ? X[i - 1] - beg : x1;
						}
					}
					if (i == X.size() - 1)
					{
						if (X[i - 1] >= X[i])
						{
							x1 = (X[i] - end < x1) ? X[i] - end : x1;
						}
						else
						{
							x2 = (X[i] + end > x2) ? X[i] + end : x2;
						}
					}
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	void Path::setLayer(short layer)
	{
		Layer = layer;
	}

	void Path::setDataType(short data_type)
	{
		Data_type = data_type;
	}

	void Path::setWidth(int width)
	{
		Width = width;
	}

	void Path::setExtension(int begin, int end)
	{
		Begin_extn = begin;
		End_extn = end;
	}

	void Path::setPathType(int type)
	{
		Path_type = type;
	}

	void Path::setXY(std::vector<int> &x, std::vector<int> &y)
	{
		X = x;
		Y = y;
	}

	bool Path::read(std::ifstream &in)
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
				if (record_size % 8 != 0 || num < 2)
				{
					std::stringstream ss;
					ss << "wrong record size of XY for PATH (";
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
			case WIDTH:
				if (record_size != 8)
				{
					std::stringstream ss;
					ss << "wrong record size of WIDTH (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Width = readInteger(in);
				break;
			case BGNEXTN:
				if (record_size != 8)
				{
					std::stringstream ss;
					ss << "wrong record size of BGNEXTN (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Begin_extn = readInteger(in);
				break;
			case ENDEXTN:
				if (record_size != 8)
				{
					std::stringstream ss;
					ss << "wrong record size of ENDEXTN (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				End_extn = readInteger(in);
				break;
			case PATHTYPE:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of PATHTYPE (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Path_type = readShort(in);
				break;
			default:
				break;
			}
		}

		return true;
	}

	bool Path::write(std::ofstream &out)
	{
		short record_size;

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, PATH);
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

		record_size = 8;
		writeShort(out, record_size);
		writeByte(out, WIDTH);
		writeByte(out, Integer_4);
		writeInteger(out, Width);

		record_size = 8;
		writeShort(out, record_size);
		writeByte(out, BGNEXTN);
		writeByte(out, Integer_4);
		writeInteger(out, Begin_extn);

		record_size = 8;
		writeShort(out, record_size);
		writeByte(out, ENDEXTN);
		writeByte(out, Integer_4);
		writeInteger(out, End_extn);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, PATHTYPE);
		writeByte(out, Integer_2);
		writeShort(out, Path_type);

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

	bool Path::printASCII(std::ofstream &out)
	{
		out << "PATH" << std::endl;
		out << "EFLAGS " << Eflags << std::endl;
		out << "LAYER " << Layer << std::endl;
		out << "DATATYPE " << Data_type << std::endl;
		out << "WIDTH " << Width << std::endl;
		out << "BGNEXTN " << Begin_extn << std::endl;
		out << "ENDEXTN " << End_extn << std::endl;
		out << "PATHTYPE " << Path_type << std::endl;
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


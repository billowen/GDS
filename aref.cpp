/*
 * This file is part of GDSII.
 *
 * aref.cpp -- The source file which defines the AREF of GDSII format.
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

#include <limits>
#include <assert.h>
#include "aref.h"
#include "log.h"
#include "exceptions.h"
#include <sstream>
#include "gdsio.h"
#include "structures.h"
#include "library.h"

namespace GDS
{

	ARef::ARef(Structure* parent) :Element(AREF, parent)
	{
		Eflags = 0;
		SName = "";
		Strans = 0;
		Row = 0;
		Col = 0;
		Angle = 0;
		Mag = 1;
	}

	ARef::~ARef()
	{
	}

	std::string ARef::structName() const
	{
		return SName;
	}

	short ARef::row() const
	{
		return Row;
	}

	short ARef::col() const
	{
		return Col;
	}

	void ARef::xy(std::vector<int> &x, std::vector<int> &y) const
	{
		x = X;
		y = Y;
	}

	double ARef::angle() const
	{
		return Angle;
	}

	double ARef::mag() const
	{
		return Mag;
	}

	short ARef::strans() const
	{
		return Strans;
	}

	bool ARef::stransFlag(STRANS_FLAG flag) const
	{
		return Strans & flag;
	}

	bool ARef::boundingRect(int& x1, int& y1, int& x2, int& y2) const
	{
		Library* lib = Library::getInstance();
		Structure* reference = lib->get(structName());
		if (reference == nullptr)
			return false;

		x1 = std::numeric_limits<int>::max();
		y1 = std::numeric_limits<int>::max();
		x2 = std::numeric_limits<int>::min();
		y2 = std::numeric_limits<int>::min();
		for (int i = 0; i < 3; i++)
		{
			x1 = X[i] < x1 ? X[i] : x1;
			y1 = Y[i] < y1 ? Y[i] : y1;
			x2 = X[i] > x2 ? X[i] : x2;
			y2 = Y[i] > y2 ? Y[i] : y2;
		}
		
		return true;
	}

	void ARef::setStructName(std::string name)
	{
		SName = name;
	}

	void ARef::setRowCol(int row, int col)
	{
		Row = row;
		Col = col;
	}

	void ARef::setXY(std::vector<int> &x, std::vector<int> &y)
	{
		X = x;
		Y = y;
	}

	void ARef::setAngle(double angle)
	{
		Angle = angle;
	}

	void ARef::setMag(double mag)
	{
		Mag = mag;
	}

	void ARef::setStrans(short strans)
	{
		Strans = strans;
	}

	void ARef::setStrans(STRANS_FLAG flag, bool enable)
	{
		Strans = enable ? (Strans | flag) : (Strans & (~flag));
	}

	bool ARef::read(std::ifstream &in)
	{
#ifdef _DEBUG_LOG
		LogIO* log = LogIO::getInstance();
#endif
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
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << std::endl;
					log->write(ss.str());
				}
#endif
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
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Eflags << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case SNAME:
				if (record_size < 4 || record_size % 2 != 0)
				{
					std::stringstream ss;
					ss << "wrong record size of SNAME (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				SName = readString(in, record_size - 4);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << SName << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case XY:
				if (record_size != 28)
				{
					std::stringstream ss;
					ss << "wrong record size of XY for AREF (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				for (int i = 0; i < 3; i++)
				{
					int x = readInteger(in);
					int y = readInteger(in);
					X.push_back(x);
					Y.push_back(y);
				}
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type;
					for (int i = 0; i < 3; i++)
					{
						ss << " " << X[i] << " " << Y[i];
					}
					ss << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case STRANS:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of STRANS (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Strans = readShort(in);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Strans<< std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case COLROW:
				if (record_size != 8)
				{
					std::stringstream ss;
					ss << "wrong record size of COLROW (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Col = readShort(in);
				Row = readShort(in);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Col << " " << Row << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case MAG:
				if (record_size != 12)
				{
					std::stringstream ss;
					ss << "wrong record size of MAG (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Mag = readDouble(in);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Mag << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			case ANGLE:
				if (record_size != 12)
				{
					std::stringstream ss;
					ss << "wrong record size of ANGLE (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Angle = readDouble(in);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Angle << std::endl;
					log->write(ss.str());
				}
#endif
				break;
			default:
				break;
			}
		}
		return true;
	}

	bool ARef::write(std::ofstream &out)
	{
		short record_size;

		// AREF
		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, AREF);
		writeByte(out, NoData);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, EFLAGS);
		writeByte(out, Integer_2);
		writeShort(out, Eflags);

		record_size = 4 + SName.size();
		if (record_size % 2 != 0)
			record_size += 1;
		writeShort(out, record_size);
		writeByte(out, SNAME);
		writeByte(out, String);
		writeString(out, SName);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, STRANS);
		writeByte(out, Integer_2);
		writeShort(out, Strans);

		record_size = 8;
		writeShort(out, record_size);
		writeByte(out, COLROW);
		writeByte(out, Integer_2);
		writeShort(out, Col);
		writeShort(out, Row);

		record_size = 28;
		writeShort(out, record_size);
		writeByte(out, XY);
		writeByte(out, Integer_4);
		for (int i = 0; i < 3; i++)
		{
			writeInteger(out, X[i]);
			writeInteger(out, Y[i]);
		}

		record_size = 12;
		writeShort(out, record_size);
		writeByte(out, ANGLE);
		writeByte(out, Real_8);
		writeDouble(out, Angle);

		record_size = 12;
		writeShort(out, record_size);
		writeByte(out, MAG);
		writeByte(out, Real_8);
		writeDouble(out, Mag);

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, ENDEL);
		writeByte(out, NoData);

		return true;
	}

	bool ARef::printASCII(std::ofstream &out)
	{
		out << "AREF" << std::endl;
		out << "EFLAGS " << Eflags << std::endl;
		out << "SNAME " << SName << std::endl;
		out << "STRANS " << Strans << std::endl;
		out << "COLROW " << Col << " " << Row << std::endl;
		out << "XY ";
		for (size_t i = 0; i < X.size(); i++)
		{
			out << X[i] << " " << Y[i] << " ";
		}
		out << std::endl;
		out << "ANGLE " << Angle << std::endl;
		out << "MAG " << Mag << std::endl;
		out << "ENDEL" << std::endl;

		return true;
	}

}



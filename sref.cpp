/*
 * This file is part of GDSII.
 *
 * sref.cpp -- The source file which defines the SREF of GDSII format.
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
#include "sref.h"
#include "exceptions.h"
#include <sstream>
#include "log.h"
#include "gdsio.h"
#include "library.h"
#include "structures.h"

namespace GDS
{

	SRef::SRef(Structure* parent) :Element(SREF, parent)
	{
		Eflags = 0;
		SName = "";
		Strans = 0;
		Angle = 0;
		Mag = 1;
	}

	SRef::~SRef()
	{
	}

	std::string SRef::structName() const
	{
		return SName;
	}

	void SRef::xy(int &x, int &y) const
	{
		x = X;
		y = Y;
	}

	double SRef::angle() const
	{
		return Angle;
	}

	double SRef::mag() const
	{
		return Mag;
	}

	short SRef::strans() const
	{
		return Strans;
	}

	bool SRef::stransFlag(STRANS_FLAG flag) const
	{
		return Strans & flag;
	}

	bool SRef::boundaryRect(int& x1, int& y1, int& x2, int& y2) const
	{
		Library* lib = Library::getInstance();
		Structure* reference = lib->get(structName());
		if (reference == nullptr)
			return false;

		return reference->boundingRect(x1, y1, x2, y2);
	}

	void SRef::setStructName(std::string name)
	{
		SName = name;
	}

	void SRef::setXY(int x, int y)
	{
		X = x;
		Y = y;
	}

	void SRef::setAngle(double angle)
	{
		Angle = angle;
	}

	void SRef::setMag(double mag)
	{
		Mag = mag;
	}

	void SRef::setStrans(short strans)
	{
		Strans = strans;
	}

	void SRef::setStrans(STRANS_FLAG flag, bool enable)
	{
		Strans = enable ? (Strans | flag) : (Strans & (~flag));
	}

	bool SRef::read(std::ifstream &in)
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
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << std::endl;
					log->write(ss.str());
				}
#endif
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
				if (record_size != 12)
				{
					std::stringstream ss;
					ss << "wrong record size of XY for SREF (";
					ss << std::hex << record_size << record_type << data_type;
					ss << "). ";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				X = readInteger(in);
				Y = readInteger(in);
#ifdef _DEBUG_LOG
				{
					std::stringstream ss;
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << X << " " << Y << std::endl;
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
					ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Strans << std::endl;
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

	bool SRef::write(std::ofstream &out)
	{
		short record_size;

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, SREF);
		writeByte(out, NoData);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, EFLAGS);
		writeByte(out, Integer_2);
		writeShort(out, Eflags);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, STRANS);
		writeByte(out, Integer_2);
		writeShort(out, Strans);

		record_size = 4 + SName.size();
		if (record_size % 2 != 0)
			record_size += 1;
		writeShort(out, record_size);
		writeByte(out, SNAME);
		writeByte(out, String);
		writeString(out, SName);

		record_size = 12;
		writeShort(out, record_size);
		writeByte(out, XY);
		writeByte(out, Integer_4);
		writeInteger(out, X);
		writeInteger(out, Y);

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

	bool SRef::printASCII(std::ofstream &out)
	{
		out << "SREF" << std::endl;
		out << "EFLAGS " << Eflags << std::endl;
		out << "SNAME " << SName << std::endl;
		out << "STRANS " << Strans << std::endl;
		out << "XY " << X << " " << Y << std::endl;
		out << "ANGLE " << Angle << std::endl;
		out << "MAG " << Mag << std::endl;
		out << "ENDEL" << std::endl;

		return true;
	}

}


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

#include "text.h"
#include "exceptions.h"
#include "log.h"
#include <sstream>
#include "gdsio.h"

namespace GDS
{

	Text::Text(Structure* parent) :Element(TEXT, parent)
	{
		Eflags = 0;
		Layer = -1;
		Text_type = -1;
		Presentation = 0;
		Strans = 0;
		String = "";
	}

	Text::~Text()
	{

	}

	short Text::layer() const
	{
		return Layer;
	}

	short Text::textType() const
	{
		return Text_type;
	}

	short Text::presentation() const
	{
		return Presentation;
	}

	short Text::strans() const
	{
		return Strans;
	}

	void Text::xy(int &x, int &y) const
	{
		x = X;
		y = Y;
	}

	std::string Text::string() const
	{
		return String;
	}

	void Text::setLayer(short layer)
	{
		Layer = layer;
	}

	void Text::setTextType(short text_type)
	{
		Text_type = text_type;
	}

	void Text::setPresentation(short presentation)
	{
		Presentation = presentation;
	}

	void Text::setStrans(short strans)
	{
		Strans = strans;
	}

	void Text::setXY(int x, int y)
	{
		X = x;
		Y = y;
	}

	void Text::setString(std::string string)
	{
		String = string;
	}

	bool Text::read(std::ifstream &in)
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
#ifdef _DEBUG_LOG
                {
                    std::stringstream ss;
                    ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Layer << std::endl;
                    log->write(ss.str());
                }
#endif
				break;
			case TEXTTYPE:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of TEXTTYPE (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Text_type = readShort(in);
#ifdef _DEBUG_LOG
                {
                    std::stringstream ss;
                    ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Text_type << std::endl;
                    log->write(ss.str());
                }
#endif
				break;
			case XY:
			{
				if (record_size != 12)
				{
					std::stringstream ss;
					ss << "wrong record size of XY for TEXT (";
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
			}
			case PRESENTATION:
				if (record_size != 6)
				{
					std::stringstream ss;
					ss << "wrong record size of PRESENTATION (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Presentation = readShort(in);
#ifdef _DEBUG_LOG
                {
                    std::stringstream ss;
                    ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << Presentation << std::endl;
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
			case STRING:
				if (record_size < 4 || record_size % 2 != 0)
				{
					std::stringstream ss;
					ss << "wrong record size of STRING (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				String = readString(in, record_size - 4);
#ifdef _DEBUG_LOG
                {
                    std::stringstream ss;
                    ss << std::dec << " " << record_size << " " << Record_name[record_type] << " " << data_type << " " << String << std::endl;
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

	bool Text::write(std::ofstream &out)
	{
		short record_size;

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, TEXT);
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
		writeByte(out, TEXTTYPE);
		writeByte(out, Integer_2);
		writeShort(out, Text_type);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, PRESENTATION);
		writeByte(out, Integer_2);
		writeShort(out, Presentation);

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, STRANS);
		writeByte(out, Integer_2);
		writeShort(out, Strans);

		record_size = 12;
		writeShort(out, record_size);
		writeByte(out, XY);
		writeByte(out, Integer_4);
		writeInteger(out, X);
		writeInteger(out, Y);

		record_size = 4 + String.size();
		if (record_size % 2 != 0)
			record_size += 1;
		writeShort(out, record_size);
		writeByte(out, STRING);
		writeByte(out, GDS::String);
		writeString(out, String);

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, ENDEL);
		writeByte(out, NoData);

		return true;
	}

	bool Text::printASCII(std::ofstream &out)
	{
		out << "TEXT" << std::endl;
		out << "EFLAGS " << Eflags << std::endl;
		out << "LAYER " << Layer << std::endl;
		out << "TEXTTYPE " << Text_type << std::endl;
		out << "PRESENTATION " << Presentation << std::endl;
		out << "STRANS " << Strans << std::endl;
		out << "XY " << X << " " << Y << std::endl;
		out << "STRING " << String << std::endl;
		out << "ENDEL";
		return true;
	}

}



/*
 * This file is part of GDSII.
 *
 * library.cpp -- The source file which defines the library of GDSII format.
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
#include "library.h"
#include "exceptions.h"
#include "tags.h"
#include "gdsio.h"
#include <sstream>
#include <ctime>
#include "elements.h"
#include "aref.h"
#include "sref.h"

namespace GDS {

	Library::Library()
	{
		init();
	}

	Library::~Library()
	{
		for (Structure* &e : Contents)
		{
			if (e != nullptr)
			{
				delete e;
				e = nullptr;
			}
		}
		Contents.clear();
	}

	void Library::init()
	{
		Lib_name = "";

		time_t now = time(0);
		tm *ltm    = localtime(&now);
		Mod_year   = ltm->tm_year + 1900;
		Mod_month  = ltm->tm_mon + 1;
		Mod_day    = ltm->tm_mday;
		Mod_hour   = ltm->tm_hour + 1;
		Mod_minute = ltm->tm_min + 1;
		Mod_second = ltm->tm_sec + 1;
		Acc_year   = ltm->tm_year + 1900;
		Acc_month  = ltm->tm_mon + 1;
		Acc_day    = ltm->tm_mday;
		Acc_hour   = ltm->tm_hour + 1;
		Acc_minute = ltm->tm_min + 1;
		Acc_second = ltm->tm_sec + 1;

		Version = 0;
		DBUnit_in_meter = 1e-9;
		DBUnit_in_userunit = 1e-3;

		for (Structure* &e : Contents)
		{
			if (e != nullptr)
			{
				delete e;
				e = nullptr;
			}
		}
		Contents.clear();
	}

	size_t Library::size()
	{
		for (int i = (int)Contents.size() - 1; i >= 0; i--)
		{
			if (Contents[i] == nullptr)
				Contents.erase(Contents.begin() + i);
		}
		return Contents.size();
	}

	Structure* Library::get(int index)
	{
		if (index < 0 || (size_t)index >= Contents.size())
			return nullptr;
		return Contents[index];
	}

	Structure* Library::add(std::string name)
	{
		bool existed = false;
		for (Structure* e : Contents)
		{
			if (e == nullptr)
				continue;
			if (e->name() == name)
			{
				existed = true;
				break;
			}
		}
		if (existed)
			return nullptr;

		Structure* new_item = new Structure(name);
		Contents.push_back(new_item);
		return new_item;
	}

	Structure* Library::get(std::string name)
	{
		for (Structure* e : Contents)
		{
			if (e == nullptr)
				continue;
			if (e->name() == name)
			{
				return e;
			}
		}
		return nullptr;
	}

	void Library::del(std::string name, bool del_referred)
	{
		Structure* node = get(name);
		if (node == nullptr)
			return;

		for (size_t i = 0; i < size(); i++)
		{
			Structure* node = Contents[i];
			assert(node != nullptr);
			if (node == nullptr)
				continue;
			if (node->name() == name)
			{
				if (del_referred)
				{
					std::vector<Element*> referred_list = node->getReferredList();
					for (auto ptr : referred_list)
					{
						delete ptr;
					}
					node->clearReferredList();
				}
				delete node;
				Contents.erase(Contents.begin() + i);
				break;
			}
		}
	}

	bool Library::read(std::ifstream &in)
	{
		init();
		// read HEADER
		short record_size = readShort(in);
		Byte record_type = readByte(in);
		Byte data_type = readByte(in);
		if (record_type != HEADER)
		{
			std::stringstream ss;
			ss << "unexpected tag where HEADER are expected (";
			ss << std::hex << record_size << record_type << data_type;
			ss << ").";
			std::string msg = ss.str();
			throw FormatError(msg);
		}
		if (record_size != 6)
		{
			std::stringstream ss;
			ss << "wrong record size of HEADER (";
			ss << std::hex << record_size << record_type << data_type;
			ss << ").";
			std::string msg = ss.str();
			throw FormatError(msg);
		}
		Version = readShort(in);

		// read BGNLIB
		record_size = readShort(in);
		record_type = readByte(in);
		data_type = readByte(in);
		if (record_type != BGNLIB)
		{
			std::stringstream ss;
			ss << "unexpected tag where BGNLIB are expected (";
			ss << std::hex << record_size << record_type << data_type;
			ss << ").";
			std::string msg = ss.str();
			throw FormatError(msg);
		}
		if (record_size != 28)
		{
			std::stringstream ss;
			ss << "wrong record size of BGNLIB (";
			ss << std::hex << record_size << record_type << data_type;
			ss << ").";
			std::string msg = ss.str();
			throw FormatError(msg);
		}
		Mod_year = readShort(in);
		Mod_month = readShort(in);
		Mod_day = readShort(in);
		Mod_hour = readShort(in);
		Mod_minute = readShort(in);
		Mod_second = readShort(in);
		Acc_year = readShort(in);
		Acc_month = readShort(in);
		Acc_day = readShort(in);
		Acc_hour = readShort(in);
		Acc_minute = readShort(in);
		Acc_second = readShort(in);

		while (1)
		{
			record_size = readShort(in);
			record_type = readByte(in);
			data_type = readByte(in);

			bool finished = false;
			switch (record_type)
			{
			case ENDLIB:
				finished = true;
				break;
			case LIBNAME:
				if (record_size < 4 || record_size % 2 != 0)
				{
					std::stringstream ss;
					ss << "wrong record size of " + Record_name[record_type] + " (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Lib_name = readString(in, record_size - 4);
				break;
			case UNITS:
				if (record_size != 20)
				{
					std::stringstream ss;
					ss << "wrong record size of UNITS (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				DBUnit_in_userunit = readDouble(in);
				DBUnit_in_meter = readDouble(in);
				break;
			case BGNSTR:
			{
				if (record_size != 28)
				{
					std::stringstream ss;
					ss << "wrong record size of BGNSTR (";
					ss << std::hex << record_size << record_type << data_type;
					ss << ").";
					std::string msg = ss.str();
					throw FormatError(msg);
				}
				Structure *node = new Structure();
				node->read(in);
				Contents.push_back(node);
				break;
			}
			default:
				break;
			}
			if (finished)
				break;
		}

		return true;
	}

	bool Library::write(std::ofstream &out)
	{
		int record_size;

		record_size = 6;
		writeShort(out, record_size);
		writeByte(out, HEADER);
		writeByte(out, Integer_2);
		writeShort(out, Version);

		record_size = 28;
		writeShort(out, record_size);
		writeByte(out, BGNLIB);
		writeByte(out, Integer_2);
		writeShort(out, Mod_year);
		writeShort(out, Mod_month);
		writeShort(out, Mod_day);
		writeShort(out, Mod_hour);
		writeShort(out, Mod_minute);
		writeShort(out, Mod_second);
		writeShort(out, Acc_year);
		writeShort(out, Acc_month);
		writeShort(out, Acc_day);
		writeShort(out, Acc_hour);
		writeShort(out, Acc_minute);
		writeShort(out, Acc_second);

		record_size = 4 + Lib_name.size();
		if (record_size % 2 != 0)
			record_size += 1;
		writeShort(out, record_size);
		writeByte(out, LIBNAME);
		writeByte(out, String);
		writeString(out, Lib_name);

		record_size = 20;
		writeShort(out, record_size);
		writeByte(out, UNITS);
		writeByte(out, Real_8);
		writeDouble(out, DBUnit_in_userunit);
		writeDouble(out, DBUnit_in_meter);

		for (Structure *e : Contents)
		{
			e->write(out);
		}

		record_size = 4;
		writeShort(out, record_size);
		writeByte(out, ENDLIB);
		writeByte(out, NoData);

		return true;
	}

	bool Library::printASCII(std::ofstream &out)
	{
		out << "HEADER " << Version << std::endl;
		out << "BGNLIB " << std::endl;
		out << Mod_year << " "
			<< Mod_month << " "
			<< Mod_day << " "
			<< Mod_hour << " "
			<< Mod_minute << " "
			<< Mod_second << std::endl;
		out << Acc_year << " "
			<< Acc_month << " "
			<< Acc_day << " "
			<< Acc_hour << " "
			<< Acc_minute << " "
			<< Acc_second << std::endl;
		out << "LIBNAME " << Lib_name << std::endl;
		out << "UNITS " << DBUnit_in_userunit << " " << DBUnit_in_meter << std::endl;

		for (auto e : Contents)
		{
			e->printASCII(out);
		}
		out << "ENDLIB";
		return true;
	}

}



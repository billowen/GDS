/*
 * This file is part of GDSII.
 *
 * structure.cpp -- The source file which defines the structure of GDSII format.
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

#include <sstream>
#include "structures.h"
#include "aref.h"
#include "boundary.h"
#include "path.h"
#include "sref.h"
#include "text.h"
#include "exceptions.h"
#include "gdsio.h"

using namespace GDS;

Structure::Structure()
{
    Struct_name = "";
    Mod_year    = -1;
    Mod_month   = -1;
    Mod_day     = -1;
    Mod_hour    = -1;
    Mod_minute  = -1;
    Mod_second  = -1;
    Acc_year    = -1;
    Acc_month   = -1;
    Acc_day     = -1;
    Acc_hour    = -1;
    Acc_minute  = -1;
    Acc_second  = -1;
}

Structure::~Structure()
{
    for (Element * &e : Contents)
    {
        if (e != nullptr)
        {
            delete e;
            e = nullptr;
        }
    }
    Contents.clear();
}

bool Structure::read(std::ifstream &in)
{
    Mod_year    = readShort(in);
    Mod_month   = readShort(in);
    Mod_day     = readShort(in);
    Mod_hour    = readShort(in);
    Mod_minute  = readShort(in);
    Mod_second  = readShort(in);
    Acc_year    = readShort(in);
    Acc_month   = readShort(in);
    Acc_day     = readShort(in);
    Acc_hour    = readShort(in);
    Acc_minute  = readShort(in);
    Acc_second  = readShort(in);

    bool finished = false;
    while (!finished)
    {
        short record_size = readShort(in);
        Byte record_type = readByte(in);
        Byte data_type = readByte(in);
        switch (record_type)
        {
        case ENDSTR:
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of ENDSTR (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            finished = true;
            break;
        case STRNAME:
            if (record_size < 4 || record_size % 2 != 0)
            {
                std::stringstream ss;
                ss << "wrong record size of STRNAME (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            Struct_name = readString(in, record_size - 4);
            break;
        case TEXT:
        {
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of TEXT (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            Text *e = new Text();
            e->read(in);
            Contents.push_back(e);
            break;
        }
        case BOUNDARY:
        {
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of BOUNDARY (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            Boundary *e = new Boundary();
            e->read(in);
            Contents.push_back(e);
            break;
        }
        case PATH:
        {
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of PATH (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            Path *e = new Path();
            e->read(in);
            Contents.push_back(e);
            break;
        }
        case SREF:
        {
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of SREF (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            SRef *e = new SRef();
            e->read(in);
            Contents.push_back(e);
            break;
        }
        case AREF:
        {
            if (record_size != 4)
            {
                std::stringstream ss;
                ss << "wrong record size of AREF (" ;
                ss << std::hex << record_size << record_type << data_type;
                ss << ").";
                std::string msg = ss.str();
                throw FormatError(msg);
            }
            ARef *e = new ARef();
            e->read(in);
            Contents.push_back(e);
            break;
        }
        default:
            break;
        }
    }
    return true;
}

bool Structure::write(std::ofstream &out)
{
    int record_size;

    record_size = 28;
    writeShort(out, record_size);
    writeByte(out, BGNSTR);
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

    record_size = 4 + Struct_name.size();
    if (record_size % 2 != 0)
        record_size += 1;
    writeShort(out, record_size);
    writeByte(out, STRNAME);
    writeByte(out, String);
    writeString(out, Struct_name);

    for (Element * e : Contents)
    {
        e->write(out);
    }

    record_size = 4;
    writeShort(out, record_size);
    writeByte(out, ENDSTR);
    writeByte(out, NoData);

    return true;
}

bool Structure::printASCII(std::ofstream &out)
{
    out << "BGNSTR" << std::endl;
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
    out << "STRNAME " << Struct_name << std::endl;
    for (Element *e : Contents)
    {
        e->printASCII(out);
    }
    out << "ENDSTR" << std::endl;

    return true;
}



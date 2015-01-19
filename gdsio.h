/*
 * This file is part of GDSII.
 *
 * gdsio.h -- The header file which declare the functions used to convert
 *            binary data from GDSII files.
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

#ifndef GDSIO_H
#define GDSIO_H
#include <fstream>
#include "tags.h"

namespace GDS {

/*
 * 2-Byte Signed Integer    ---- short
 * 4-Byte Signed Integer    ---- int
 * 4-Byte Real              ---- float
 * 8-Byte Real              ---- double
 * ASCII String             ---- std::string
 * Bit Array                ---- short
 **/

Byte readByte(std::ifstream &in);
short readShort(std::ifstream &in);
int readInteger(std::ifstream &in);
float readFloat(std::ifstream &in);
double readDouble(std::ifstream &in);
std::string readString(std::ifstream &in, int size);
short readBitarray(std::ifstream &in);

void writeByte(std::ofstream &out, Byte data);
void writeShort(std::ofstream &out, short data);
void writeInteger(std::ofstream &out, int data);
void writeFloat(std::ofstream &out, float data);
void writeDouble(std::ofstream &out, double data);
void writeString(std::ofstream &out, std::string data);
void writeBitarray(std::ofstream &out, short data);



}

#endif // GDSIO_H


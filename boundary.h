/*
 * This file is part of GDSII.
 *
 * boundary.h -- The header file which declare the BOUNDARY in GDSII format.
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

#ifndef BOUNDARY_H
#define BOUNDARY_H
#include "elements.h"

namespace GDS {

/*!
 * \brief Class for 'BOUNDARY' GDSII element
 *
 * GDS syntax:
 *  BOUNDARY
 *  [EFLAGS]
 *  [PLEX]
 *  LAYER
 *  DATATYPE
 *  XY
 *  ENDEL
 */
class Boundary : public Element {
    short               Eflags;         //< 2 bytes of bit flags. Not support yet.
    short               Layer;
    short               Data_type;
    std::vector<int>    X, Y;

public:
    Boundary(Structure *parent);
    virtual ~Boundary();

	short layer() const;
	short dataType() const;
	void xy(std::vector<int> &x, std::vector<int> &y)const;

	void setLayer(short layer);
	void setDataType(short data_type);
	void setXY(std::vector<int> &x, std::vector<int> &y);

    virtual bool read(std::ifstream &in);
    virtual bool write(std::ofstream &out);
    virtual bool printASCII(std::ofstream &out);
};

}

#endif // BOUNDARY_H


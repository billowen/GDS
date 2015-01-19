/*
 * This file is part of GDSII.
 *
 * aref.h -- The header file which declare the AREF in GDSII format.
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

#ifndef AREF_H
#define AREF_H
#include "elements.h"

namespace GDS {

/*!
 * \brief Class for 'AREF' GDSII element
 *
 * GDS syntax:
 * GDS syntax:
 *  AREF
 *  [EFLAGS]
 *  [PLEX]
 *  SNAME
 *  [STRANS]
 *  COLROW
 *  XY
 *  ENDEL
 */
class ARef : public Element {
    short               Eflags;
    std::string         SName;
    short               Strans;
    short               Row, Col;
    std::vector<int>    X, Y;
    double              Angle;
    double              Mag;

public:
    ARef();
    virtual ~ARef();

    virtual bool read(std::ifstream &in);
    virtual bool write(std::ofstream &out);
    virtual bool printASCII(std::ofstream &out);
};

}

#endif // AREF_H


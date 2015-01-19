/*
 * This file is part of GDSII.
 *
 * text.h -- The header file which declare the TEXT in GDSII format.
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

#ifndef TEXT_H
#define TEXT_H
#include "elements.h"

namespace GDS {

/*!
 * \brief Class for 'Text' GDSII element
 *
 * GDS syntax:
 *  TEXT
 *  [EFLAGS]
 *  [PLEX]
 *  LAYER
 *  TEXTLAYER
 *  [PRESENTATION]
 *  [STRANS]
 *  XY
 *  STRING
 *  ENDEL
 */
class Text : public Element {
    short               Eflags;         //< 2 bytes of bit flags. Not support yet.
    short               Layer;
    short               Text_type;
    short               Presentation;
    short               Strans;
    int                 X, Y;
    std::string         String;

public:
    Text();
    virtual ~Text();

    virtual bool read(std::ifstream &in);
    virtual bool write(std::ofstream &out);
    virtual bool printASCII(std::ofstream &out);
};

}

#endif // TEXT_H


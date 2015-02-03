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
		ARef(Structure* parent = nullptr);
		virtual ~ARef();

		std::string structName() const;
		short row() const;
		short col() const;
		void xy(std::vector<int> &x, std::vector<int> &y) const;
		double angle() const;
		double mag() const;
		short strans() const;
		virtual bool boundingRect(int& x1, int& y1, int& x2, int& y2) const;

		void setStructName(std::string name);
		void setRowCol(int row,  int col);
		void setXY(std::vector<int> &x, std::vector<int> &y);
		void setAngle(double angle);
		void setMag(double mag);
		void setStrans(short strans);

		virtual bool read(std::ifstream &in);
		virtual bool write(std::ofstream &out);
		virtual bool printASCII(std::ofstream &out);
	};

}

#endif // AREF_H


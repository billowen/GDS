/*
 * This file is part of GDSII.
 *
 * sref.h -- The header file which declare the SREF in GDSII format.
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

#ifndef SREF_H
#define SREF_H
#include "elements.h"

namespace GDS {
	class Structure;

	/*!
	 * \brief Class for 'SREF' GDSII element
	 *
	 * GDS syntax:
	 *  SREF
	 *  [EFLAGS]
	 *  [PLEX]
	 *  SNAME
	 *  [STRANS]
	 *  XY
	 *  ENDEL
	 */
	class SRef : public Element {
		short               Eflags;
		std::string         SName;
		short               Strans;
		int                 X, Y;
		double              Angle;
		double              Mag;

	public:
		SRef(Structure *parent = nullptr);
		virtual ~SRef();

		std::string structName() const;
		void xy(int &x, int &y) const;
		double angle() const;
		double mag() const;
		short strans() const;
		virtual bool boundaryRect(int& x1, int& y1, int& x2, int& y2) const;

		void setStructName(std::string name);
		void setXY(int x, int y);
		void setAngle(double angle);
		void setMag(double mag);
		void setStrans(short strans);

		virtual bool read(std::ifstream &in);
		virtual bool write(std::ofstream &out);
		virtual bool printASCII(std::ofstream &out);
	};

}

#endif // SREF_H


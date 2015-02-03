/*
 * This file is part of GDSII.
 *
 * path.h -- The header file which declare the PATH in GDSII format.
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

#ifndef PATH_H
#define PATH_H
#include "elements.h"

namespace GDS {

	/*!
	 * \brief Class for 'PATH' GDSII element
	 *
	 * GDS syntax:
	 *  PATH
	 *  [EFLAGS]
	 *  [PLEX]
	 *  LAYER
	 *  DATATYPE
	 *  [PATHTYPE]
	 *  [WIDTH]
	 *  [BGNEXTN]
	 *  [ENDEXTN]
	 *  XY
	 *  ENDEL
	 */
	class Path : public Element {
		short               Eflags;         //< 2 bytes of bit flags. Not support yet.
		short               Layer;
		short               Data_type;
		int                 Width;
		int                 Begin_extn;
		int                 End_extn;
		short               Path_type;
		std::vector<int>    X, Y;

	public:
		Path(Structure* parent = nullptr);
		virtual ~Path();

		short layer() const;
		short dataType() const;
		int width() const;
		void extension(int &begin, int &end) const;
		int pathType() const;
		void xy(std::vector<int> &x, std::vector<int> &y) const;
		virtual bool boundingRect(int& x1, int& y1, int& x2, int& y2) const;

		void setLayer(short layer);
		void setDataType(short data_type);
		void setWidth(int width);
		void setExtension(int begin, int end);
		void setPathType(int type);
		void setXY(std::vector<int> &x, std::vector<int> &y);

		virtual bool read(std::ifstream &in);
		virtual bool write(std::ofstream &out);
		virtual bool printASCII(std::ofstream &out);
	};

}
#endif // PATH_H


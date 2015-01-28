/*
 * This file is part of GDSII.
 *
 * struct.h -- The header file which declare the structure of GDSII format.
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

#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <vector>
#include <string>
#include <fstream>
#include "elements.h"

namespace GDS {

	class Structure {
		std::string     Struct_name;
		short           Mod_year;
		short           Mod_month;
		short           Mod_day;
		short           Mod_hour;
		short           Mod_minute;
		short           Mod_second;
		short           Acc_year;
		short           Acc_month;
		short           Acc_day;
		short           Acc_hour;
		short           Acc_minute;
		short           Acc_second;

		std::vector<Element*> Contents;

		std::vector<Element*> Referred_list;		//< Point to the AREF/SREF which use current structure as a reference;

	public:
		Structure();
		Structure(std::string name);
		~Structure();

		std::string name() const;
		size_t size();
		Element* get(int index) const;
		std::vector<Element*> getReferredList();

		void set(int index, Element* e);
		void addReferred(Element* referred);
		void clearReferredList();
		void delReferred(Element* referred);

		bool read(std::ifstream &in);
		bool write(std::ofstream &out);
		bool printASCII(std::ofstream &out);
	};

}



#endif // STRUCTURES_H


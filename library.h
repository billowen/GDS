/*
 * This file is part of GDSII.
 *
 * library.h -- The header file which declare the library in GDSII format.
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

#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include <fstream>
#include "structures.h"

namespace GDS {

	class Library {
		short           Version;
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
		std::string     Lib_name;
		double          DBUnit_in_meter;
		double          DBUnit_in_userunit;

		std::vector<Structure*> Contents;

		Library();
	public:
		~Library();
        
        static Library* getInstance();

		void init();

		size_t size();
		Structure* get(int index);
		Structure* get(std::string name);
		/*!
		 * Add a new structure into library. If there is a structure existed in library which
		 * have the same name, it will cause the failure of process.
		 * 
		 * \param [in] name		The name of the new structure.
		 *
		 * \return	The pointer to the new structure. If failed to add the new structure, the
		 *			return value will be nullptr.
		 */
		Structure* add(std::string name);
		/*!
		 * Delete a structure in the library.
		 *
		 * \param [in] name			Name of structure.
		 * \param [in] de_referred	Wether to delete the SREF/AREF or not.
		 */
		void del(std::string name, bool del_referred = false);


		/*!
		 * \brief Read gdsii data from file stream.
		 *
		 * The call will throw some exceptions.
		 * \param in
		 * \return
		 */
		bool read(std::ifstream &in);
		/*!
		 * \brief Write gdsii data to file stream.
		 *
		 * The call will throw some exceptions.
		 * \param out
		 * \return
		 */
		bool write(std::ofstream &out);
		bool printASCII(std::ofstream &out);
	};
}

#endif // LIBRARY_H


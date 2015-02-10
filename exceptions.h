/*
 * This file is part of GDSII.
 *
 * exceptions.h -- The header file which declare the exceptions using in the project.
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

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace GDS {

class FormatError : public std::exception {
    std::string Message;

public:
    FormatError();
    FormatError(std::string message);
    virtual ~FormatError();

#ifdef _WIN32
	virtual const char *what() const;
#else
	virtual const char *what() const noexcept;
#endif
    void setMessage(std::string message);
};
}

#endif // EXCEPTIONS_H


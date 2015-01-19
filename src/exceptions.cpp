/*
 * This file is part of GDSII.
 *
 * exceptions.cpp -- The source file which define the exceptions using in the project.
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

#include "exceptions.h"

using namespace GDS;

FormatError::FormatError() noexcept
{
    Message = "";
}

FormatError::FormatError(std::string message) noexcept
{
    Message = message;
}

FormatError::~FormatError()
{

}

const char* FormatError::what() const noexcept
{
    std::string ret = "Format error: " + Message;

    return ret.c_str();
}

void FormatError::setMessage(std::string message)
{
    Message = message;
}

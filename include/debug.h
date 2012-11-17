/*
Act-Out! game library - implements generic game logic.
Copyright (C) 2012 Rio Lowry, Chris Pinter, Matt Voroney

This file is part of Act-Out!

Act-Out! is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Act-Out! is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Act-Out!.  If not, see <http://www.gnu.org/licenses/>.
*/
/** \file debug.h
 * Defines custom debugging macros
 */
#ifndef DEBUG_H
#define DEBUG_H

#include <cassert>

/**
 * \def dout
 *
 * \brief defines a c++ stream style debug output facility. 
 *
 * \details This symbol can be used in exactly the same manner as std::cout
 * or std::cerr. If NDEBUG is defined, then this symbol will be defined as
 * a nop. If NDEBUG is not defined, then for any 'dout' statements, the print
 * line will be prefixed with the name of the file, and the line number that
 * the statement was run from.
 */
#ifdef NDEBUG
#   define dout if (false) std::cout
#else
#   define dout std::cout << __FILE__ << ": " << __LINE__ << " "
#endif


#endif /* DEBUG_H */


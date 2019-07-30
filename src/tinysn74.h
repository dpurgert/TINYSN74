/***********************************************************************
*
*                 Program: Arduino SN74HC595 Library - sn74.h
*                      by: Dan Purgert <dan@djph.net>    
*               copyright: 2018
*                 version: 0.6
*                    date: Fri, 19 Jul 2019 19:27:13 -0400
*                 purpose: Library for the SN74HC595 shift register, as
*                        : it's readily available from suppliers
*
*                 license: GPL v2 (only)
*              repository: http://github.com/dpurgert
*
*  This program is free software; you can redistribute it and/or
*  modify it under the terms of the GNU General Public License
*  as published by the Free Software Foundation.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
*  02110-1301, USA.
***********************************************************************/

/** 
 * @file
 *
*/

#ifndef SN74_H
#define SN74_H

//#include <stdint.h>
#include "tinysn74_config.h"

#ifdef __cplusplus 
extern "C" {
#endif

void snInit (void);

void snCLR (void);

void snOE (uint8_t off); 

void snShiftInit (void);

void snShift (uint8_t *b);

void snLat (void);

#ifdef __cplusplus
}
#endif
#endif

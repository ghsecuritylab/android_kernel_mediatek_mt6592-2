/* San Angeles Observation OpenGL ES version example
 * Copyright 2004-2005 Jetro Lauha
 * All rights reserved.
 * Web: http://iki.fi/jetro/
 *
 * This source is free software; you can redistribute it and/or
 * modify it under the terms of EITHER:
 *   (1) The GNU Lesser General Public License as published by the Free
 *       Software Foundation; either version 2.1 of the License, or (at
 *       your option) any later version. The text of the GNU Lesser
 *       General Public License is included with this source in the
 *       file LICENSE-LGPL.txt.
 *   (2) The BSD-style license that is included with this source in
 *       the file LICENSE-BSD.txt.
 *
 * This source is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files
 * LICENSE-LGPL.txt and LICENSE-BSD.txt for more details.
 *
 * $Id: shapes.h,v 1.6 2005/01/31 22:15:30 tonic Exp $
 * $Revision: 1.6 $
 */

#ifndef SHAPES_H_INCLUDED
#define SHAPES_H_INCLUDED


#define SUPERSHAPE_PARAMS 15

static const float sSuperShapeParams[][SUPERSHAPE_PARAMS] =
{
    
    { 10, 1,    2,    90,      1,   -45,    8,    1,    1,    -1,     1,  -0.4f,   20,  30, 2 }, 
    { 10, 1,    2,    90,      1,   -45,    4,    1,    1,    10,     1,  -0.4f,   20,  20, 4 }, 
    { 10, 1,    2,    60,      1,   -10,    4,    1,    1,    -1,    -2,  -0.4f,   41,  41, 1 }, 
    {  6, 1,    1,    60,      1,   -70,    8,    1,    1,  0.4f,     3,  0.25f,   20,  20, 1 }, 
    {  4, 1,    1,    30,      1,    20,   12,    1,    1,  0.4f,     3,  0.25f,   10,  30, 1 }, 
    {  8, 1,    1,    30,      1,    -4,    8,    2,    1,    -1,     5,   0.5f,   25,  26, 1 }, 
    { 13, 1,    1,    30,      1,    -4,   13,    1,    1,     1,     5,      1,   30,  30, 6 }, 
    { 10, 1, 1.1f, -0.5f,   0.1f,    70,   60,    1,    1,   -90,     0, -0.25f,   20,  60, 8 }, 
    {  7, 1,    1,    20,  -0.3f, -3.5f,    6,    1,    1,    -1,  4.5f,   0.5f,   10,  20, 4 }, 
    {  4, 1,    1,    10,     10,    10,    4,    1,    1,    10,    10,     10,   10,  20, 1 }, 
    {  4, 1,    1,     1,      1,     1,    4,    1,    1,     1,     1,      1,   10,  10, 2 }, 
    {  1, 1,    1,    38, -0.25f,    19,    4,    1,    1,    10,    10,     10,   10,  15, 2 }, 
    {  2, 1,    1,  0.7f,   0.3f,  0.2f,    3,    1,    1,   100,   100,    100,   10,  25, 2 }, 
    {  6, 1,    1,     1,      1,     1,    3,    1,    1,     1,     1,      1,   30,  30, 2 }, 
    {  3, 1,    1,     1,      1,     1,    6,    1,    1,     2,     1,      1,   10,  20, 2 }, 
    {  6, 1,    1,     6,   5.5f,   100,    6,    1,    1,    25,    10,     10,   30,  20, 2 }, 
    {  3, 1,    1,  0.5f,   1.7f,  1.7f,    2,    1,    1,    10,    10,     10,   20,  20, 2 }, 
    {  5, 1,    1,  0.1f,   1.7f,  1.7f,    1,    1,    1,  0.3f,  0.5f,   0.5f,   20,  20, 4 }, 
    {  2, 1,    1,     6,   5.5f,   100,    6,    1,    1,     4,    10,     10,   10,  22, 1 }, 
    {  6, 1,    1,    -1,     70,  0.1f,    9,    1, 0.5f,   -98, 0.05f,    -45,   20,  30, 4 }, 
    {  6, 1,    1,    -1,     90, -0.1f,    7,    1,    1,    90,  1.3f,     34,   13,  16, 1 }, 
};
#define SUPERSHAPE_COUNT (sizeof(sSuperShapeParams) / sizeof(sSuperShapeParams[0]))


#endif 
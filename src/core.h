/*
 * core.h -- header file for reading in the interface configuration of the client
 * Part of the CarFi project
 * Author: Sylvain Dassier <sourav.sxcs@gmail.com>
 * Copyright (C) 2016 - eternity Sylvain Dassier
 *
****************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 ***************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILENAME "config.conf"
#define MAXBUF 1024
#define DELIM "="

struct config {
	char wifi[MAXBUF];
	char cellular[MAXBUF];
};

struct config readConfig();

void subFlow(int);
void subFlowAdd(int, char[]);

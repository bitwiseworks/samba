/*
   Unix SMB/CIFS implementation.

   This file contains Samba helper functions for the OS/2 port of samba
   do not try to compile on other platforms!
   
   Copyright (C) 2007-2019
                 Silvan Scherrer 
                 Yuri Dario
                 Paul Smedley
                 Herwig Bauernfeind
 
     ** NOTE! The following LGPL license applies to the replace
     ** library. This does NOT imply that all of Samba is released
     ** under the LGPL

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifdef __OS2__

#define INCL_DOS
#define INCL_DOSDATETIME
#define INCL_DOSERRORS
#include <os2.h>
#include <time.h>

/* Samba DEBUG() needs the following includes and defines */
#include "replace.h"
#include "debug.h"


/* set date/time on OS/2 */
int os2_setdatetime(time_t t)
{
	struct tm *tm;

	tm = localtime(&t);
	if (!tm)
		return -1;


	DATETIME DateTime = {0};
	APIRET rc = NO_ERROR;

	/* Get current date/time to properly fill structure */
	rc = DosGetDateTime(&DateTime);
	if (rc != NO_ERROR)
		return rc;

	DateTime.year = (USHORT) ((BYTE) tm->tm_year+1900);
	DateTime.month = (UCHAR) ((BYTE) tm->tm_mon+1);
	DateTime.day = (UCHAR) ((BYTE) tm->tm_mday);
	DateTime.hours = (UCHAR) ((BYTE) tm->tm_hour);
	DateTime.minutes = (UCHAR) ((BYTE) tm->tm_min);
	DateTime.seconds = (UCHAR) ((BYTE) tm->tm_sec);

	rc = DosSetDateTime(&DateTime);  /* Update the date and time */

	if (rc!= NO_ERROR)
		DEBUG(3, ("DosSetDateTime error : return code = %u\n", rc));

	return rc;
}

#endif

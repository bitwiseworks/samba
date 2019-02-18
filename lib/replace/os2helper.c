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

#include <sys/socket.h>


/* OS/2 specific pipe implementation, we have to use socketpair as select on 
   filehandle is not working. */
int os2_pipe(int fds[2])
{
	int rc = 0;

	rc = socketpair(AF_UNIX, SOCK_STREAM, 0, fds);
	return rc;
}

#endif

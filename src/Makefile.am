## Process this file with automake to produce Makefile.in.
## Makefile.am for hello/src.
##
## Copyright (C) 1996, 1997, 2001, 2005 Free Software Foundation, Inc.
##
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

bin_PROGRAMS = hello
hello_SOURCES = hello.c version.c getopt.c getopt1.c getopt.h system.h 
noinst_HEADERS = gettext.h

hello_LDADD = @LIBINTL@ @ALLOCA@

localedir = $(datadir)/locale

INCLUDES = -I. -I$(srcdir) -I.. -I../intl -I$(top_srcdir)/intl
DEFS = -DLOCALEDIR=\"$(localedir)\" @DEFS@

## # Automake cannot handle this now (version 1.0).
## $(bin_PROGRAMS): $(LDADD)

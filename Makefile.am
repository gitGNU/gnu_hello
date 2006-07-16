# Process this file with automake to produce Makefile.in (in this,
# and all subdirectories).
# 
# Makefile for the top-level directory of GNU hello.
# Copyright (C) 1997, 1998, 2005, 2006 Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation,
# Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

# Find gnulib headers.
ACLOCAL_AMFLAGS = -I gnulib/m4

# Additional files to distribute.
EXTRA_DIST = ChangeLog.O

# Subdirectories to descend into.
SUBDIRS = contrib gnulib/lib po src doc man tests

# `make diff' produces a diff against the previous version, given both
# .tar.gz's in the current directory.  This should only be done when an
# official release is made (and only if you care to provide diffs).
# 
hello_pre = 2.1.1
#
diff: diffcheck
	echo -e "\
To apply these patches, cd to the main directory of the package\n\
and then use \`patch -p1 < hello-XXX.diff'.\n\
Before building the program, run \`autogen.sh'.\n" > \
	    $(PACKAGE)-$(hello_pre)-$(VERSION).diff
	-diff -rc2P --exclude=configure --exclude=config.h.in --exclude=*.info \
	    --exclude=*.gmo --exclude=aclocal.m4 \
	    $(PACKAGE)-$(hello_pre) $(PACKAGE)-$(VERSION) >> \
	    $(PACKAGE)-$(hello_pre)-$(VERSION).diff
	gzip --force --best $(PACKAGE)-$(hello_pre)-$(VERSION).diff

diffcheck:
	for d in $(PACKAGE)-$(hello_pre) $(PACKAGE)-$(VERSION) ; do \
	    if test ! -d $$d ; then \
	        if test -r $$d.tar.gz ; then \
	            tar -zxf $$d.tar.gz ; \
                else \
	            echo subdir $$d does not exist. ; \
	            exit 1 ; \
                fi ; \
	    fi ; \
	done

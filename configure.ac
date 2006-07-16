dnl Process this file with autoconf to produce a configure script.
dnl
dnl This file is free software; as a special exception the author gives
dnl unlimited permission to copy and/or distribute it, with or without
dnl modifications, as long as this notice is preserved.
dnl
dnl This program is distributed in the hope that it will be useful, but
dnl WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
dnl implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

AC_INIT([GNU Hello], [2.1.90], [bug-hello@gnu.org])

dnl Must come before AM_INIT_AUTOMAKE.
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([dist-bzip2 readme-alpha])

# Minimum Autoconf version required.
AC_PREREQ(2.59)

# Where to generate output; srcdir location.
AC_CONFIG_HEADERS([config.h:config.in])dnl Keep filename to 8.3 for MS-DOS.
AC_CONFIG_SRCDIR([src/hello.c])

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC

# Since we use gnulib: gl_EARLY must be called as soon as possible after
# the C compiler is checked.  The others could be later, but we just
# keep everything together.
gl_EARLY
gl_INIT

# Since we make a helper library.
AC_PROG_RANLIB

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
AM_MISSING_PROG(HELP2MAN, help2man)

dnl Checks for header files.
AC_HEADER_STDC([])
AC_CHECK_HEADERS([string.h fcntl.h sys/file.h sys/param.h])

# i18n support from GNU gettext.
AM_GNU_GETTEXT_VERSION([0.14.5])
AM_GNU_GETTEXT([external])

AC_CONFIG_FILES([Makefile \
           contrib/Makefile \
           doc/Makefile \
           gnulib/lib/Makefile \
           man/Makefile \
           po/Makefile.in \
           src/Makefile \
           tests/Makefile])
AC_OUTPUT

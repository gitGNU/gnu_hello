dnl Process this file with autoconf to produce a configure script.
AC_INIT([GNU Hello], [2.9.90], [bug-hello@gnu.org])
AM_INIT_AUTOMAKE([check-news dist-bzip2 readme-alpha])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SRCDIR([src/hello.c])

# Minimum Autoconf version required.
AC_PREREQ(2.59)

dnl Checks for programs.
# We need a C compiler.
AC_PROG_CC

# GNU help2man creates man pages from --help output; in many cases, this
# is sufficient, and obviates the need to maintain man pages separately.
AM_MISSING_PROG(HELP2MAN, help2man)

dnl Checks for header files.
AC_HEADER_STDC([])
AC_CHECK_HEADERS([string.h fcntl.h sys/file.h sys/param.h])

# i18n support from GNU gettext.
AM_GNU_GETTEXT_VERSION([0.14.3])
AM_GNU_GETTEXT()

AC_CONFIG_FILES([Makefile \
           contrib/Makefile \
           doc/Makefile \
           intl/Makefile \
	   m4/Makefile \
           man/Makefile \
           po/Makefile.in \
           src/Makefile \
           tests/Makefile])
AC_OUTPUT

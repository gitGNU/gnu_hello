dnl Process this file with autoconf to produce a configure script.
AC_INIT(hello, 2.1.2, bug-gnu-hello@gnu.org)
AC_CONFIG_SRCDIR([src/hello.c])

AC_PREREQ(2.52)

AC_SUBST(ke_PRE, 2.1.1)
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER(config.h)
dnl AC_SUBST(PACKAGE_BUGREPORT, bug-gnu-hello@gnu.org)
dnl AH_TEMPLATE(PACKAGE_BUGREPORT)
dnl AC_DEFINE_UNQUOTED(PACKAGE_BUGREPORT, "$PACKAGE_BUGREPORT")

dnl Checks for programs.
AC_PROG_CC
AC_ISC_POSIX

dnl Check for build configuration.
dnl AM_PROG_LIBTOOL

dnl Checks for libraries.

dnl Checks for header files.
AC_HEADER_STDC([])
AC_CHECK_HEADERS([string.h fcntl.h sys/file.h sys/param.h])

dnl Checks for library functions.
AC_FUNC_ALLOCA

dnl Check for st_blksize in struct stat
AC_DIAGNOSE([obsolete],[AC_STRUCT_ST_BLKSIZE:
        your code should no longer depend upon `HAVE_ST_BLKSIZE', but
        `HAVE_STRUCT_STAT_ST_BLKSIZE'.  Remove this warning and
        the `AC_DEFINE' when you adjust the code.])
AC_CHECK_MEMBERS([struct stat.st_blksize],[AC_DEFINE(HAVE_ST_BLKSIZE, 1,
                            [Define if your `struct stat' has
                             `st_blksize'.  Deprecated, use
                             `HAVE_STRUCT_STAT_ST_BLKSIZE' instead.])])


dnl internationalization macros
AM_GNU_GETTEXT
AM_GNU_GETTEXT_VERSION

dnl for help2man
AC_CHECK_PROG(PERL, perl, perl)

AC_CONFIG_FILES([Makefile contrib/Makefile doc/Makefile  intl/Makefile \
           man/Makefile po/Makefile.in \
	   m4/Makefile \
           src/Makefile tests/Makefile])
AC_CONFIG_COMMANDS([default],[[ echo timestamp > stamp-h ]],[[]])
AC_OUTPUT

dnl configure.in ends here

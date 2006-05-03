/* hello.c -- print a greeting message and exit.
   Copyright (C) 1992, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
   2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <errno.h>

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifndef errno
extern int errno;
#endif

#ifdef	STDC_HEADERS
#include <stdlib.h>
#else	/* Not STDC_HEADERS */
extern void exit ();
extern char *malloc ();
#endif	/* STDC_HEADERS */

#ifdef	HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#ifdef HAVE_FCNTL_H
#include <fcntl.h>
#endif
#ifdef HAVE_SYS_FILE_H
#include <sys/file.h>
#endif

#ifdef HAVE_SYS_PARAM_H
/* To possibly get the definition of DEV_BSIZE. */
#include <sys/param.h>
#endif
#include "system.h"

struct option longopts[] =
{
  { "greeting", required_argument, NULL, 'g' },
  { "help", no_argument, NULL, 'h' },
  { "next-generation", no_argument, NULL, 'n' },
  { "traditional", no_argument, NULL, 't' },
  { "version", no_argument, NULL, 'v' },
  { NULL, 0, NULL, 0 }
};

extern char version[];

static char *progname;

int
main (argc, argv)
     int argc;
     char *argv[];
{
  int optc;
  int h = 0, v = 0, t = 0, n = 0, lose = 0, z = 0;
  char *greeting = NULL;

  progname = argv[0];

#ifdef HAVE_SETLOCALE
  /* Set locale via LC_ALL.  */
  setlocale (LC_ALL, "");
#endif

#if ENABLE_NLS
  /* Set the text message domain.  */
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif

  while ((optc = getopt_long (argc, argv, "g:hntv", longopts, (int *) 0))
         != EOF)
    switch (optc)
      {
      case 'v':
        v = 1;
        break;
      case 'g':
        greeting = optarg;
        break;
      case 'h':
        h = 1;
        break;
      case 'n':
        n = 1;
        break;
      case 't':
        t = 1;
        break;
      default:
        lose = 1;
        break;
      }
  
  if (optind == argc - 1 && strcmp (argv[optind], "sailor") == 0)
    z = 1;
  else if (lose || optind < argc)
    {
      /* Print error message and exit.  */
      if (optind < argc)
        fputs (_("Too many arguments\n"), stderr);
      fprintf (stderr, _("Try `%s --help' for more information.\n"), 
               progname);
      exit (1);
    }

  /* `help' should come first.  If `help' is requested, ignore the other
     options. */
  if (h)
    {
      /* Print help info and exit.  */
      /* TRANSLATORS: --help output 1
         no-wrap */
      fputs (_("\
GNU hello, THE greeting printing program.\n"), stdout);
      printf ("\n");
      /* TRANSLATORS: --help output 2
         no-wrap */
      printf (_("\
Usage: %s [OPTION]\n"), progname);

      printf ("\n");
      /* TRANSLATORS: --help output 3 : options 1/2
         no-wrap */
      fputs (_("\
  -h, --help          display this help and exit\n\
  -v, --version       display version information and exit\n"), stdout);

      printf ("\n");
      /* TRANSLATORS: --help output 4 : options 2/2
         no-wrap */
      fputs (_("\
  -t, --traditional       use traditional greeting format\n\
  -n, --next-generation   use next-generation greeting format\n\
  -g, --greeting=TEXT     use TEXT as the greeting message\n"), stdout);

      printf ("\n");
      /* TRANSLATORS: --help output 5 (end)
         TRANSLATORS, please don't forget to add the contact address for
         your translation!
         no-wrap */
      printf (_("\
Report bugs to <%s>.\n"), PACKAGE_BUGREPORT);

      exit (0);
    }

  if (v)
    {
      /* Print version number.  */
      printf ("hello - GNU %s %s\n", PACKAGE, version);
      /* xgettext: no-wrap */
      puts ("");
      printf (_("\
Copyright (C) %s Free Software Foundation, Inc.\n\
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A\n\
PARTICULAR PURPOSE.  You may redistribute copies of GNU %s\n\
under the terms of the GNU General Public License.\n\
For more information about these matters, see the file named COPYING.\n"),
              "2005", PACKAGE);
      exit (0);
    }
  else if (z)
    puts (_("Nothing happens here."));

  else
    /* Print greeting message and exit. */
    {
      if (t)
        printf (_("hello, world\n"));
      else if (n)
	/* TRANSLATORS: Use box drawing characters or other fancy stuff
	   if your encoding (e.g., UTF-8) allows it.  If done so add the
	   following note, please:

	   [Note: For best viewing results use a UTF-8 locale, please.]
	*/
	printf (_("\
+---------------+\n\
| Hello, world! |\n\
+---------------+\n\
"));
      else
        {
          if (!greeting)
            greeting = _("Hello, world!");
          puts (greeting);
        }
    }

  exit (0);
}

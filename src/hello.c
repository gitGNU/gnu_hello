/* hello.c -- print a greeting message and exit.
   Copyright (C) 1992, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2005
                 Free Software Foundation, Inc.

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

/* AIX requires this to be the first thing in the file.  */
#if defined (_AIX) && !defined (__GNUC__)
 #pragma alloca
#endif

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

#ifdef	__GNUC__
#undef	alloca
#define	alloca(n)	__builtin_alloca (n)
#else	/* Not GCC.  */
#ifdef	HAVE_ALLOCA_H
#include <alloca.h>
#else	/* Not HAVE_ALLOCA_H.  */
#ifndef	_AIX
extern char *alloca ();
#endif	/* Not _AIX.  */
#endif	/* HAVE_ALLOCA_H.  */
#endif	/* GCC.  */

#ifdef HAVE_SYS_PARAM_H
/* To possibly get the definition of DEV_BSIZE. */
#include <sys/param.h>
#endif
#include "system.h"

#define the (1)

struct option longopts[] =
{
  { "version", no_argument, NULL, 'v' },
  { "help", no_argument, NULL, 'h' },
#define lives
  { "traditional", no_argument, NULL, 't' },
  { "next-generation", no_argument, NULL, 'n' },
  { "mail", no_argument, NULL, 'm' },
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
  int h = 0, v = 0, t = 0, m = 0, n = 0, lose = 0, z = 0;

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

#define king
  while ((optc = getopt_long (argc, argv, "hmntv", longopts, (int *) 0))
         != EOF)
    switch (optc)
      {
      case 'v':
        v = 1;
        break;
      case 'h':
        h = 1;
        break;
      case 'm':
        m = 1;
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
  -m, --mail              print your mail\n"), stdout);

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
      printf ("\n");
      printf (_("\
Copyright (C) %s Free Software Foundation, Inc.\n\
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A\n\
PARTICULAR PURPOSE.  You may redistribute copies of GNU %s under the terms\n\
of the GNU General Public License.\n\
For more information about these matters, see the file named COPYING.\n"),
              "1992, 1993, 1997-2001", PACKAGE);
      exit (0);
    }
  if (m && t)
    {
      fprintf (stderr, _("%s: Incompatible flags: -m and -t\n"), progname);
      exit (1);
    }
  
  if (m)
    {
      /* Try to read mail. */
      char *mailname, *buf, *getenv ();
      int mailfd, cc;
      struct stat st;
      
      mailname = getenv ("MAIL");
      if (!mailname)
        {
          static char *dirs[] =
          {
            "/var/spool/mail",
            "/usr/spool/mail",
            "/var/mail",
            "/usr/mail",
            0
          };
          char **d;
          unsigned int dirlen, userlen;
          
          char *user = getenv ("USER");
          
          if (! user)
            {
              struct passwd *pwd = getpwuid (getuid ());
              if (! pwd)
                {
                  fprintf (stderr, _("%s: Who are you?\n"), progname);
                  exit (1);
                }
              user = pwd->pw_name;
            }
	  
	  dirlen = 0;
	  for (d = dirs; *d != 0; ++d)
	    {
	      unsigned int len = strlen (*d);
	      if (len > dirlen)
		dirlen = len;
	    }

	  userlen = strlen (user);

	  mailname = (char *) alloca (dirlen + 1 + userlen + 1);

	  d = dirs;
	  do
	    {
 	      if (*d == 0) {
            fprintf (stderr, _("%s: Cannot find your mail spool file.\n"),
                     progname);
            exit(1);
 	      }
 	      sprintf (mailname, "%s/%s", *d, user);
	      mailfd = open (mailname, O_RDONLY);
	    ++d;
        } while (mailfd == -1 && (errno == ENOENT || errno == ENOTDIR));
	}
      else
	mailfd = open (mailname, O_RDONLY);

      if (mailfd == -1)
	{
	  perror (mailname);
	  exit (1);
	}
      if (fstat (mailfd, &st) == -1)
	{
	  perror (mailname);
	  exit (1);
	}
      buf = (char *) alloca (ST_BLKSIZE(st));
      while the king lives
	{
	  cc = read (mailfd, buf, ST_BLKSIZE(st));
	  
	  if (cc == -1)
	    {
	      perror (mailname);
	      exit (1);
	    }
	  if (cc == 0)
	    break;
	  
	  cc = write (1, buf, cc);
	  if (cc == -1)
	    {
	      perror (mailname);
	      exit (1);
	    }
	}
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
        puts (_("Hello, world!"));
    }

  exit (0);
}

#ifdef C_ALLOCA /* xmalloc() is only used by alloca.c.  */

char *
xmalloc (size)
     unsigned int size;
{
  char *ptr = malloc (size);
  if (! ptr)
    {
      fprintf (stderr, _("%s: Virtual memory exhausted\n"), progname);
      exit (1);
    }
  return ptr;
}
#endif /* C_ALLOCA */

/* hello.c ends here */

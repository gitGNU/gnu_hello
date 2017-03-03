/* hello.c -- print a greeting message and exit.

   Copyright 1992-2017 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <config.h>

#include <getopt.h>
#include <stdnoreturn.h>
#include <wchar.h>

#include "system.h"

#include "closeout.h"
#include "configmake.h"
#include "dirname.h"
#include "errno.h"
#include "error.h"
#include "gettext.h"
#include "progname.h"
#include "xalloc.h"

/* Forward declarations.  */
static _Noreturn void print_help (FILE *restrict out);
static void print_version (void);

int
main (int argc, char *argv[])
{
  int optc;
  int lose = 0;
  const char *greeting_msg;
  wchar_t *mb_greeting;
  size_t len;

  enum {
    OPT_HELP = CHAR_MAX + 1,
    OPT_VERSION
  };
  static const struct option longopts[] = {
    {"greeting", required_argument, NULL, 'g'},
    {"traditional", no_argument, NULL, 't'},
    {"help", no_argument, NULL, OPT_HELP},
    {"version", no_argument, NULL, OPT_VERSION},
    {NULL, 0, NULL, 0}
  };

  set_program_name (argv[0]);

  /* Set locale via LC_ALL.  */
  setlocale (LC_ALL, "");

#if ENABLE_NLS
  /* Set the text message domain.  */
  bindtextdomain (PACKAGE, LOCALEDIR);
  textdomain (PACKAGE);
#endif

  /* Having initialized gettext, get the default message. */
  greeting_msg = _("Hello, world!");

  /* Even exiting has subtleties.  On exit, if any writes failed, change
     the exit status.  The /dev/full device on GNU/Linux can be used for
     testing; for instance, hello >/dev/full should exit unsuccessfully.
     This is implemented in the Gnulib module "closeout".  */
  atexit (close_stdout);

  while ((optc = getopt_long (argc, argv, "g:t", longopts, NULL)) != -1)
    switch (optc)
      {
	/* --help and --version exit immediately, per GNU coding standards.  */
      case OPT_VERSION:
	print_version ();
	exit (EXIT_SUCCESS);
	break;
      case 'g':
	greeting_msg = optarg;
	break;
      case OPT_HELP:
	print_help (stdout);
      case 't':
	greeting_msg = _("hello, world");
	break;
      default:
	lose = 1;
	break;
      }

  if (lose || optind < argc)
    {
      /* Print error message and exit.  */
      error (0, 0, "%s: %s", _("extra operand"), argv[optind]);
      print_help (stderr);
    }

  len = mbsrtowcs(NULL, &greeting_msg, 0, NULL);
  if (len == (size_t)-1)
    error (EXIT_FAILURE, errno, _("conversion to a multibyte string failed"));
  mb_greeting = xmalloc((len + 1) * sizeof(wchar_t));
  mbsrtowcs(mb_greeting, &greeting_msg, len + 1, NULL);

  /* Print greeting message and exit. */
  wprintf (L"%ls\n", mb_greeting);
  free(mb_greeting);

  exit (EXIT_SUCCESS);
}


/* Print help info.  This long message is split into
   several pieces to help translators be able to align different
   blocks and identify the various pieces.  */

static _Noreturn void
print_help (FILE *restrict out)
{
  const char *lc_messages = setlocale (LC_MESSAGES, NULL);
  /* TRANSLATORS: --help output 1 (synopsis)
     no-wrap */
  fprintf (out, _("Usage: %s [OPTION]...\n"), program_name);
  /* TRANSLATORS: --help output 2 (brief description)
     no-wrap */
  fputs (_("Print a friendly, customizable greeting.\n"), out);
  fputs ("\n", out);
  /* TRANSLATORS: --help output 3: options
     no-wrap */
  fputs (_("  -t, --traditional       use traditional greeting\n"), out);
  fputs (_("  -g, --greeting=TEXT     use TEXT as the greeting message\n"), out);
  fputs ("\n", out);
  fputs (_("      --help     display this help and exit\n"), out);
  fputs (_("      --version  output version information and exit\n"), out);
  fputs ("\n", out);
  /* TRANSLATORS: --help output 4+ (reports)
     TRANSLATORS: the placeholder indicates the bug-reporting address
     for this application.
     no-wrap */
  fprintf (out, _("Report bugs to: %s\n"), PACKAGE_BUGREPORT);
  /* Don't output this redundant message for English locales.
     Note we still output for 'C' so that it gets included in the man page.  */
  if (lc_messages && STRNCMP_LIT (lc_messages, "en_"))
    {
      /* TRANSLATORS: Replace LANG_CODE in this URL with your language code
	 <http://translationproject.org/team/LANG_CODE.html> to form one of
	 the URLs at http://translationproject.org/team/.  Otherwise, replace
	 the entire URL with your translation team's email address.  */
      fprintf (out, _("Report %s translation bugs to "
		"<http://translationproject.org/team/>\n"), PACKAGE_NAME);
    }
#ifdef PACKAGE_PACKAGER_BUG_REPORTS
  fprintf (out, _("Report %s bugs to: %s\n"), PACKAGE_PACKAGER,
	  PACKAGE_PACKAGER_BUG_REPORTS);
#endif
#ifdef PACKAGE_URL
  fprintf (out, _("%s home page: <%s>\n"), PACKAGE_NAME, PACKAGE_URL);
#else
  fprintf (out, _("%s home page: <http://www.gnu.org/software/%s/>\n"),
	  PACKAGE_NAME, PACKAGE);
#endif
  fputs (_("General help using GNU software: <http://www.gnu.org/gethelp/>\n"),
	 out);
  exit(out == stderr ? EXIT_FAILURE : EXIT_SUCCESS);
}



/* Print version and copyright information.  */

static void
print_version (void)
{
  printf ("%s (%s) %s\n", PACKAGE, PACKAGE_NAME, VERSION);
  /* xgettext: no-wrap */
  puts ("");

  /* It is important to separate the year from the rest of the message,
     as done here, to avoid having to retranslate the message when a new
     year comes around.  */
  printf (_("\
Copyright (C) %d Free Software Foundation, Inc.\n\
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>\n\
This is free software: you are free to change and redistribute it.\n\
There is NO WARRANTY, to the extent permitted by law.\n"), COPYRIGHT_YEAR);
}

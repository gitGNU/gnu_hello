## Process this file with automake to produce Makefile.in

# man_aux = $(man_MANS:.1=.x)
man_MANS = hello.1
HELP2MAN = help2man
noinst_SCRIPTS = $(HELP2MAN)

EXTRA_DIST = $(man_MANS) $(noinst_SCRIPTS) # $(man_aux)
CLEANFILES = $(man_MANS)
#  Makefile.maint GNUmakefile Makefile.summ

hello.1: ../src/hello $(HELP2MAN)
	-$(PERL) $(srcdir)/$(HELP2MAN) --name="Friendly Greeting Program" \
	  ../src/hello >$@

MAINTAINERCLEANFILES = $(man_MANS)

# man/Makefile.am ends here

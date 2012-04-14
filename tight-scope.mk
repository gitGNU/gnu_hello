# TS-start

# Most functions should have static scope.
# Any that don't must be marked with 'extern', but 'main'
# and 'usage' are exceptions: they're always extern, but
# do not need to be marked.  Symbols matching '__.*' are
# reserved by the compiler, so are automatically excluded below.
_gl_TS_unmarked_extern_functions ?= main usage
_gl_TS_function_match ?= /^(?:$(_gl_TS_extern)) +.*?(\S+) *\(/

# If your project uses a macro like "XTERN", then put
# the following in cfg.mk to override this default:
# export _gl_TS_extern = extern|XTERN
_gl_TS_extern ?= extern

# The second nm|grep checks for file-scope variables with 'extern' scope.
# Without gnulib's progname module, you might put program_name here.
# Symbols matching '__.*' are reserved by the compiler,
# so are automatically excluded below.
_gl_TS_unmarked_extern_vars ?=

# NOTE: the _match variables are perl expressions -- not mere regular
# expressions -- so that you can extend them to match other patterns
# and easily extract matched variable names.
# For example, if your project declares some global variables via
# a macro like this: GLOBAL(type, var_name, initializer), then you
# can override this definition to automatically extract those names:
# export _gl_TS_var_match = \
#   /^(?:$(_gl_TS_extern)) .*?\**(\w+)(\[.*?\])?;/ || /\bGLOBAL\(.*?,\s*(.*?),/
_gl_TS_var_match ?= /^(?:$(_gl_TS_extern)) .*?(\w+)(\[.*?\])?;/

# The names of object files in (or relative to) $(_gl_TS_dir).
_gl_TS_obj_files ?= *.$(OBJEXT)

# Files in which to search for the one-line style extern declarations.
# $(_gl_TS_dir)-relative.
_gl_TS_headers ?= $(noinst_HEADERS)

.PHONY: _gl_tight_scope
_gl_tight_scope: $(bin_PROGRAMS)
	t=exceptions-$$$$;						\
	trap 's=$$?; rm -f $$t; exit $$s' 0;				\
	for sig in 1 2 3 13 15; do					\
	  eval "trap 'v=`expr $$sig + 128`; (exit $$v); exit $$v' $$sig"; \
	done;								\
	src=`for f in $(SOURCES); do					\
	       test -f $$f && d= || d=$(srcdir)/; echo $$d$$f; done`;	\
	hdr=`for f in $(_gl_TS_headers); do				\
	       test -f $$f && d= || d=$(srcdir)/; echo $$d$$f; done`;	\
	( printf '^%s$$\n' '__.*' $(_gl_TS_unmarked_extern_functions);	\
	  grep -h -A1 '^extern .*[^;]$$' $$src				\
	    | grep -vE '^(extern |--)' | sed 's/ .*//';			\
	  perl -lne							\
	     '$(_gl_TS_function_match) and print "^$$1\$$"' $$hdr;	\
	) | sort -u > $$t;						\
	nm -e $(_gl_TS_obj_files) | sed -n 's/.* T //p'|grep -Ev -f $$t	\
	  && { echo the above functions should have static scope >&2;	\
	       exit 1; } || : ;						\
	( printf '^%s$$\n' '__.*' $(_gl_TS_unmarked_extern_vars);	\
	  perl -lne '$(_gl_TS_var_match) and print "^$$1\$$"' $$hdr *.h	\
	) | sort -u > $$t;						\
	nm -e $(_gl_TS_obj_files) | sed -n 's/.* [BCDGRS] //p'		\
            | sort -u | grep -Ev -f $$t					\
	  && { echo the above variables should have static scope >&2;	\
	       exit 1; } || :
# TS-end

/* system.h
   Copyright (C) 1996 Free Software Foundation, Inc. */

/* Include sys/types.h before this file.  */

/* Get or fake the disk device blocksize.
   Usually defined by sys/param.h (if at all).  */
#if !defined(DEV_BSIZE) && defined(BSIZE)
#define DEV_BSIZE BSIZE
#endif
#if !defined(DEV_BSIZE) && defined(BBSIZE) /* SGI */
#define DEV_BSIZE BBSIZE
#endif
#ifndef DEV_BSIZE
#define DEV_BSIZE 4096
#endif

/* Extract or fake data from a `struct stat'.
   ST_BLKSIZE: Optimal I/O blocksize for the file, in bytes. */
#ifndef HAVE_ST_BLKSIZE
# define ST_BLKSIZE(statbuf) DEV_BSIZE
#else /* HAVE_ST_BLKSIZE */
/* Some systems, like Sequents, return st_blksize of 0 on pipes. */
# define ST_BLKSIZE(statbuf) ((statbuf).st_blksize > 0 \
                              ? (statbuf).st_blksize : DEV_BSIZE)
#endif /* HAVE_ST_BLKSIZE */

/* system.h ends here */

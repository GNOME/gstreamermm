#!/bin/sh
MAKE=`which gnumake`
if test ! -x "$MAKE" ; then MAKE=`which gmake` ; fi
if test ! -x "$MAKE" ; then MAKE=`which make` ; fi
HAVE_GNU_MAKE=`$MAKE --version|grep -c "Free Software Foundation"`

if test "$HAVE_GNU_MAKE" != "1"; then 
echo !!!! ERROR: You need GNU make to build from svn!; 
echo !!!! $MAKE is not GNU make;
exit 1; 
fi

echo Found GNU Make at $MAKE ... good.

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

PKG_NAME="gstreamermm"

(test -f $srcdir/configure.ac \
  && test -d $srcdir/gst/src \
  && test -d $srcdir/gst/gstmm) || {
    echo -n "**Error**: Directory "\`$srcdir\'" does not look like the"
    echo " top-level $PKG_NAME directory"
    exit 1
}



echo "Adding libtools."
libtoolize --automake

echo "Building macros."
aclocal -I scripts $ACLOCAL_FLAGS

#echo "Building config header."
#autoheader

echo "Building makefiles."
automake   --add-missing

echo "Building configure."
autoconf

rm -f config.cache

if test -z "$AUTOGEN_SUBDIR_MODE"; then

    echo "Running configure."
    ./configure --enable-maintainer-mode "$@"
    echo
    echo 'run "make"'
    echo
else
    echo
    echo 'run "./configure ; make"'
    echo
fi


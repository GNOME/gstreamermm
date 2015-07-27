#! /bin/sh -e
test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

mm-common-prepare --force --copy "$srcdir"
touch gstreamer/src/plugin_filelist.am
autoreconf --force --install --verbose "$srcdir"
test -n "$NOCONFIGURE" || "$srcdir/configure" --enable-maintainer-mode "$@"

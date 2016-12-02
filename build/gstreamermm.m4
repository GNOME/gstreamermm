## Copyright 2015 The gstreamermm Development Team
##
## This library is free software: you can redistribute it and/or modify it
## under the terms of the GNU Lesser General Public License as published
## by the Free Software Foundation, either version 2.1 of the License,
## or (at your option) any later version.
##
## This library is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.


## Arguments: 
##  * $1 - var_name (e.g. GSTREAMERMM_GL, GSTREAMERMM_NET)
##  * $2 - pkg-config module name sufix (e.g. gl, net)
##  * $3 - var_name (e.g. gl, plugins_bad) - can't contain underscores
##  * $4 - dependency conditions
## Macro creates two variables:
##  * ENABLE_$1 - true, if module will be enabled, false otherwise
##  * gstmm_enable_$2 - "yes", if module will be enabled, "no" otherwise
## Module $2 can be explicitly disabled, using --disable-$2 argument
## in ./configure script.
AC_DEFUN([FIND_GST_MODULE], 
[
  PKG_CHECK_MODULES($1, gstreamer-[$2]-1.0 >= GSTREAMERMM_VERSION,
                  [gstmm_enable_$3=yes], [gstmm_enable_$3=no])

  AC_ARG_ENABLE($2,
              AS_HELP_STRING([--enable-$2], [Enable gstreamer-$2 library]))
  tst=x$4
  if test $tst = "x"; then :
    tst=xyes
  fi

  gstmm_$3_version=$(pkg-config --modversion gstreamer-[$2]-1.0)
  AS_IF([test "x$enable_$3" != "xyes" || test "$tst" != xyes], [gstmm_enable_$3=no])
  AM_CONDITIONAL([ENABLE_$1], [test "x$gstmm_enable_$3" = xyes])
  AS_IF([test "x$gstmm_enable_$3" = xyes], [AC_DEFINE(ENABLE_$1, [], [Enable gstreamer-$2 module])])
])

## Arguments:
##  * $1 - modules name variable (e.g. GSTREAMERMM_PLUGINS_BAD_MODULES)
##  * $2 - module name (e.g. gstreamer-gl-1.0)
##  * $3 - conditional variable (must equals to yes)
AC_DEFUN([ADD_MODULE_CONDITIONALLY],
[
  AS_IF([test x$3 = xyes], [
    AC_SUBST([$1], ["$$1 $2"])
  ])
])

## Arguments:
##  * $1 - output file
##  * $2 - plugins list
## Generates list of plug-ins. If USE_MAINTAINER_MODE defined, macro also
## checks for the existence of the plug-ins. Note that this check doesn't
## work when cross-compiling.  That isn't much of a problem though since
## it only applies in maintainer-mode.
AC_DEFUN([GENERATE_PLUGINS_LIST_FILE],
[
  # clear plugins file once per file
  m4_ifndef([$1], [
    printf "plugins_hg = \n" > $1
    m4_define([$1], [yes])
  ])

  printf "plugins_hg += " >> $1

  AS_IF([test "x$USE_MAINTAINER_MODE" != xno],
  [
    gstmm_toolsdir=`$PKG_CONFIG --variable=toolsdir gstreamer-1.0 2>&AS_MESSAGE_LOG_FD`
    AC_PATH_PROGS([GST_INSPECT], [gst-inspect-1.0],,
                  [$gstmm_toolsdir$PATH_SEPARATOR$PATH])

    AC_MSG_CHECKING([the existance of required plug-ins.])
  ])
  for gstmm_plugin_def in $2
  do
    gstmm_hg_name=`[expr "X$gstmm_plugin_def" : 'X\(.*\)|.*|.*$' 2>&]AS_MESSAGE_LOG_FD`
    printf "$gstmm_hg_name.hg " >> $1
    AS_IF([test "x$USE_MAINTAINER_MODE" != xno],
    [
      # Extract plugin name and run gst-inspect to check whether the plugin
      # is installed on the build system.
      gstmm_plugin_name=`[expr "X$gstmm_plugin_def" : 'X.*|\(.*\)|.*$' 2>&]AS_MESSAGE_LOG_FD`
      AS_IF([$GST_INSPECT "$gstmm_plugin_name" >/dev/null 2>&AS_MESSAGE_LOG_FD],,
            [AC_MSG_FAILURE([[The gstreamer plug-in '$gstmm_plugin_name' does not exist.
If you built gst-plugins-base from source code then you might need to
install the appropriate -dev or -devel packages or enable experimental
plugins before rebuilding gst-plugins-base.]])])
    ])
  done
  AS_IF([test "x$USE_MAINTAINER_MODE" != xno],
  [
    AC_MSG_RESULT([All required plug-ins found.])
  ])
  printf "\n" >> $1
])


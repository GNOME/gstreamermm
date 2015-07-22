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
              AS_HELP_STRING([--disable-$2], [Disable gstreamer-$2 library]))
  tst=x$4
  if test $tst = "x"; then :
    tst=xyes
  fi

  gstmm_$3_version=v$(pkg-config --modversion gstreamer-[$2]-1.0)

  AS_IF([test "x$enable_$3" = "xno" || test "$tst" != xyes], [gstmm_enable_$3=no])
  AM_CONDITIONAL([ENABLE_$1], [test "x$gstmm_enable_$3" = xyes])
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


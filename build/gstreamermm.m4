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
## Macro creates two variables:
##  * ENABLE_$1 - true, if module will be enabled, false otherwise
##  * gstmm_enable_$2 - "yes", if module will be enabled, "no" otherwise
## Module $2 can be explicitly disabled, using --disable-$2 argument
## in ./configure script.
AC_DEFUN([FIND_GST_MODULE], 
[

  PKG_CHECK_MODULES($1, gstreamer-[$2]-1.0 >= GSTREAMERMM_VERSION,
                  [gstmm_enable_$2=yes], [gstmm_enable_$2=no])
  
  AC_ARG_ENABLE($2,
              AS_HELP_STRING([--disable-$2], [Disable gstreamer-$2 library]))
  
  AS_IF([test "x$enable_$2" = "xno"], [gstmm_enable_$2=no])
  AM_CONDITIONAL([ENABLE_$1], [test "x$gstmm_enable_$2" = xyes])
])
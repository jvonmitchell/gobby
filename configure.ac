#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([gobby], [0.6.0], [crew@0x539.de])
AM_INIT_AUTOMAKE(1.9 check-news foreign)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES])
AC_CONFIG_SRCDIR([code/window.hpp])
AC_CONFIG_HEADER([code/features.hpp])

# Extract host information.
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AM_PROG_CC_C_O
AC_CACHE_SAVE

###################################
# Check for Win32
###################################

AC_MSG_CHECKING([whether to enable WIN32 specific flags])
case "$host_os" in
*mingw*)
        win32=true
        AC_MSG_RESULT([yes])
  AC_CHECK_TOOL(WINDRES, windres)
  ;;
*)
        win32=false
        AC_MSG_RESULT([no])
  ;;
esac
AM_CONDITIONAL(WIN32, test x$win32 = xtrue)

required_libs="libxml++-2.6 glibmm-2.4 >= 2.40.0 giomm-2.4 >= 2.40.0 libgsasl >= 0.2.21 gtkmm-3.0 >= 3.6.0 gtksourceview-3.0 >= 3.0.0"

###################################
# Check for Mac OS X
###################################

# Check if we are running on OS X, for special link handling.
if test "x$build_vendor" = "xapple" ; then
  AC_DEFINE([PLATFORM_OSX], 1, [Define whether we are running on Mac OS X.])

  # Check whether we are running the native quartz backend
  target=`pkg-config --variable=targets gtk+-3.0`

  # If so use ige-mac-integration
  if test "$target" = "quartz" ; then
    AC_DEFINE([PLATFORM_OSX_NATIVE], 1, [Define whether we are running on
                                         Mac OS X with the quartz GDK target])
    required_libs="$required_libs ige-mac-integration"
  fi
fi
AC_CACHE_SAVE

###################################
# Check for libraries.
###################################

PKG_CHECK_MODULES([gobby], [$required_libs])
PKG_CHECK_MODULES([infinote], [libinfinity-0.7 libinftext-0.7 libinfgtk-0.7 libinftextgtk-0.7])
AC_CACHE_SAVE

###################################
# Glib i18n/gettext support.
###################################
ALL_LINGUAS="`grep -v '^#' "$srcdir/po/LINGUAS" | tr '\n' ' '`"
AM_GLIB_GNU_GETTEXT
AM_GLIB_DEFINE_LOCALEDIR(GOBBY_LOCALEDIR)
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=gobby05
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], ["${GETTEXT_PACKAGE}"], [gettext domain])

###################################
# Help file building
###################################
GNOME_DOC_INIT([0.9.0],,
  [AC_MSG_WARN([[gnome-doc-utils not found: documentation will not be built.]])])

# AC_DEFINE(GOBBY_CONFIGDIR, [".gobby-0.5"],
#           [where to store Gobby's config files,
#            relative to the user's home directory])

###################################
# Output
###################################

AC_OUTPUT([
  Makefile
    m4/Makefile
    po/Makefile.in

    code/Makefile
      code/util/Makefile
      code/core/Makefile
      code/dialogs/Makefile
      code/operations/Makefile
      code/commands/Makefile
        code/commands/file-tasks/Makefile

    icons/Makefile
      icons/hicolor/Makefile
        icons/hicolor/48x48/Makefile
          icons/hicolor/48x48/apps/Makefile
          icons/hicolor/48x48/actions/Makefile
          icons/hicolor/48x48/status/Makefile
        icons/hicolor/scalable/Makefile
          icons/hicolor/scalable/apps/Makefile
          icons/hicolor/scalable/actions/Makefile
          icons/hicolor/scalable/status/Makefile
      icons/HighContrastLargePrint/Makefile
        icons/HighContrastLargePrint/48x48/Makefile
          icons/HighContrastLargePrint/48x48/apps/Makefile
          icons/HighContrastLargePrint/48x48/actions/Makefile
        icons/HighContrastLargePrint/scalable/Makefile
          icons/HighContrastLargePrint/scalable/apps/Makefile
          icons/HighContrastLargePrint/scalable/actions/Makefile
      icons/HighContrastLargePrintInverse/Makefile
        icons/HighContrastLargePrintInverse/48x48/Makefile
          icons/HighContrastLargePrintInverse/48x48/apps/Makefile
          icons/HighContrastLargePrintInverse/48x48/actions/Makefile
        icons/HighContrastLargePrintInverse/scalable/Makefile
          icons/HighContrastLargePrintInverse/scalable/apps/Makefile
          icons/HighContrastLargePrintInverse/scalable/actions/Makefile

    help/Makefile

    win32/Makefile
])

# vim:set et sw=2 ts=2:

# https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
# https://autotools.io/autoconf/arguments.html
# https://github.com/aria2/aria2/issues/120#issuecomment-23083616
dnl https://stackoverflow.com/a/3377708/6828099

AC_INIT([shell], [0.1], [alex.shell@senorcontento.com])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--disable-readline], [Disable Readline Support]))

AS_IF([test "x$enable_readline" != "xno"], [
  AM_CFLAGS="$AM_CFLAGS -lreadline -DREADLINE_LIBRARY"
])

AC_SUBST(AM_CFLAGS)
AM_INIT_AUTOMAKE([subdir-objects])
AC_PROG_CC
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

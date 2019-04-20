# https://thoughtbot.com/blog/the-magic-behind-configure-make-make-install
# https://autotools.io/autoconf/arguments.html
# https://github.com/aria2/aria2/issues/120#issuecomment-23083616
# https://autotools.io/autoconf/finding.html
dnl https://stackoverflow.com/a/3377708/6828099

AC_INIT([shell], [0.1], [alex.shell@senorcontento.com])

AC_ARG_ENABLE([readline],
    AS_HELP_STRING([--disable-readline], [Disable Readline Support]))

AS_IF([test "x$enable_readline" != "xno"], [
  AC_CHECK_HEADERS([readline/readline.h readline/history.h],
        [readline_found_headers=yes; break;])

  AS_IF([test "x$readline_found_headers" != "xyes"],
        [AC_MSG_ERROR([Unable to Find Readline Headers])])

  AM_CFLAGS="$AM_CFLAGS -lreadline -DREADLINE_LIBRARY"
])

AC_SUBST(AM_CFLAGS)
AM_INIT_AUTOMAKE([subdir-objects])
AC_PROG_CC
AC_CONFIG_FILES([Makefile])
AC_OUTPUT

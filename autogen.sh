# Bootstrap script for Open Endless SDK
# Run this script on a clean source checkout to get ready for building.

FILE_MUST_EXIST=endless/endless.h
POT_FILE=po/eos-sdk.pot

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.
olddir=`pwd`

cd $srcdir
test -f $FILE_MUST_EXIST || {
    echo "You must run this script in the top-level checkout directory"
    exit 1
}

# Install our commit message script if a git repo
if [ -d .git ]; then
    cp commit-msg .git/hooks/commit-msg
    chmod +x .git/hooks/commit-msg
fi

# GNU gettext automake support doesn't get along with git
# https://bugzilla.gnome.org/show_bug.cgi?id=661128
touch -t 200001010000 $POT_FILE

# NOCONFIGURE is used by gnome-common
if test -z "$NOCONFIGURE"; then
    echo "This script will run ./configure automatically. If you wish to pass "
    echo "any arguments to it, please specify them on the $0 "
    echo "command line. To disable this behavior, have NOCONFIGURE=1 in your "
    echo "environment."
fi

am_ver=`automake --version | grep -m 1 -o '[^ ]*$'`
# Autmake 1.11.x doesn't grasp the 'serial-tests' option. Add a m4 file which
# defines HAS_SERIAL_TESTS_OPTION so we can keep our configure.ac forward
# compatible
case $am_ver in
    *\ 1.11*|*\ 1.12*) ;;
    *) echo 'm4_define([HAS_SERIAL_TESTS_OPTION], [1])';;
esac > m4/serial-tests.m4

# Run the actual tools to prepare the clean checkout
gtkdocize || exit $?
autoreconf -fi || exit $?
rm -f po/Makevars.template

cd "$olddir"
test -n "$NOCONFIGURE" || "./configure" "$@"

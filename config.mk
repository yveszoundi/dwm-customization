# dwm version
VERSION = 6.3

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# Linking
FREETYPELIBS = -lfontconfig -lXft

# compiler and linker
CC = cc

UNAME != uname

include config.mk.${UNAME}


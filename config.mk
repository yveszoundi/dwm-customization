# dwm version
VERSION = 6.1

# Customize below to fit your system

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man

# compiler and linker
CC = cc

UNAME != uname

include config.mk.${UNAME}

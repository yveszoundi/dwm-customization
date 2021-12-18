# dwm version
VERSION = 6.1

# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
UNAME:=`uname`

# Xinerama
XINERAMALIBS  = -lXinerama
XINERAMAFLAGS = -DXINERAMA

# freetype
FREETYPELIBS = -lfontconfig -lXft

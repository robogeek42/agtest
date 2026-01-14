# agtest
Agon compiler agondev test program using multiple sub-dirs

AgDev compiler can make use of EXTRA_C_SOURCES to compile
sources not in the same tree as main.c

agondev does not have this, so the current method is just
to link the sources from the top directory

The simple test applications also highlight some of the key differences
in the APIs available to the different build-chains.

**Important**
Use make to choose the compile chain and set links (see below)

## To Use
1. set the build chain to either AgDev or agondev:

`make set_agdev`
or 
`make set_agondev`

2. Build the applications in subdirs app1 and app2
`make`

3. Install to the emulator sdcard
`make install`

Note: change FAE_HOME in Makefile to your FAB Agon Emulator directory

## Top Makefile Usage
Makefile in the top directory calls make in subdirs

`make set_agondev` - sets build-chain to agondev
`make set_agdev` - sets build-chain to AgDev
`make clean` - cleans subdirs and final binaries in top directory
`make install` - calls install in subdirs
`make` - makes apps in subdirs



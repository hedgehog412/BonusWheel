#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac
  make -f /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac
  make -f /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac
  make -f /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac
  make -f /Users/jyunjeon/Desktop/CocosTest/proj.ios_mac/mac/CMakeScripts/ReRunCMake.make
fi


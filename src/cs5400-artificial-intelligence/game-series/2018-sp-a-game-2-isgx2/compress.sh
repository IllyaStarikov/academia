#!/bin/bash

# This script compresses the directory specified as an argument into a .zuo
# You may change this to compress the directory into a .tar or .tar.gz if you prefer one of these compression formats more (for some reason).
# Don't forget you are limited to 150MB compressed filesize.

LANG=$1

cd $LANG
zip -r $LANG.zip .
mv $LANG.zp ../

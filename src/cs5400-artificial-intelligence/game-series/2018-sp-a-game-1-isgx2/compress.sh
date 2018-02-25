#!/bin/bash

# This script compresses the directory specified as an argument into a .tar.gz
# You may change this to compress the directory into a .zip or .tar if you prefer one of these compression formats more (for some reason).
# Don't forget you are limited to 150MB compressed filesize.

LANG=$1

tar czf $LANG.tar.gz -C $LANG .

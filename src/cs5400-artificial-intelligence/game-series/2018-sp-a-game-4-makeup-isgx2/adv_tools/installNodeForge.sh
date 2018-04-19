#!/bin/bash

mkdir ~/node
mkdir ~/node/install
cd ~/node/install
curl http://nodejs.org/dist/node-latest.tar.gz | tar xz --strip-components=1
./configure --prefix=~/node
make install
curl https://www.npmjs.org/install.sh | sh
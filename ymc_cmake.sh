#!/bin/bash

BUILD_DIR="BUILD"
SRC_DIR="src"

cd ${BUILD_DIR}
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../${SRC_DIR} -DUSE_SYSTEM_CURL=ON -DCURL_CA_BUNDLE="/etc/ssl/certs/ca-certificates.crt"
mv compile_commands.json ..
cd ..


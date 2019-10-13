#!/bin/bash
direnv allow
python3 -m venv .venv
FOLDER=${PWD}
source .venv/bin/activate 
git submodule update --init --recursive
cd ${ESP32_ROOT}/tools/
python get.py
cd $FOLDER
pip install -r requirements.txt 
sed -i "1 i\export HOME=${FOLDER}\n" .envrc
direnv allow

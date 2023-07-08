#!/bin/bash

_template=${2:-"temp"}

if [[ -d $1 ]]; then
  echo "The $1 already exsist."
  exit 1
fi

cp -R temp/$_template $1

if [[ $OSTYPE == 'darwin'* ]] ;then
  sed -i '' "1 s/^.*$/set(TARGET $1)/" "$1/CMakeLists.txt"
else
  sed -i "1 s/^.*$/set(TARGET $1)/" "$1/CMakeLists.txt"
fi

echo "add_subdirectory($1)" >> CMakeLists.txt



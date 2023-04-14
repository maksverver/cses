#!/bin/sh

set -e

if [ -z "$1" ]; then
  echo "Usage: $0 <name>"
  exit 1
fi

name=$1

if ! echo "$name" | grep -Eq '^[a-zA-Z][a-zA-Z0-9_-]*$'
then
  echo "Invalid name!"
  exit 1
fi

source=${name}.cc

if [ -e "$source" ]; then
  echo "$source already exists!"
  exit 1
fi

cp -n template.cc "$source"

sed -e "/^SORTING_AND_SEARCHING_PROBLEMS=/s/$/ $name/" -i Makefile

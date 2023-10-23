#!/bin/sh

set -e

function print_categories() {
  sed -n 's/_PROBLEMS=.*//p' Makefile
}

if [ $# != 2 ]; then
  echo "Usage: $0 <category> <name>"
  echo "Categories:"
  print_categories
  exit 1
fi

category=$1
name=$2

if ! grep -q "^${category}_PROBLEMS=" Makefile; then
  echo "Invalid category! Categories:"
  print_categories
fi

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

# Update the section name after completing a section.
sed -e "/^${category}_PROBLEMS=/s/$/ $name/" -i Makefile

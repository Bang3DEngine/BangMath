#!/bin/bash

cd "$(dirname "$0")"

hash clang-format 2>/dev/null
if [ $? -ne 0 ]
then
    echo "SETUP ERROR: no clang-format executable found, or it is not executable. Please install it!"
    exit 1
fi

fileList=""
if [ "$#" -ne 0 ]
then
    fileList="$@"
else
    fileList=$(find ./include/ -type f)
fi

for f in $fileList
do
    echo "Formatting '$f'..."
    clang-format -i $f
done

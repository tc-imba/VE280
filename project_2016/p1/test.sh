#!/bin/bash

echo "Welcome to VE280 auto-testing, by tc-imba"
path="$(dirname $(readlink -f $0))"

# Test whether the source exists
if [ ! -n "$1" ]; then
    echo "Usage: test.sh <source_path>"
    exit
fi
src="$path/$1"
if [ ! -d "$src" ]; then
    echo "Error: the source doesn't exist in $src"
    exit
fi

# Remove the previous files and create new ones
echo "Removing old files ..."
temp="$path/test.temp"
rm -rf "$temp"

echo "Copying new files ..."
cp -r "$path/test-cases/" "$temp"

# Copy project files
cp "$src/p1.cpp" "$temp/"
echo "Temp files created, ready to compile"

# Compile project files
cd "$temp"
make
echo "Compiled, begin to test"

# Testing
testNum=26
acNum=0
for i in `seq 0 $(($testNum-1))`; do
    ./p1 <$i.in >$i.test
    diff $i.test $i.out
    if [ $? = 0 ]; then
        echo "testcase $i: Accepted"
        acNum=$((acNum+1))
    else
        echo "testcase $i: Wrong Answer"
    fi
done

echo "Accepted $acNum/$testNum"
if [ "$acNum" = "$testNum" ]; then
    echo "All test cases accepted"
else
    echo "Some test cases failed, work hard and try again!"
fi 

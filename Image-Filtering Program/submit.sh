#!/bin/bash

echo "Trying to compile assignment3.cpp ..."
clang++ -std=c++11 -c assignment3.cpp > /dev/null 2>&1
error=$?
if [ $error = 0 ]; then
	tar -czf assignment3.tar.gz assignment3.cpp assignment3.h
	echo "Success! You may now submit assignment3.tar.gz to Moodle."
else
	echo "ERROR: Compilation failed, you are not ready to submit."
fi

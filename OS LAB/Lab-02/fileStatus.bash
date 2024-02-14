#!/usr/bin/env bash

dir_path="/home/samdani1412/Desktop/Semester4/OS LAB/Lab-02"

cd "$dir_path" || exit

find . -type f \( -name '*.c' -o -name '*.cpp' \) -exec sh -c '
	echo "File: {}"
	echo "Size: $(du -h {} | cut -f1)"
	echo "Lines: $(wc -l < {})"
	echo ""
	' \;

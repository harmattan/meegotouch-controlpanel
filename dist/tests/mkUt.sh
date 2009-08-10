#! /bin/bash

# TEST

dcp_src=../src

findPath() {
	find $dcp_src -name "$1"
}

sourceForHeader() {
	source=`echo $1 | sed 's/\.h$/\.cpp/'`
	if [ -f "$source" ]; then
		echo "$source"
	fi
}

toLowerCase() {
	echo $1 | tr [A-Z] [a-z]
}

toUpperCase() {
	echo $1 | tr [a-z] [A-Z]
}

# finds the included headers in a cpp/header file, 
# adds the relevant source files also
# usage: $1 - the header file name without path
findIncludedHeaders() {
	headerName=$(basename "$1")
	headerPath=$1
	sourcePath=$(sourceForHeader $headerPath)
	cat "$headerPath" "$sourcePath" 2>/dev/null | grep '#include "' | 
		sed 's/#include "//' | sed 's/".*$//' | grep -v "$headerName"
}

findIncludedHeadersRecursive() {
	findIncludedHeaders "$1" | while read filename; do
		path=$(findPath $filename)
		if [ -n "$path" ]; then
			echo "$path"
			findIncludedHeadersRecursive "$path"
		fi
	done
}


printProjectFile() {
	tmpFile=/tmp/finddeps.txt

	findIncludedHeadersRecursive "$baseHeaderPath" | 
		sort -u >$tmpFile

	# initial:
	echo "include(../common_top.pri)"
	echo "TARGET = ut_$baseclassname"
	echo

	# find the dependpaths:
	echo "DEPENDPATH += \\"
	cat $tmpFile | while read path; do
		if [ -n "$path" ]; then
			echo "           ../`dirname $path` \\"
		fi
	done | sort -u

	# find the headers:
	echo
	echo "HEADERS += $baseHeaderPath \\"
	cat $tmpFile | while read line; do
		echo "           ../$line \\"
	done | sort -u

	# find the cpps:
	echo
	echo "SOURCES += $baseSourcePath \\"
	cat $tmpFile | while read line; do
		source=`echo $line | sed 's/\.h$/\.cpp/'`
		if [ -e "$source" ]; then
			echo "           ../$source \\"
		fi
	done | sort -u

	echo
	echo "include(../common_bottom.pri)"
}


if [ $# != 1 ]; then
	echo "Usage: $0 <ClassName>"
	exit 1
fi

baseClassName=$1
baseclassname=$(toLowerCase $baseClassName)
baseHeaderPath=$(findPath ${baseclassname}.h)
baseSourcePath=$(sourceForHeader $baseHeaderPath)

dir=ut_$baseclassname
mkdir "$dir" || exit 1
printProjectFile >$dir/$dir.pro

cp template/*.cpp $dir/$dir.cpp
cp template/*.h $dir/$dir.h


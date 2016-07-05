#!/bin/sh

cxx="clang++"
cc="clang"
cxxflags="\
	-std=c++1z\
	-stdlib=libc++\
	-pipe\
	-pedantic\
	-march=native\
	-Wall\
	-fdiagnostics-format=vi\
	-fno-elide-type\
	-fvisibility=hidden\
	-fPIC"
cmakeargs=" \
	-DCMAKE_BUILD_TYPE=Custom \
	-DCMAKE_VERBOSE_MAKEFILE=OFF "

if [ $# == 0 ] || [ $1 == "debug" ]; then
	echo 'Generating debug build'
	cxxflags="${cxxflags} -O2 -g3"
	cmakeargs="${cmakeargs} -DBUILD_DEBUG=ON"
	if [[ ! -d build/debug ]]; then
		mkdir -pv build/debug
	fi
	cd build/debug
elif [ $1 == "release" ]; then
	echo 'Generating release build'
	cxxflags="${cxxflags} -O2 -g0"
	cmakeargs="${cmakeargs} -DBUILD_DEBUG=OFF"
	if [[ ! -d build/release ]]; then
		mkdir -pv build/release
	fi
	cd build/release
else
	echo "Wrong argument. Should be release or debug"
	exit 1
fi

yes | rm -rf *

CXX=${CXX:=${cxx}} \
CC=${CC:=${cc}} \
CXXFLAGS=${CXXFLAGS:=${cxxflags}} \
cmake ${cmakeargs} ../../cmake/

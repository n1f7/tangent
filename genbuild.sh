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

if [[ $# -eq 1 ]] || [[ $1 -eq "debug" ]]; then
	cxxflags="${cxxflags} -O2 -g3"
	cmakeargs="${cmakeargs} -DBUILD_DEBUG=ON"
	if [[ ! -d build/debug ]]; then
		mkdir -pv build/debug
	fi
	cd build/debug
elif [[ $1 -eq "release" ]]; then
	cxxflags="${cxxflags} -O2 -g0"
	cmakeargs="${cmakeargs} -DBUILD_DEBUG=OFF"
	if [[ ! -d build/release ]]; then
		mkdir -pv build/release
	fi
	cd build/release
else
	echo "Wrong argument should be release or debug"
	exit 1
fi

yes | rm -rvf *

CXX=${CXX:=${cxx}} \
CC=${CC:=${cc}} \
CXXFLAGS=${CXXFLAGS:=${cxxflags}} \
cmake ${cmakeargs} ../../cmake/

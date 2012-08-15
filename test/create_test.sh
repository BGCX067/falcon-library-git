#/bin/sh
USAGE='[dirname] category'

cd `dirname $0`

[ $# = 0 ] && echo $0 $USAGE && exit 1

if [ $# = 2 ];then
	d=${1%%\/}
	shift 1
	defbase=$d'_'
	cmakelist=$d/CMakeLists.txt
	if [ ! -d $d ];then
		[ -e $d ] && echo $d is not directory && exit 3
		mkdir $d
		echo "include(../../CMakeDefinitions.txt)
include_directories(.. ../..)
" > $cmakelist
	fi
else
	d=
	defbase=
	cmakelist=CMakeLists.txt
fi

h="$d/$1.hpp"
s="$d/$1.cpp"
( [ -e $h ] && echo $h exists || [ -e $s ] && echo $s exists ) && exit 2

def=$defbase$1
#with bash: ${def^^*}
def=_FALCON_TEST_$(echo $def | tr -s '[a-z]' '[A-Z]')_HPP

echo "#ifndef $def
#define $def

void $1_test();

#endif" > $h

echo "#include <falcon/$h>
#include \"test.hpp\"
#include \"$1.hpp\"

void $1_test()
{

}

FALCON_GROUP_TEST_TO_MAIN($1_test)" > $s

echo create_exec_test"($1)" >> $cmakelist

exit 0

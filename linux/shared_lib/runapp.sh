if [ $# -lt 1 ]; then
    echo "less argument"
    exit 1
fi

#echo "arguments:$* $0 $1"
target=$1
curdir=`pwd`
echo $curdir
LD_LIBRARY_PATH=$curdir:LD_LIBRARY_PATH
export LD_LIBRARY_PATH
./$target

exit 0

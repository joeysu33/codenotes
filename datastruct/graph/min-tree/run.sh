target=$1
target=$(echo $target | sed -n 's/\.c//p')
gcc -o $target $target.c common.c
if [ $? -ne 0 ]; then
    echo "compile errors"
    exit 1
fi
./$target

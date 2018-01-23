if [ $# -lt 1 ]; then
    echo "argument count is less then 1."
    exit 1
fi

target=$1
targetc=$target.c

if [[ ! -f "$targetc" ]]; then
    echo "target is not file :$targetc"
    exit 2
fi

run_mode=0
declare -i run_mode
for i in $*; do
    if [[ $i == "-run" || $i == "--run=true" ]]; then
        run_mode=1
    fi
done

#echo "runmode=$run_mode"
#echo "target=$target"
gcc -g -o $target $targetc sort_common.c
if [[ $run_mode -eq 1 && $? -eq 0 ]]; then
    ./$target
fi
exit 0

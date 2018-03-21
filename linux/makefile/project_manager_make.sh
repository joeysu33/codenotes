#!/bin/bash

#function () { [return int] ;}
#return [0~255]
#default value is last return value of cmd
ROOT_DIR=testdir
CREAT_MKFILE=1
function creatdir() {
    ok=0
    if [ $# -ne 1 ]; then
        return 1;
    fi

    if [ ! -d $1 ]; then
        if `mkdir -p $1` ; then
            ok=1
            echo "mkdir $1"
        else
            echo "mkdir error: $1"
        fi
    else
        ok=1
    fi

    if [ ${ok} -eq 1 ];then
        if [ ${CREAT_MKFILE} -eq 1 ];then
            mkfile="$1/Makefile"
            if [ ! -f "$mkfile" ];then
                echo "all:" >> ${mkfile}
                echo -e "\techo testmakefile" >> ${mkfile}
            fi
        fi
    fi
}

for i in db codec ui ;do
    j="${ROOT_DIR}/include/$i"
    creatdir $j
    k="$ROOT_DIR/lib/$i"
    creatdir $k
done

creatdir "${ROOT_DIR}/app/player"
creatdir "${ROOT_DIR}/doc"


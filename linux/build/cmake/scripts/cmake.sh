#!/bin/bash

k=0
for i in `ls *.txt`; do
    ((k+=1))
    echo "$k: Processing $i ...";
    cmake -P $i
    echo ""
done

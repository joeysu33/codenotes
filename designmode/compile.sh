if [ $# -ne 1 ]; then
    echo "arguments lost"
    exit 1
fi
target=$1
g++ -std=c++11 -g -o $target  $target.cpp


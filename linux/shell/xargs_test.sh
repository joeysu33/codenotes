if [ -d tmp ]; then
    if `rm -fr tmp`; then
        exit 1
    fi
fi

mkdir tmp
cd tmp
mkdir  a b c d test logdir shdir
touch "one space.log"
touch logdir/{1..10}.log
touch shdir/{1..5}.sh
echo "then second sh the second line " > shdir/2.sh

exit 0

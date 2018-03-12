filename=$1
if [ ! -f $filename ];then
    exit 1
fi

echo "filename=$filename"
while read line ;do
    echo "git clone $line"
    git clone $line
    if [ $? -eq 0 ]; then
        echo "error:git clone $line"
    fi
done < $filename

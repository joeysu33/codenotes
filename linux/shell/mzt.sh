#! /bin/bash

last=`ls *.jpg | sed -n '$p'`
host=http://mm.chinasareview.com/wp-content/uploads/
year=2017
y=0
m=0
d=0
index=0
url=''
dir=''
file=''

#continue to download...
if [ "${last}" != "" ];then
    y=${last:0:4}
    m=${last:6:2}
    d=${last:12:2}
    if [ ${y} -gt ${year} ];then
        year=${y}
    fi
fi
echo "year=$y month=$m day=$d"

for month in {1..12}; do
    if [ ${m} -ge ${month} ];then
        continue
    fi
    for day in {1..31}; do
        index=1
        until [ ${index} -gt 99 ]; do
            dir=`printf "%da/%02d/%02d" ${year} ${month} ${day}`
            file=`printf "%s/%02d.jpg" ${dir} ${index}`
            url=`printf "%s%s" ${host} ${file}`
            file=${file//\//_}

            #if [ ! -d "${dir}" ];then
            #    mkdir -p "${dir}"
            #fi

            if [ ! -f ${file} ]; then
                wget -P ${dir} -O ${file} ${url}
                if [ $? -ne 0 ]; then
                    break;
                fi
            fi

            ((index += 1))
            sleep 0.1
        done
    done
done

exit 0

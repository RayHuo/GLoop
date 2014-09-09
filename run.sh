#! /bin/bash

# cd IO/pealGraph/
# for file in `ls`
# do
# 	if[ ${file} != "hc.lp" ]; then
# 		echo > ${file}
# 	fi
# done

# cd ../../
./a.out

cd IO/output/
rm -rf ./*

cd ..
> count_out.txt

cd ./input/

for fileName in `ls`
do
    argus="IO/input/"
	argus=${argus}${fileName}
    # echo $argus
    cd ../../
    ./gloop $argus
    cd IO/input/
done

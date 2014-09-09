#! /bin/bash

cd IO/output/
rm -rf ./*

cd ../input/

for fileName in `ls`
do
    argus="IO/input/"
	argus=${argus}${fileName}
    # echo $argus
    cd ../../
    ./gloop $argus
    cd IO/input/
done

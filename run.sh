#! /bin/bash

cd IO/input/
argus=""
for fileName in `ls | xargs realpath`
do
	argus=${argus}${fileName}" "
done

cd ../output/
rm -rf ./*

cd ../../
# echo $argus
./gloop $argus

#! /bin/bash

cd ./files/ 
argus=""
for fileName in `ls | xargs realpath`
do
	argus=${argus}${fileName}" "
done

#echo $argus
cd ..
./a.out $argus
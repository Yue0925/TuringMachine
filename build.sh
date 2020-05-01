#!/bin/bash
make
make clean
make ./bin/myTuring
chmod u+x ./bin/myTuring
make clean

touch ./test/test.log

cat ./test/test | while read line
do
	echo "#################################" >> ./test/test.log
	echo "./bin/myTuring" $line >> ./test/test.log
	./bin/myTuring $line >> ./test/test.log
done
#on peut redéfinir cout dans log fichier, mais cerr rest dans terminal
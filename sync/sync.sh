#!/bin/sh


echo $$ >> file1.txt

while [ ! -f "file2.txt" ]
do
	sleep 0
done

if [ $(cat file1.txt) = $(cat file2.txt) ]
then
	exit 0
fi

exit 1

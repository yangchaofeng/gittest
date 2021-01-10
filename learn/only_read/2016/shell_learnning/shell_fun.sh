#!/bin/bash

is_directory()
{
 DIR_NAME=$1 
 if [ ! -d $DIR_NAME ]; 
	then 
		echo "$DIR_NAME not exist ,return 1"
		return 1 
 else
	echo "$DIR_NAME exist ,return 0" 
	return 0 
 fi
}

for DIR in "$@"; do
	if is_directory "$DIR" # $DIR 是给函数 传递参数
		then 
			 echo "$DIR exist" 
		:
	else 
		echo "$DIR doesn't exist. Creating it now..." 
		mkdir $DIR 
		if [ $? -ne 0 ]; 
			then echo "Cannot create directory $DIR" 
			exit 1 
		fi 
	fi
done

#!/bin/bash


COUNTER=0
echo "Enter password:"
read TRY
while [ "$TRY" != "secret"  ] ; do
        COUNTER=$(($COUNTER+1))
	echo "Sorry,enter times is $COUNTER ,Please try again"
        if [ $COUNTER -ge 5  ];then
                exit
        fi
	read TRY
done

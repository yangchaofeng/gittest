#!/bin/bash

pwd=`pwd`
if [ -f "$pwd/test.sh" ]
then echo "$pwd/test.sh is a file"
else echo "$pwd/test.sh is NOT a file"
fi

if :; then echo "if : always true"; fi

if [ 0  ]; then echo "if [ 0  ] always true"; fi


echo "Is it morning? Please answer yes or no."
read YES_OR_NO
if [ "$YES_OR_NO" = "yes"  ] ; then 
   echo "Good morning!"
elif [ "$YES_OR_NO" = "no"  ] ; then
   echo "Good afternoon!"
else
   echo "Soory,$YES_OR_NO not recognized.ENTER yse or no"
fi



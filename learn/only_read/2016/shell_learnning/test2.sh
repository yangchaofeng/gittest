#!/bin/bash

echo this is in test2.sh
echo $VARNAME

#用unset命令可以删除已定义的环境变量或本地变量
unset VARNAME  
echo $VARNAME

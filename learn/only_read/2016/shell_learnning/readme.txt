
1. Shell的历史

Shell脚本是解释执行的，不需要编译，Shell程序从脚本中一行一行读取并执行这些命令，相当于一个用户把脚本中的命令一行一行敲到Shell提示符下执行.

由于历史原因，UNIX系统上有很多种Shell

bash（Bourne Again Shell）：由GNU开发的Shell，主要目标是与POSIX标准保持一致，同时兼顾对sh的兼容,在Linux系统上/bin/sh往往是指向/bin/bash的符号链接.

文件/etc/shells给出了系统中所有已知（不一定已安装）的Shell.

用户的默认Shell设置在/etc/passwd文件中，例如下面这行对用户yang的设置:
yang:x:500:500:yang:/home/yang:/bin/bash

2. Shell的基本语法

变量

按照惯例，Shell变量由全大写字母加下划线组成，有两种类型的Shell变量：
环境变量
本地变量


文件名代换

* 		匹配 0 个或多个任意字符
? 		匹配一个任意字符
[若干字符]      匹配方括号中任意一个字符的一次出现

命令代换




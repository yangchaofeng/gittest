#! /bin/bash


echo '$0='$0  '$1='$1 '$2='$2  '$3='$3 '$@='$@  '$?='$? '$#='$#

#本地变量
VARNAME=value1 
echo $VARNAME #在定义变量时不用$，取变量值时要用$

#用export命令可以把本地变量导出为环境变量，定义和导出环境变量通常可以一步完成
export VARNAME=value2

./test2.sh
#事实上Shell变量的值都是字符串
#Shell变量不需要先定义后使用，如果对一个没有定义的变量取值，则值为空字符串



#文件名代换
#*               匹配 0 个或多个任意字符
#?               匹配一个任意字符
#[若干字符]      匹配方括号中任意一个字符的一次出现



#命令代换
DATE=`date`
#命令代换也可以用$()表示
DATE2=$(date)
echo $DATE $DATE2



#算术代换：$(())
VAR=45
echo $(($VAR+3))  #$(())中只能用+-*/和()运算符，并且只能做整数运算。


#转义字符\
#和C语言类似，\在Shell中被用作转义字符，用于去除紧跟其后的单个字符的特殊意义（回车除外）
echo \\
echo $VARNAME
echo \$VARNAME


#单引号
#单引号用于保持引号内所有字符的字面值，即使引号内的\和回车也不例外
echo '$SHELL'
echo 'ABC\\'


#双引号
#双引号用于保持引号内所有字符的字面值（回车也不例外），但以下情况除外：
#$加变量名可以取变量的值
#反引号仍表示命令替换
#\$表示$的字面值
#\`表示`的字面值
#\"表示"的字面值
#\\表示\的字面值
#除以上情况之外，在其它字符前面的\无特殊含义，只表示字面值
echo "$SHELL"
echo "`date`"
echo "\\"



#测试命令
#命令test或[可以测试一个条件是否成立，如果测试结果为真，则该命令的Exit Status为0，如果测试结果为假，则命令的Exit Status为1
#[ -d DIR ]如果DIR存在并且是一个目录则为真
#[ -f FILE]如果FILE存在且是一个普通文件则为真
#[ -zSTRING ]如果STRING的长度为零则为真
#[ -nSTRING ]如果STRING的长度非零则为真
#[ STRING1= STRING2]如果两个字符串相同则为真
#[ STRING1!= STRING2]如果字符串不相同则为真
#[ ARG1 OPARG2 ]ARG1和ARG2应该是整数或者取值为整数的变量，
#OP是-eq（等于）
#-ne（不等于）
#-lt（小于）
#-le（小于等于）
#-gt（大于）
#-ge（大于等于）之中的一个

#带与、或、非的测试命令
#[ ! EXPR ]EXPR可以是上表中的任意一种测试条件，!表示逻辑反
#[ EXPR1 -a EXPR2]EXPR1和EXPR2可以是上表中的任意一种测试条件，-a表示逻辑与
#[ EXPR1 -o EXPR2]EXPR1和EXPR2可以是上表中的任意一种测试条件，-o表示逻辑或

VAR=abc
[ -f test2.sh -a $VAR = 'abc' ]
echo $?


unset VAR
[ -f test2.sh -a $VAR = 'abc' ]
[ -f test2.sh -a "$VAR" = 'abc' ]
echo $?
VAR=abc
[ -f test2.sh -a "$VAR" = 'abc' ]
echo $?




#位置参数和特殊变量
#$0		相当于C语言main函数的argv[0]
#$1、$2...	这些称为位置参数（Positional Parameter），相当于C语言main函数的argv[1]、argv[2]...
#$#		相当于C语言main函数的argc - 1，注意这里的#后面不表示注释
#$@		表示参数列表"$1" "$2" ...，例如可以用在for循环中的in后面。
#$?		上一条命令的Exit Status
#$$		当前Shell的进程号
echo '$0='$0  '$1='$1 '$2='$2  '$3='$3 '$@='$@  '$?='$?

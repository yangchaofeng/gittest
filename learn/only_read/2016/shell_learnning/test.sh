#! /bin/bash


echo '$0='$0  '$1='$1 '$2='$2  '$3='$3 '$@='$@  '$?='$? '$#='$#

#���ر���
VARNAME=value1 
echo $VARNAME #�ڶ������ʱ����$��ȡ����ֵʱҪ��$

#��export������԰ѱ��ر�������Ϊ��������������͵�����������ͨ������һ�����
export VARNAME=value2

./test2.sh
#��ʵ��Shell������ֵ�����ַ���
#Shell��������Ҫ�ȶ����ʹ�ã������һ��û�ж���ı���ȡֵ����ֵΪ���ַ���



#�ļ�������
#*               ƥ�� 0 �����������ַ�
#?               ƥ��һ�������ַ�
#[�����ַ�]      ƥ�䷽����������һ���ַ���һ�γ���



#�������
DATE=`date`
#�������Ҳ������$()��ʾ
DATE2=$(date)
echo $DATE $DATE2



#����������$(())
VAR=45
echo $(($VAR+3))  #$(())��ֻ����+-*/��()�����������ֻ�����������㡣


#ת���ַ�\
#��C�������ƣ�\��Shell�б�����ת���ַ�������ȥ���������ĵ����ַ����������壨�س����⣩
echo \\
echo $VARNAME
echo \$VARNAME


#������
#���������ڱ��������������ַ�������ֵ����ʹ�����ڵ�\�ͻس�Ҳ������
echo '$SHELL'
echo 'ABC\\'


#˫����
#˫�������ڱ��������������ַ�������ֵ���س�Ҳ�����⣩��������������⣺
#$�ӱ���������ȡ������ֵ
#�������Ա�ʾ�����滻
#\$��ʾ$������ֵ
#\`��ʾ`������ֵ
#\"��ʾ"������ֵ
#\\��ʾ\������ֵ
#���������֮�⣬�������ַ�ǰ���\�����⺬�壬ֻ��ʾ����ֵ
echo "$SHELL"
echo "`date`"
echo "\\"



#��������
#����test��[���Բ���һ�������Ƿ������������Խ��Ϊ�棬��������Exit StatusΪ0��������Խ��Ϊ�٣��������Exit StatusΪ1
#[ -d DIR ]���DIR���ڲ�����һ��Ŀ¼��Ϊ��
#[ -f FILE]���FILE��������һ����ͨ�ļ���Ϊ��
#[ -zSTRING ]���STRING�ĳ���Ϊ����Ϊ��
#[ -nSTRING ]���STRING�ĳ��ȷ�����Ϊ��
#[ STRING1= STRING2]��������ַ�����ͬ��Ϊ��
#[ STRING1!= STRING2]����ַ�������ͬ��Ϊ��
#[ ARG1 OPARG2 ]ARG1��ARG2Ӧ������������ȡֵΪ�����ı�����
#OP��-eq�����ڣ�
#-ne�������ڣ�
#-lt��С�ڣ�
#-le��С�ڵ��ڣ�
#-gt�����ڣ�
#-ge�����ڵ��ڣ�֮�е�һ��

#���롢�򡢷ǵĲ�������
#[ ! EXPR ]EXPR�������ϱ��е�����һ�ֲ���������!��ʾ�߼���
#[ EXPR1 -a EXPR2]EXPR1��EXPR2�������ϱ��е�����һ�ֲ���������-a��ʾ�߼���
#[ EXPR1 -o EXPR2]EXPR1��EXPR2�������ϱ��е�����һ�ֲ���������-o��ʾ�߼���

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




#λ�ò������������
#$0		�൱��C����main������argv[0]
#$1��$2...	��Щ��Ϊλ�ò�����Positional Parameter�����൱��C����main������argv[1]��argv[2]...
#$#		�൱��C����main������argc - 1��ע�������#���治��ʾע��
#$@		��ʾ�����б�"$1" "$2" ...�������������forѭ���е�in���档
#$?		��һ�������Exit Status
#$$		��ǰShell�Ľ��̺�
echo '$0='$0  '$1='$1 '$2='$2  '$3='$3 '$@='$@  '$?='$?
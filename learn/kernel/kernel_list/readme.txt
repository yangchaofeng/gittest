在Ubuntu14.04在加载自己的hello写的hello驱动时出现了如下的错误：insmod: ERROR: could not insert module kernel_hello.ko: Invalid module format

通过查看sudo dmesg -c 查看最新的内核打印信息发现如下的出错的原因：缺少retpoline



version magic '4.4.0-142-generic SMP mod_unload modversions
 
should be '4.4.0-142-generic SMP mod_unload modversions retpoline
这可能是当前内核的版本与编译模块使用的内核头文件版本不一致引起的。

解决方法：
通过修改：/usr/src/linux-headers-4.4.0-142-generic/include/generated$ 路径下的 utsrelease.h添加一段宏定义：#define RETPOLINE 1


————————————————
版权声明：本文为CSDN博主「TianJinCheng'Blog」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_44045338/article/details/109647470

run log:

4>[39952.181888] list: loading out-of-tree module taints kernel.
<4>[39953.384084] <0>student 5 name: Student5
<4>[39953.384119] <0>student 4 name: Student4
<4>[39953.384246] <0>find tmp_student->num==3  sucess
<4>[39953.384260] <0>student 3 name: Student3
<4>[39953.384263] <0>student 2 name: Student2
<4>[39953.384265] <0>student 1 name: Student1



1、计划在虚拟机上模拟recovery UI显示
先搭建一个库 makeifle 文件
计划App使用 libyanglib.so 来做显示。
2、移植开源代码recovery 中minui的 graphics.cpp resources.cpp 相关文件
编译，修改不需要支持的代码。

在编译过程中为了支持C++11，升级G++版本，
[root@yangchaofeng libminui]# g++ -v
使用内建 specs。
COLLECT_GCC=/usr/bin/g++
COLLECT_LTO_WRAPPER=/usr/local/gcc-4.7/libexec/gcc/i686-pc-linux-gnu/8.3.0/lto-wrapper
目标：i686-pc-linux-gnu
配置为：./configure --prefix=/usr/local/gcc-4.7 --enable-threads=posix --disable-checking --disable-multilib --enable-languages=c,c++ --with-gmp=/usr/local/gmp-5.0.1 --with-mpfr=/usr/local/mpfr-3.1.0 --with-mpc=/usr/local/mpc-0.9
线程模型：posix
gcc 版本 8.3.0 (GCC)

mkfont.c 
先用Bitmap（win下软件）生成图片字库tmp.png
到linux下用gimp打开然后导出为tmp.c
tmp.c中会有gimp_image结构体
tmp.c mkfont.c一起编译(gcc tmp.c mkfont.c -o tmp)
 ./tmp > font.h
这个就是font_10x18.h的来源。也是gimp_image结构体的来源！
3、在app中调用库，会报段错误，由于只是为了验证显示相关问题，故不需关注该问题
于是将相关代码移植到gr_init中
4、创建文件保存raw data数据
5、使用IrfanView查看图像数据
6、需要注意 PngHandler::PngHandler 中png 资源路径
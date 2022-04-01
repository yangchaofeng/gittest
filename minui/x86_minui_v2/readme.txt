0.登录高通开源网站https://www.codeaurora.org，选择Android for MSM，选择 GIT，https://source.codeaurora.org/quic/la  即高通手机代码开源库地址。
搜索recovery，点击 platform/bootable/recovery 。选择 aosp-new/master ，
复制浏览器上面网址： https://source.codeaurora.org/quic/la/platform/bootable/recovery/log/?h=aosp-new/master

即 https://source.codeaurora.org/quic/la/platform/bootable/recovery   branch: aosp-new/master
取代码：
  mkdir opensource
  cd opensource/
  git clone https://source.codeaurora.org/quic/la/platform/bootable/recovery -b aosp-new/master --depth=1


1、创建 libminui，复制刚才更新的recovery minui 文件下所有文件
Z:\workspace\my_github\gittest\minui\x86_minui_v2\opensource\recovery\minui 下所有文件

2、从/workspace/my_github/gittest/minui/x86_minui/libminui 目录下拷贝
Makefile  config.mk 后make

3、解决编译报错（在recovery 中找，在 http://aospxref.com/  中找、在 https://www.androidos.net.cn/android/10.0.0_r6/xref  中找）
resources.cpp:36:34: fatal error: android-base/strings.h: No such file

git clone https://source.codeaurora.org/quic/la/platform/system/libbase  -b aosp-new/master --depth=1

复制 system/libbase/include/android-base/ 下文件到 libminui/include/android-base/后，并修改包含路径为当前路径。

4、同步minui/x86_minui 下相关修改。


5、include/private/resources.h:24:17: fatal error: png.h: No such file or directory
 #include <png.h>
sudo apt-get install libpng-dev

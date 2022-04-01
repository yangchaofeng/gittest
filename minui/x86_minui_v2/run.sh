cd /home/yangchaofeng/workspace/my_github/gittest/minui/x86_minui_v2/libminui
make clean
make

cd /home/yangchaofeng/workspace/my_github/gittest/minui/x86_minui_v2
g++ -std=c++11 main.cpp libminui/libyanglib.a  -lpng -lz -ldrm

chmod 777 dataapp.raw
./a.out





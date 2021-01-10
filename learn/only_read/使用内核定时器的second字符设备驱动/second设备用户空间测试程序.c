1 #include ...
2
3 main()
4 {
5 int fd;
6 int counter = 0;
7 int old_counter = 0;
8
9 /*打开/dev/second设备文件*/
10 fd = open("/dev/second", O_RDONLY);
11 if (fd != - 1)
12 {
13 while (1)
14 {
15 read(fd,&counter, sizeof(unsigned int));//读目前经历的秒数
16 if(counter!=old_counter)
17 {
18 printf("seconds after open /dev/second :%d\n",counter);
19 old_counter = counter;
20 }
21 }
22 }
23 else
24 {
25 printf("Device open failure\n");
26 }
27 }
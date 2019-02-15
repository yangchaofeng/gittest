CFLAGS  = -Wall
#all:  en_test cn_test
all:  en_test
en_test: test.cpp
	g++ $(CFLAGS) -g  -o en_test test.cpp
cn_test: test_cn.cpp
	g++ $(CFLAGS) -g  -o cn_test test_cn.cpp
clean:
	rm -rf en_test cn_test data.raw

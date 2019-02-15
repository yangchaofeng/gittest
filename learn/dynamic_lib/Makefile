#包含配置文件
include config.mk

# 指定编译器设置
CC= gcc
CXX = g++
LD = ld
CFLAGS= -fPIC -g -shared -I.
CXXFLAGS +=
STRIP=strip
EXCFLAGS:=
EXTERLIBS:=


#$(warning, "here add the debug info")
#$(warning, "here add the debug info")
#$(info, $(TARGET_DEVICE) )

CFLAGS += $(INCLUDES)

COBJS += rand.o yanglib.o

all:lib$(LIBSNAME).so.1.0.0 lib$(LIBSNAME).so lib$(LIBSNAME).a
# 建立符号连接
lib$(LIBSNAME).so: lib$(LIBSNAME).so.1.0.0
#ln -sf $< $@
	cp -af $< $@

# 由指定的多个目标文件生成共享库
lib$(LIBSNAME).so.1.0.0:$(COBJS)
	$(CC) $(EXCFLAGS) -g -shared -Wl,-soname,lib$(LIBSNAME).so -o $@ $^  $(EXTERLIBS)
	$(STRIP) $@
# 由指定的多个目标文件生成静态库
lib$(LIBSNAME).a:$(COBJS)
	$(AR) rcs $@ $^


%.o: %.c
	$(CC) $(CFLAGS) -c $< -I.

#the scripts for clean
.PHONY: clean

clean:
	rm -rf *.so* *.o *.a *.O

install:
	cp -rf lib$(LIBSNAME).so /usr/lib/
	

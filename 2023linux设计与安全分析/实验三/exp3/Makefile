# 下面一行的"my_module"需要与上面的C源文件的名字部分保持一致
obj-m += keylogger.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean



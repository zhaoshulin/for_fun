obj-m := zsl_cache.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

defaule:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
.PHONY:clean
clean:
	rm -rf *.o *.order *.mod.c *.symvers 

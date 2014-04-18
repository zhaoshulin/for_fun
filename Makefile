obj-m := zsl_cache.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

defaule:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
	rm -rf Module.markers modles.order Modle.symvers

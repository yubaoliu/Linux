obj-m :=hello.o

KDIR := /lib/modules/4.13.0-36-generic/build
PWD := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod *.syvers *.order

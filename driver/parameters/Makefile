obj-m += hello_variable.o
obj-m += hello_array.o
obj-m += moduleParameters.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

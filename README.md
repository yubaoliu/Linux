# Linux

#Linux Driver
##Debug
dmesg

##Projects
###HelloWorld
Doc: http://www.cnblogs.com/yubao/p/8535626.html

> load module

````
    insmod hello.ko
````   
> unload module

````
    rmmod hello.ko
````

### Param_Variable
* How to run?
````
$ sudo insmod hello.ko p aram_var=100
````
* Doc
http://www.cnblogs.com/yubao/p/8536908.html

### Parame_array
````
$ sudo insmod hello.ko p aram_var=10,25,111
````
* Doc
http://www.cnblogs.com/yubao/p/8536908.html


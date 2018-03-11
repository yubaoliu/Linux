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

### Parameters
* How to run?
````
$ sudo insmod hello_variable.ko p aram_var=100
$ sudo insmod hello_array.ko p aram_var=10,25,111
$ sudo insmod moduleParameters.ko  myshort=3 myint=100   myintArray=25,67  mylong=888 mystring="yubao"
````
* Doc
http://www.cnblogs.com/yubao/p/8536908.html


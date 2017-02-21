# glibtest
This project just provide you ways to help you understand glibc by debugging or printing debug info.

#yum install glib (help you install dependency Library)
yum install glib2-2.46.2-4.el7.x86_64 -y

then
 download this project glib-2.47.92

#compile the project  source

./configure
make
make install

[root@localhost glib-2.47.92]# ls /usr/local/lib/|grep glib
glib-2.0
libglib-2.0.la
libglib-2.0.so
libglib-2.0.so.0
libglib-2.0.so.0.4792.0

#read link so
t@localhost glib-2.47.92]# readelf -d mytest/hello

Dynamic section at offset 0x1e18 contains 25 entries:
  标记        类型                         名称/值
 0x0000000000000001 (NEEDED)             共享库：[libglib-2.0.so.0]
 0x0000000000000001 (NEEDED)             共享库：[libc.so.6]
 0x000000000000000c (INIT)               0x400858
 0x000000000000000d (FINI)               0x400d04
 0x0000000000000019 (INIT_ARRAY)         0x601e00
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000001a (FINI_ARRAY)         0x601e08
 0x000000000000001c (FINI_ARRAYSZ)       8 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0x400298
 0x0000000000000005 (STRTAB)             0x400520
 0x0000000000000006 (SYMTAB)             0x4002e0
 0x000000000000000a (STRSZ)              359 (bytes)
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000003 (PLTGOT)             0x602000
 0x0000000000000002 (PLTRELSZ)           336 (bytes)
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000017 (JMPREL)             0x400708
 0x0000000000000007 (RELA)               0x4006d8
 0x0000000000000008 (RELASZ)             48 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffffe (VERNEED)            0x4006b8
 0x000000006fffffff (VERNEEDNUM)         1
 0x000000006ffffff0 (VERSYM)             0x400688
 0x0000000000000000 (NULL)               0x0
[root@localhost glib-2.47.92]# find /usr/ -name libglib-2.0.so.0
/usr/lib64/libglib-2.0.so.0
/usr/local/lib/libglib-2.0.so.0 

#mv so to running-time object dir
mv libglib-2.0.so.0.4792.0 /usr/lib64/
ln -s libglib-2.0.so.0  libglib-2.0.so.0.4792.0


#project test dir when you in project
cd mytest
#Compile
gcc test_hashtable.c -o hello $(pkg-config --cflags --libs glib-2.0)
#exec
./hello

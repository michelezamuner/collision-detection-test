To compile and run exercise 1:

```
$ make ex1
$ ./ex1
```

or, more quickly:

```
$ make run
```

To compile exercise 2:

```
g++ -oex2 ex2.cpp -lGL -lglut -lGLU
```

## Ubuntu notes

To install freeglut:

```
$ sudo apt-get install freeglut3-dev
```

If getting an error like

    Inconsistency detected by ld.so: dl-version.c: 224: _dl_check_map_versions: Assertion `needed != ((void *)0)' failed!

preload libGL static library:

```
$ export LD_PRELOAD=/usr/lib/i386-linux-gnu/mesa/libGL.so.1 make run
```

or, on x86_64 systems:

```
$ export LD_PRELOAD=/usr/lib/x86_64-linux-gnu/mesa/libGL.so.1
```

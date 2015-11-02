#mkdir

A soft in C to create directories.

Use C compilator
```
# install http://sourceforge.net/projects/mingw/files/
# https://en.wikibooks.org/wiki/A_Little_C_Primer/C_Console_IO
```

Build
```
#WIN
windres src\mkdir.rc -O coff -o src\mkdir.res
gcc src\mkdir.c -o bin\mkdir src\mkdir.res

#MACOS
gcc src/mkdir.c -o bin/mkdir
```

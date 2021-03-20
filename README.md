`loc` is a toy project, expanding on `wc` as described in KnR.  To keep this
project simple, `loc` will simply `++count` types of lines based on the file
name and/or extension.


Usage
==========
Optionally set `CC` and/or `CC_LD` if you have a preference.

```
$ meson build/debug --buildtype debug
$ meson build/release --buildtype release
$ ninja -C build/release
$ ./build/release/loc src/* ~/.profile.d/*.sh
language                        files       blank     comment        code
-------------------------------------------------------------------------
C                                   4          55          32         179
C/C++ Header                        1          13          13          58
Shell Script                       13          30           0         119
-------------------------------------------------------------------------
Total                              18          98          45         356
```

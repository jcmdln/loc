`loc` is a toy project, expanding on `wc` as described in KnR. To keep this
project simple, `loc` will simply `++count` types of lines based on the file
name and/or extension.


Usage
==========

Build
----------
`loc` is built using [Meson](https://mesonbuild.com/) which allows for simple
[debug](#Debug) and [release](#Release) builds across many platforms. For all
build types, you may optionally define the `CC` and/or `CC_LD` environment
variables if you have a preference:

```sh
$ CC=clang CC_LD=lld meson build/debug
```

### Debug (default)
```sh
$ meson build/debug
$ meson compile -C build/debug
$ ./build/debug/loc src/* ~/.profile.d/*.sh
language                        files       blank     comment        code
-------------------------------------------------------------------------
C                                   4          55          32         179
C/C++ Header                        1          13          13          58
Shell Script                       13          30           0         119
-------------------------------------------------------------------------
Total                              18          98          45         356
```

### Release
```sh
$ meson build/release --buildtype release \
    -Db_lto=true -Db_pie=true -Db_sanitize=none -Dstrip=true
$ meson compile -C build/release
$ ./build/loc src/* ~/.profile.d/*.sh
language                        files       blank     comment        code
-------------------------------------------------------------------------
C                                   4          55          32         179
C/C++ Header                        1          13          13          58
Shell Script                       13          30           0         119
-------------------------------------------------------------------------
Total                              18          98          45         356
```

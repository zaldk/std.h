# My Own C Stardard Library

Currently only for x86_64 Linux, with Windows in plans.

## USAGE

bootstrap the builder and run it:
```sh
cc -nostdlib -fno-stack-protector build.c std.linux.s -o build.exe
./build.exe
```

`std.linux.s` supplies the entry point and passes `argc`, `argv`, and `envp`
to `main`. The builder also uses `cc` to rebuild itself and the usage test.
After changing the library headers, bootstrap again with the command above.

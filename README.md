# My Own C Stardard Library

Currently only for x86_64 Linux, with Windows in plans.

## USAGE

bootstrap the builder and run it:
```sh
gcc -nostdlib -fno-stack-protector -masm=intel build.c -o build.exe
./build.exe
```

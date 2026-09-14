#!/usr/bin/env bash

flags=(-std=c89 -masm=intel -nostdlib -no-pie -fno-stack-protector -static -g)
more_flags=(-Wno-builtin-declaration-mismatch -Wall -Wextra)

gcc ${flags[*]} ${more_flags[*]} -o ./.build/program.exe entry.c && ./.build/program.exe

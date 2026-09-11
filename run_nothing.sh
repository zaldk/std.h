#!/usr/bin/env bash

clear && gcc -nostdlib -static -fno-stack-protector -no-pie nothing.c -o nothing.exe && ./nothing.exe

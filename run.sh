#!/usr/bin/env bash

clear && clang -o main.exe main.c -std=c89 -pedantic -Wall -Wextra -g && ./main.exe

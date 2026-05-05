#!/bin/bash

clang -E -C -P main.c -DJACK=1 -o Main.jack

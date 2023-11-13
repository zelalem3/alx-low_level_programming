#!/bin/bash
wget -F /tmp https://github.com/zelalem3/alx-low_level_programming/raw/master/0*18-dynameic_libraries/libgiga.so
export LD_PRELOAD=/tmp/libgiga.c

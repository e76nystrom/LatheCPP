#!/bin/bash

cd Inc
dos2unix main.h
patch <../patch/main.patch
rm -f main.h.orig  main.h.rej
cd ..

cd Drivers/CMSIS/Include
dos2unix cmsis_gcc.h
patch <../../../patch/cmsis_gcc.patch
rm -f cmsis_gcc.h.rej
ls cmsis_gcc.*
cd ../../..

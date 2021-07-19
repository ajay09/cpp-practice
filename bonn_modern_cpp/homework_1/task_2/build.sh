#!/usr/bin/env bash

echo "********************"
echo "Started building!"

echo "Creating object files"
g++ -c --std=c++17 -g -Iinclude src/subtract.cpp -o build/subtract.o
g++ -c --std=c++17 -g -Iinclude src/sum.cpp -o build/sum.o
# g++ -c --std=c++17 -g -Iinclude src/main.cpp -o results/lib/main.o
ar rcs build/libipb_arithmetic.a build/subtract.o build/sum.o 

echo "Linking object file to create executable"
g++ --std=c++17 -Iinclude -Lbuild -l subtract.o -l sum.o src/main.cpp -o build/output

echo "Moving output files to result folder"
mv build/libipb_arithmetic.a results/lib
mv build/output results/bin

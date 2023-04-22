#!/bin/bash

rm -rf dist &&

mkdir "dist" &&

g++ -o "dist/main" "src/main.cpp" -std=c++17 `sdl2-config --cflags --libs` &&

"./dist/main"

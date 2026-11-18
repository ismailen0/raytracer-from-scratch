#!/bin/zsh
# Derle, çalıştır, image.ppm üret ve aç.
# Kullanım: ./run.sh
set -e
cd "$(dirname "$0")"

clang++ -std=c++17 -O2 -Wall -o raytracer main.cpp
./raytracer > image.ppm
open image.ppm

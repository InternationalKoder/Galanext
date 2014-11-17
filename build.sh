#!/bin/bash

echo 'Building Galanext with best speed optimization...'
g++ -std=c++0x -O3 src/* -o Galanext -L shared-libs -lsfml-graphics -lsfml-window -lsfml-system
echo 'Done'

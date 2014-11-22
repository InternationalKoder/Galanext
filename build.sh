#!/bin/bash

echo 'Building Galanext with best speed optimization...'
g++ -O3 src/* -o Galanext -L shared-libs -lsfml-graphics -lsfml-window -lsfml-system
echo 'Done'

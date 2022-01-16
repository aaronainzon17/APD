#!/bin/bash

PRUEBAS=$(ls pruebasEntrega/)

make

for PROG in $PRUEBAS; do
        ./practica2 "pruebasEntrega/"$PROG        
done;

make clean

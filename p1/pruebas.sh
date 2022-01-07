#!/bin/bash

NOEDGES=$(ls testing/noEdges/)
ONECLIQUE=$(ls testing/oneClique/)
TWOCLIQUE=$(ls testing/twoClique/)
RAND=$(ls testing/random/)
CIRCLE="testing/circle.txt"

for PROG in $NOEDGES; do
        echo "testing/noEdges/"$PROG
done;

for PROG in $ONECLIQUE; do
        echo "testing/oneClique/"$PROG
done;

for PROG in $TWOCLIQUE; do
        echo "testing/twoClique/"$PROG
done;

for PROG in $RAND; do
        echo "testing/random/"$PROG
done;

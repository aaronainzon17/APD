# !/bin/bash
# To declare static Array 
arr=(30 50 100 300 500 700 900 1000 1500 3000)
  
# loops iterate through a 
# set of values until the
# list (arr) is exhausted
for i in "${arr[@]}"
do
  NAME=noEdges${i}
  echo $NAME $i
  ./generadorMatrices noEdges${i} $i
done

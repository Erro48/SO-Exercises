#!/bin/bash

counter=1
myrand=$RANDOM
while [ $((myrand%10)) -ne 2 ];do
	myrand=$RANDOM
	(( counter++ ))
done

echo "Variabile RANDOM letta in totale $counter volte ($myrand)"

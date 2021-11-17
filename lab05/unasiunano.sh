#!/bin/bash

counter=0
while read riga; do
	if [ $counter == 0 ]; then
		(( counter=1 ));
		echo $riga;
	else
		(( counter=0 ));
	fi
done

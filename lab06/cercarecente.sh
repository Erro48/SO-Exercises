#!/bin/bash

DIR="/usr/include/"

#echo `find $DIR -mindepth 2 -type f -iname "*.h"` | sed 's/ /\n/g'

younger="";
for iterator in `find /usr/include/ -mindepth 2 -type f -iname "*.h"`; do
	if [[ $younger -ot $iterator ]]; then
		younger=$iterator
	fi
done

echo "Il file modificato più recentemente è ${younger}"

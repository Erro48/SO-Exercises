#!/bin/bash

if (( $# == 1 )); then 
	OUT=""
	while read prima seconda altro; do
		if [[ -n $seconda ]]; then
			OUT="${OUT}${seconda}"
		fi
	done < $1
	echo $OUT
fi

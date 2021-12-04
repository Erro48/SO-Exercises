#!/bin/bash

while read surname2 name2 matr2 mark2; do
	if [[ $mark2 -lt 18 ]]; then
		foundFlag=0
		while read sur name matr mark; do
			if [[ $matr2 -eq $matr ]]; then
				(( foundFlag = 1 ))
			fi
		done < RisultatiProvaPratica1.txt

		if (( $foundFlag == 0 )); then
			echo "${matr2} ${surname2} ${name2} ${mark2}"
		fi
	fi
done < RisultatiProvaPratica2.txt

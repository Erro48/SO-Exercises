#!/bin/bash

DIR="/usr/include/"
for letter in [c-g]; do
	filename=${DIR}?[c-g]*
	echo ${#filename}
	if [[ ${#filename} < 18 || ${#filename} > 23 ]]; then
		echo ${filename}" ("${#filename}")"
	fi
done

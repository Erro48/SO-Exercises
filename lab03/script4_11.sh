#!/bin/bash

for file in `ls`; do echo "file is $file"; ls -dl $file; done

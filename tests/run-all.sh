#!/bin/bash
#this script is a workaround for passing arguments to all tests
ARRAY=(`ls | egrep -e "test-[^\.]+$"`)
COUNT="0"

for i in ${ARRAY[*]}; do
     "./$i" $@
    let COUNT++;
done

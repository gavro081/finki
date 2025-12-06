#!/bin/bash
        
if [ $# -eq 0 ]
then
        echo "Insert name of file!"
        exit
fi

if [ $# -gt 1 ]
then
        echo "Too many input arguments"
        exit
fi

for file in * ;
do
if [[ "$file" =~ .*\.txt$ && -r "$file" && ! -w "$file" && ! -x "$file" ]] ;
then
        cat "$file" >> "$1"
        echo " " >> "$1"
fi
done
  
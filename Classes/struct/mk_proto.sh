#!/bin/sh

file=$1
path=$(dirname $file)
# echo $0 $1  $file  $path
../ext/google/protoc -I $path --cpp_out=$path $file 
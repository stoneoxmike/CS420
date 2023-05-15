#!/bin/sh

filename=$1

touch $filename
truncate -s 0 $filename
echo 0 > $filename

#!/bin/bash
echo "1 == $1" > tmp.txt
echo "2 == $2" >> tmp.txt
echo "3 == $3" >> tmp.txt
echo "4 == $4" >> tmp.txt
echo "5 == $5" >> tmp.txt
echo "6 == $6" >> tmp.txt

cd $1
make CRYPTO_TARGET=$2 PLATFORM=$3 FIRMWAREPATH=$4 SS_VER=$5 TARGET=$6> output.txt 2>warnings.txt
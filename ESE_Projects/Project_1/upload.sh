#!/bin/bash

ip_address=192.168.7.2
username="root"

exe_file="./project"
BB_Path="/home/debian/"

if [ -f "$exe_file" ]
then
	scp -v $exe_file $username"@"$ip_address:$BB_Path
else
	echo "Creating the exe; calling make build"
	make build ARCH=bbb
	echo "Now transfering the EXE"
	scp -v $exe_file $username"@"$ip_address:$BB_Path
fi



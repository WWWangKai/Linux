#!/bin/bash
if [ $# -eq 0 ];then
echo "Usage: $0 data1...datan
exit 1
fi

function avg()
{
	max=$1
	min=$1
	sum=$1
	for i in $@
		do
			[ $max -lt $i ]
}
	

#!/bin/bash
arr[0]=1
arr[1]=1
i=0
read max
while [$arri -le max ]
do
	$arr[$i+2]=$arr[i+1]+$arr[i] 
	let i++
done
echo ${arr[$max]}

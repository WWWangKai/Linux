#!/bin/bash

#first=1
#second=1
#last=1
#i=3
#nums=$1
#while lt
#[ $i -le $nums ]
#do
#	let last=first+second
#	let first=second
#	let second=last
#	let i++;
#done

#echo $last


fib()
{
	local num=$1
	if [ $num -le 2];then
		echo 1
	    return
	fi
	local p=$(( num-1 ))
	local pp=$(( num-2 ))
	local first=$(fib $pp)
	local second=$(fib $p)
	local last=$(( first+second ))
	echo $last
}

#!/bin/bash
i=0;
str=""
lable=('|' '/' '-' '\\')
index=0
while [ $i -le 100 ]
	do
		let index%=4
		printf "\033[?251"
		printf "\033[41m"
		printf "[%-100s\033[0m  [%d%%] [%c]\r" "$str" "$i" "${lable[$index]}" 
		str+='#'
		let i++
		let index++
		sleep 0.1
	done
	printf "\n\033[?25h"

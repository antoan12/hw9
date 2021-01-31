#!/bin/bash

final_list=""
while read packet; do
	while read rule; do
		accepted_packets=""
		rule=$(echo "$rule" | sed '/^[[:blank:]]*#/d;s/#.*//' | sed 's/ //g')  #removes comments then spaces
		if [ -z "$rule" ]; then  #checks empty lines
			continue 
		fi
		IFS=',' read -r -a array <<< "$rule"  #splits by ,
	
		for field in "${array[@]}"
		do
		accepted_packets+=`echo "$packet" | ./firewall.exe "$field"`
		accepted_packets+="\n"
		done
		
		final_list+=`echo -e "${accepted_packets}" | sed '/^$/d' | sort | uniq -c  | grep -E "^ *${#array[@]} " | sed -e "s/^ *${#array[@]} //"`
		final_list+="\n"


	 done < "$1"

done

	echo -e "${final_list}" | sed '/^$/d' | tr -d ' ' | sort
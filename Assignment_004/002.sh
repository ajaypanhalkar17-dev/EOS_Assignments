#!/bin/bash


while true; do
echo "1.Date"
echo "2.Cal"
echo "3.La"
echo "4.Pwd"
echo "5.Exit"

echo -n "Enter Choice: "
read ch

if [ "$ch" -eq 1 ]; then
  date +%Y-%m-%d
elif [ "$ch" -eq 2 ]; then 
  date +%H:%M:%S
elif [ "$ch" -eq 3 ]; then
  ls -l
elif [ "$ch" -eq 4 ]; then
  pwd
elif [ "$ch" -eq 5 ]; then
 exit
fi


done





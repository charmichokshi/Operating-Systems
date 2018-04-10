clear

echo -n "Enter file name: "
read file

while true
do
clear
cat << MENU

	***Menu***

	a. Count characters, words and lines
	b. View File in a reversed order
	c. Get Frequency of a word
	d. Apply Lower case letters in place of upper case
	i. Exit

MENU

echo -n  'Enter your Choice: '
read choice

case $choice in
	
	[aA])	cat $file
			c=`cat $file | wc -m`
			w=`cat $file | wc -w`
			l=`cat $file | wc -l`
			
			echo
			echo Number of characters in $file: $c
			echo Number of words in $file: $w
			echo Number of lines in $file: $l
			sleep 5
        continue;;

	[bB])   echo Viewing file $file
			cat $file
			echo
			echo Viewing file $file in reversed order
			echo
			tac $file
			sleep 5
   		continue;;

	[cC])   cat $file
			echo
			echo -n "Enter word to find Frequency: "
			read word
			fre=`grep -o "$word" $file | wc -l`
			echo 
			echo Frequency of $word is $fre
			sleep 5
        continue;;

	[dD])	echo Viewing file $file
			cat $file
			echo
			echo Viewing file $file after changing Case
			echo
			# tr '[:upper:]' '[:lower:]' < $file
			tr A-Z a-z < $file
			echo
			sleep 5
        continue;;


	[iI])  echo 'Thank You!'
		exit;;

	*) echo 'Please enter proper Choice.'
	   sleep 5

esac
done
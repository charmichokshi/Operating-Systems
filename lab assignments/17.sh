clear
while true
do
clear
cat << MENU

	***Menu***

	1. Count the lines, words, and characters
	2. Pick up the lines containing word ‘fleas’
	3. Pick up the lines not containing word ‘fleas’
	4. Sort the file poem in line-by-line fashion
	5. Print last three lines of the file
	6. Print last lines starting from 3rd line
	7. Create two files poem and poem_new with different contents and compare them
	8. Exit

MENU

file='/home/charmi/Desktop/shell/poem.txt'

echo -n  'Enter your Choice: '
read choice

case $choice in
	
	1)	c=`cat $file | wc -m`
		w=`cat $file | wc -w`
		l=`cat $file | wc -l`
		
		echo
		echo "Number of characters: " $c
		echo "Number of words:      " $w
		echo "Number of lines:      " $l
		sleep 5
    continue;;

	2)	echo
		echo Viewing lines containing word fleas from file poem
		echo
		word='fleas'
		grep -r "$word" $file
		sleep 5
	continue;;

	3)  echo
		echo Viewing lines NOT containing word fleas from file poem
		echo
		word='fleas'
		grep -rv "$word" $file
		sleep 5
    continue;;

	4)	
while :
do
clear
cat << MENU

	***Sub Menu***

	1. Reverse normal
	2. Numeric
	3. Reverse numeric
	4. Fold high and lower case together
	5. Sort starting at (n+1) th field
	6. Exit

MENU

echo -n  'Enter your Choice: '
read c

case $c in
	
	1)	echo Sorting file poem in Reverse order...
		echo

		sort -r $file
		sleep 5
	continue;;

	2)	echo Sorting file poem in Numeric order...
		echo

		sort -n $file
		sleep 5
	continue;;

	3)	echo Sorting file poem in Reverse Numeric order...
		echo

		sort -rn $file
		sleep 5
	continue;;

	4)	echo Fold high and lower case together...
		echo

		sort -f $file
		sleep 5
	continue;;

	5)	cat $file
		echo
		echo -n "Enter field value from where you want to sort: "
		read n
		let a=`(cat $file | wc -l)`-$n
		echo
		let nn=`expr $n+1`
		echo "File after sorting from $nn th field..."
		echo
		head -n $a $file | sort
		sleep 5
	continue;;

	6)  echo 'Exiting Sub Menu'
		sleep 3
	break;;

	*)	echo 'Please enter proper Choice.'
	  	sleep 5
esac
done
;;

    5)	echo Printing last 3 lines of file poem
		echo
		
		tail -3 $file
		slepp 5
    continue;;

    6)  echo Viewing last lines starting from 3rd line
		echo
		
		tail -n +3 $file 

		sleep 5
    continue;;

    7)  echo
		echo Comparing files poem.txt and poem_new.txt...

		f='/home/charmi/Desktop/shell/poem_new.txt'

		cmp -s $file $f

		if [ $? -eq 1 ]; then
		    echo Files are different
		else
		    echo Files are not different
		fi

		sleep 5
    continue;;

	8)  echo 'Thank You!'
		exit;;

	*)	echo 'Please enter proper Choice.'
	  	sleep 5

esac
	done
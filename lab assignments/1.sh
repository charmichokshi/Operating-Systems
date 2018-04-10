# Write a script to obtain the effect DELETE/CONFIRM command. Generalize it to
# be used for COPY/CONFIRM and RENAME/CONFIRM.

# To copy files with confirmation
fcopy()
{
	echo 'Enter the filename(s) to be copied: '
	read filename
	echo 'Enter the destination for file(s) to be copied: '
	read dest 

	echo 'Do you want to Copy file' $filename '(Y/ N)?'
	read c

	if [[ ("$c" = "Y") || ("$c" = "y") ]];
	then
		cp -i $filename $dest
		echo 'File Copied Successfuly!'
		sleep 2
	else
		echo 'File NOT Copied.'
		sleep 2
	fi
}

# To delete files with confirmation
fdel()
{
	echo 'Enter the filename(s) to be deleted: '
	read filename
	rm -i $filename
	echo 'File Deleted successfuly!'
	sleep 2
}

# To rename files with confirmation
fren()
{
	echo "Enter the filename(s) to be renamed: "
	read filename
	echo 'Enter the destination for file(s) to be moved: '
	read dest 

	echo 'Do you want to Rename file' $filename '(Y/ N)?'
	read c

	if [[ ("$c" = "Y") || ("$c" = "y") ]];
	then
		mv -i $filename $dest
		echo 'File Renamed Successfuly!'
		sleep 2
	else
		echo 'File NOT Renamed.'
		sleep 2
	fi
}

while true
do
clear
cat << MENU

	***Menu***

	1. Copy file(s)
	
	2. Delete file(s)

	3. Rename file(s)

	0. Exit

MENU

echo 'Enter your Choice: '
read choice

case $choice in
	
	1)	fcopy
        continue;;

	2)   fdel
   		continue;;

	3)   fren
        continue;;

	0)   echo 'Thank You!'
		exit;;

	*) echo 'Please enter proper Choice.'

esac
done

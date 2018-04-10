clear
while true
do
clear
cat << MENU

	***Menu***

	a. Display current directory
	b. List directory
	c. Make directory
	d. Change directory
	e. Copy file
	f. Rename file
	g. Delete file
	h. Edit file
	i. Exit

MENU

echo -n  'Enter your Choice: '
read choice

case $choice in
	
	[aA])	echo -n "Current directory: "
			pwd
			sleep 5
        continue;;

	[bB])   echo -n "Enter directory name: "
			read d
			echo
			echo "Listing directory: " $d
			ls -l $d | tail -n +2
			sleep 5
   		continue;;

	[cC])   echo
			ls
			echo -n "Enter new directory name: "
			read d
			mkdir $d
			echo "Directory "$d "created successfuly!"
			echo
			ls
			sleep 5
        continue;;

	[dD])	echo -n "Current path: "
			pwd
			echo -n "Enter directory name where you want to go: "
			read d
			cd $d
			echo
			echo "You are in Directory "$d
			echo -n "Current path: "
			pwd
			sleep 5
        continue;;

	[eE])   ls
			echo
			echo -n 'Enter the filename(s) to be copied: '
			read filename
			echo -n 'Enter the destination for file(s) to be copied: '
			read dest 

			cp -i $filename $dest
			echo
			echo 'File(s) Copied Successfuly!'
			echo
			ls
			sleep 5
		
   		continue;;

	[fF])   ls
			echo
			echo -n  "Enter the filename(s) to be renamed: "
			read filename
			echo -n  'Enter the new name for file(s): '
			read dest 
			
			mv -i $filename $dest
			echo
			echo 'File(s) Renamed Successfuly!'
			echo
			ls
			sleep 5
			
        continue;;

	[gG])	ls
			echo
			echo -n  'Enter the filename(s) to be deleted: '
			read filename

			rm -i $filename
			echo
			echo 'File(s) Deleted successfuly!'
			echo
			ls
			sleep 5
        continue;;

	[hH])   ls
			echo
			echo -n "Enter file name which you want to Edit: "
			read filename

			cat $filename			
			sleep 5

			echo -n "Enter word you want to Edit: "
			read old

			echo -n "Enter Edited word: "
			read new

			sed -i "s/$old/$new/g" $filename 
			echo
			echo "file Edited successfuly!"
			echo
			cat $filename
			sleep 5

   		continue;;

	[iI])  echo 'Thank You!'
		exit;;

	*) echo 'Please enter proper Choice.'

esac
done
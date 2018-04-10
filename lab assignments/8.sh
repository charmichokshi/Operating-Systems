clear
echo -n "Enter name of the directory :"
read directory
if [ ! -d "$directory" ]
then
    echo "Directory does not exist"
else
	for i in `find $directory -type f -size 0`
	do
		rm -i $i		
	done
fi
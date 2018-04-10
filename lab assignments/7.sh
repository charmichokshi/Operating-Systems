# Write a script to compare identically named files in two directories and if they are
# same, copy one of them in a third directory.

clear 

echo -n 'Enter 1st Directory: '
read dir1

if [ ! -d $dir1 ]; then
	echo "Directory 1 not exist"
	exit 1
fi

echo -n 'Enter 2nd Directory: '
read dir2

if [ ! -d $dir2 ]; then
	echo "Directory 1 not exist"
	exit 1
fi

# copy all file names in to a text file
ls $dir1 > dir1.txt
ls $dir2 > dir2.txt

echo
echo 'Files in Directory 1: '
ls $dir1
echo
echo 'Files in Directory 2: '
ls $dir2

echo
echo -n 'Enter the destination Directory for file(s) to be copied: '
read TargetDir

mkdir $TargetDir

for FileFromDir1 in `cat dir1.txt`
do
	for FileFromDir2 in `cat dir2.txt`
	do
		# compare file name is same or not
		if [ "$FileFromDir1" = "$FileFromDir2" ]
		then
			cp -i $dir1/$FileFromDir1 $TargetDir
		fi
	done
done

echo
echo 'File(s) Copied successfuly!'
echo
echo 'Files in Target Directory: '
ls $TargetDir
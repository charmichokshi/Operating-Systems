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

echo -n 'Enter the destination Directory for file(s) to be copied: '
read TargetDir

mkdir $TargetDir

for FileFromDir1 in `cat dir1.txt`
do
	flag=0
	for FileFromDir2 in `cat dir2.txt`
	do
		# compare file name is same or not
		if [ "$FileFromDir1" = "$FileFromDir2" ]
		then
			# check access time of both files and copy the latest file to target directory
			if [ "$FileFromDir1" -nt "$FileFromDir2" ]; 
			then
				cp $dir1/$FileFromDir1 $TargetDir
			else
				cp $dir2/$FileFromDir1 $TargetDir
		fi
		# file name from directory1 is match to file name of directory2 [ flage is true ]
		flag=1
		fi
	done

	#if file name from directory1 is does NOT match to file name of directory2 [ copy to TargetDir ]
	if [ $flag -eq 0 ]
	then
		cp $dir1/$FileFromDir1 $TargetDir
	fi
done

# copy rest of file from directory2 to TargetDir
for FileFromDir2 in `cat dir2.txt`
do
	flag=0
	for FileFromDir1 in `cat dir1.txt`
	do
		if [ "$FileFromDir2" = "$FileFromDir1" ]
		then
			flag=1
		fi
	done
	if [ $flag -eq 0 ]
	then
		cp $dir2/$FileFromDir2 $TargetDir
	fi
done

echo 'File(s) Copied Successfully!'
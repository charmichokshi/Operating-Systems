clear
echo program to move file-list and files from current directory to another directory using for loop
echo

echo -n 'Enter the destination Directory for file(s) to be moved: '
read TargetDir

mkdir $TargetDir
ls `pwd` > file-list.txt

# moving a list of files in the current directory to another directory
for i in `ls pwd`
do
	mv $i $TargetDir/file-list.txt
done 

# moving all files in another directory
for FileFromDir1 in `cat file-list.txt`
do
	mv $FileFromDir1 $TargetDir		
done
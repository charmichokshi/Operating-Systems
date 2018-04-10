clear
echo -n "Enter Directory Name : "
read dir

ls $dir>fileList.txt
count=0

if [ -d $dir ]
then
     for fileName in `cat fileList.txt`
     do
        if [ -x $dir/$fileName ]
        then
           echo "$fileName"
           count=`expr $count + 1`
        fi
     done
fi
echo
echo "Total number of Executable Files: $count"
rm fileList.txt
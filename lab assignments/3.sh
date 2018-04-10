# Input a file name from a user and find out the complete path for a give file name.

clear

echo -n 'Enter File name to find its complete Path: '
read filename
if [ -f $filename ]
then
echo
echo "Complete path of "$filename":"
echo
find $PWD -type f | grep "$filename"
echo

else
echo -n 'File '$filename' NOT exist in: '
pwd
fi	

# clear
# echo "Enter File Name : \c "
# read fileName

# if [ -f $fileName ]
# then
# str=`find $fileName`
# path=`pwd`
# echo "Full path of file is $path/$str"

# else
# echo "file [ $fileName ] not exist in \c "
# pwd
# fi
























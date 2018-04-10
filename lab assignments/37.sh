clear
echo -n "Enter the date(mmddyyyy): "
read userDate
echo

echo -n "Enter directory name: "
read d

dir="/home/charmi/Desktop/shell/date"
echo

echo "Newer files are: "
echo
touch -t $userDate $dir
find $d -newer $dir
echo
echo "Older files are: "
echo
touch -t $userDate $dir
find $d -not -newer $dir
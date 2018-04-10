clear
echo -n 'Enter user name: '
read un
n=`last | grep $un | wc -l`
echo
echo $un has logged in $n times

clear

echo 'Printing sorted list of users'
echo
cut -d ":" -f 1 /etc/passwd | sort
echo
echo 'Printing sorted list of loged in users'
echo
users | sort
clear
echo -n 'Total number of users in system: '
cut -d ":" -f 1 /etc/passwd | wc -l
echo
echo -n 'Total number of users loged in rite now: '
who | wc -l
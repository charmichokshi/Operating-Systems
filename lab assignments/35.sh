clear

awk -F'[/:]' '{if ($3 >= 1000 && $3 != 65534) print $1}' /etc/passwd > pass.txt
echo Printing all users of the system
echo
cat pass.txt

echo
echo Printing usernames without password
echo

set `awk -F'[/:]' '{if ($3 >= 1000 && $3 != 65534) print $1}' /etc/passwd | sort`
while [ -n "$1" ]
do
	sudo awk -F'[/:]' '{if ($2!="*" && !($2!="!")) print $1}' /etc/shadow | grep -w $1
	shift 1
done

# sudo getent shadow | grep '^[^:]*:.\?:' | cut -d : -f1

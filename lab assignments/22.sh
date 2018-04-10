echo
echo -n 'Enter user name: '
read un
grep -o '^[a-zA-Z]*' /etc/passwd > userName.txt

j=0

for i in `cat userName.txt`
do
	if [[ "$i" = "$un" ]];
	then
		echo user exist.
		j=1
	fi
done

if [[ $j -eq 0 ]]; then
	echo user NOT exist
fi
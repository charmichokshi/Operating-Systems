echo -n 'Enter name of User: '
read user

if [[ "$USER" = "$user" ]]; then
	echo $user is currently logged in.
else
	echo $user is not currently logged in.
fi
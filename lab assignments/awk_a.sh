clear
echo Currently loged in users
echo
who
echo
echo Printing name and time of login sorted by time
echo
echo -e "NAME \t   TIME"
echo
who | awk '{print $1 , "   ", $4}' | sort -nk4 
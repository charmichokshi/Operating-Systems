clear
echo -n "Enter file name: "
read fn

echo
echo Viewing file $fn
echo
cat $fn
echo
echo Viewing file $fn after reversing each line
echo
awk '{for(i=NF; i>=1; i--) printf "%s ", $i; print ""}' $fn
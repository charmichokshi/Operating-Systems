clear
echo Script to display the name of those files which are having multiple links.
echo
echo -n "Enter directory name: "
read d

ls -l $d | awk '{if($2>1) {print $9}}'
echo
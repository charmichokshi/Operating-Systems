clear
echo Script to obtain the effect of DIR/SINCE/BEFORE commands
echo

echo -n "Enter directory name: "
read d
echo
echo "Output of command 'dir': "
dir $d

echo
echo -n "Enter file name: "
read f
echo "Output of command 'since' on file $f: "
echo
since $f

echo
echo -n "You want to find modified directories of last how may days?: "
read days
echo
echo "Modified directories SINCE last $days days: "
find -type d -mtime -$days
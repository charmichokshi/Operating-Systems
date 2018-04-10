clear
echo -n "Enter Directory name: "
read dir

echo 
echo "Listing directory and subdirectories in tree structure..."
echo
tree $dir

echo
echo -n "Enter command you want to locate using 'which' command: "
read c
echo
which $c
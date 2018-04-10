clear
echo -n "Enter Directory name: "
read dir

echo
echo "SIZE          FILENAME"
echo "====       ==============="

ls -lS  $dir | awk '{print $9, "         ", $5}'
echo
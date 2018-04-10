cd ~
echo "Largest file in `pwd`"
set `ls -Rla | awk '{print $5,$9}' | sort -bhr | uniq`
filesize=$1
for i in *
do
if [ $1 = $filesize ]
then
echo "File Found: Name: $2"
echo "            Size: $1"
echo ""
fi
shift 2
done

echo ""
echo ""
echo "Smallest files in `pwd`"
set `ls -Rla | awk '{print $5,$9}' | sort -bh | uniq`
filesize=$1
for i in *
do
if [ $1 = $filesize ]
then
echo "File Found: Name: $2"
echo "            Size: $1"
echo ""
fi
shift 2
done


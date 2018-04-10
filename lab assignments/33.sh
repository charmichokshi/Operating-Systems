clear
echo -n "Enter directory name: "
read d
echo
echo Listing all subdirectory names
echo

ls -l $d | tail -n +2 | awk '{print $1, $9}' > prg_33.txt
while read line; 
do
    case $line in
    d*)
        echo $line | cut -d ' ' -f 2 
    esac
done < prg_33.txt
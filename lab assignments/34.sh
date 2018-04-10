clear
echo -n "Enter directory name: "
read d
echo
echo Printing files others can read and write
echo

ls -l $d | tail -n +2 | awk '{print $1 , $9}' > prg_34.txt
while read line;
do
      other=`echo $line | cut -c8-10`

    case $other in
    rw*)
        echo $line | cut -d ' ' -f 2
    esac

done < prg_34.txt
clear
echo input file containt:
cat inputfile.txt
echo
echo input file containt with line numbers:
awk '{print NR  ". " $s}' inputfile.txt 
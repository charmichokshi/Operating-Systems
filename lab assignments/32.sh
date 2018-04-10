clear
echo locating variables of all .c and .h files
echo

grep -e int -e float -e double -e char *.{c,h} |
awk '{first = $1; $1 = ""; print substr($2,1,length($2)-1)}' | 
tr '\n' ',' | 
sed 's/.$//'

echo
echo
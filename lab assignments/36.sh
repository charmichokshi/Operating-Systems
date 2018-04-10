clear

#function to calculate the the frequency of words
wordfrequency() { 
  awk '
     BEGIN { FS="[^a-zA-Z]+" } {
         for (i=1; i<=NF; i++) {
             word = tolower($i)
             words[word]++
         }
     }
     END {
         for (w in words)
              printf("   %3d \t\t %s\n", words[w], w)
     } ' | sort -rn
}

echo -n 'Enter the file name: '
read filename
echo
echo Viewing file $filename
echo
cat $filename
echo
echo '10 most frequent words in '$filename' are: '
echo
echo -e "Frequency \t Word"
echo "========================="
cat $filename | wordfrequency | head -10
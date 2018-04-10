# Write a script to display the files in the specified directory in the following format:
# File Size in KB Date Protection Owner
# At the end display total number of files occupying total space.

# stat -c "%y %s %n" *

clear
echo -n 'Enter the Directory name to show its containts: '
read dir

# -rwxrwxrwx 1 charmi charmi 1450 Aug 21 23:49 1.sh
echo 
echo -e 'File \t Size(KB) \t Date \t Protection \t Owner'
echo 
#du -ckx $dir| grep total | awk '{print $1}'

# du -sh $dir
# directory/ file (letter)...permission   link   user group size..Bytes   month  date   time  name


ls -l --block-size=K $dir | tail -n +2 | awk '{print $9, "   ", $5, "           ", $6,$7 "  ", $1 ,"   ", $3}' 
echo 

echo -n `ls -l $dir | head -1`
echo ' number of files occupying total space in directory '$dir
echo 

# set `ls -l $dir`  
# ls -la $dir | awk '{print $1 $2}'



# echo	
# echo -e 'File \t Size(KB) \t Date \t Protection \t Owner'
# echo -e $(stat -c "%n \t %s \t %y {print $1} \t %A \t %G" $dir)


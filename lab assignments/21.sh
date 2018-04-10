clear
echo -n 'Enter directory name: '
read dir
echo
echo Contains of $dir
ls $dir
echo
echo -n 'Total number of files in '$dir': '
ls $dir | wc -l
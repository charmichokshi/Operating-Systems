clear
echo -n 'Todays Date: '
date +%Y-%m-%d

echo -n 'Current Time: '
date  +"%I:%M %p"

p=$(date +"%p")
h=$(date +"%I")

if [ "$p" = "AM" ]; then
  echo Good morning
elif [ $h -lt 6 -a $p = PM ]; then
  echo Good afternoon
else	
  echo Good evening
fi

# echo -n 'Todays Date: '
# date +%Y-%m-%d

# echo -n 'Current Time: '
# date +'%H:%M %p'

# # h=date +%H`
# p=$(date +"%p")
# # p=`daye +%p`
# h=$(date +"%H")

# if [ "$p" = "AM" ]; then
#   echo Good morning
# elif [ $h -lt 6 -a "$p" = "PM" ]; then
#   echo Good afternoon
# else	
#   echo Good evening
# fi



# set -x
# echo $0
# echo $1
# echo $2

# ./11.sh a b

# out--
# ./11.sh
# a
# b
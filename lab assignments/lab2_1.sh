while true
do
cat << menu

1) Floating point calculations
2) Trigonometric operations
3) Logarithms
4) Exponent
0) Exit
menu

echo "Enter your choice"
read choice

case $choice in
	1) while true 
	   do
	   echo "A. Addition"
	   echo "B. Subtraction"
	   echo "C. Multiplication"
	   echo "D. Division"
	   echo "E. Modulo"
	   echo "F. Go to the main menu"
	   echo "Enter your choice"
	   read ch
	   if [ "$ch" = "F" ]
	   then 
		break
	   else
		echo "Enter your first number"
	   	read fir
	   	echo "Enter your second number"
	   	read sec
	   	
	   fi
	   case $ch in
		A) echo "Output:"
		   echo "scale=4; $fir+$sec" | bc;;
		B) echo "Output:"
		   echo "scale=4; $fir-$sec" | bc;;
		C) echo "Output:"
		   echo "scale=4; $fir*$sec" | bc;;
		D) echo "Output:"
		   echo "scale=4; $fir/$sec" | bc;;
		E) echo "Output:"
		   echo "scale=4; $fir%$sec" | bc;;	
		
	  
	   esac
	   done;;
	  

	2) while true
	   do
	   echo "Enter the number in degrees"
	   read deg
	   pi=3.14
	   rad=`echo "$deg*($pi/180)" | bc -l`
	 
	   echo "A. sin x"
	   echo "B. cos x"
	   echo "C. tan x"
	   echo "D. cosec x"
	   echo "E. sec x"
	   echo "F. cot x"
	   echo "G. Go to the main menu"
	   

	   echo "Enter your choice"
	   read ch1

	   case $ch1 in
		A) echo "Output:"
		   a=`echo "s($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		B) echo "Output:"
		   a=`echo "c($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		C) echo "Output:"
		   a=`echo "s($rad)/c($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		D) echo "Output:"
		   a=`echo "1/s($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		E) echo "Output:"
		   a=`echo "1/c($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		F) echo "Output:"
		   a=`echo "c($rad)/s($rad)" | bc -l`
		   printf '%.*f\n' 1 $a;;
		G) break;;
	   esac
	   done;;

	3) echo "Enter the number whose log you want to find"
	   read num
	   echo "Enter the base"
	   read base
	   echo "Output:"
	   echo "l($num)/l($base)" | bc -l;;

	4) echo "Enter the number whose exponent you want to find"
	   read n
	   echo "Output:"
	   echo "e($n)" | bc -l;;

	0) exit;;
esac
done


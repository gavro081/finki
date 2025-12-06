#!/bin/bash

# chmod +x "$0"

if [ $# -ne 1 ] 
then
	echo "invalid argument count. needed 1" 
	exit 1
fi

if [[ ! $1 =~ .*\.csv || ! -r $1 ]]
then
	echo "invalid file"
	exit 1
fi


count=$(wc -l $1 | awk '{print $1 - 1;}')

file=$1

data=$(awk -F, 'NR > 1 {print $2" "$3" "$4" "$5" "$6}' "$1")


echo "Exam Scores Analysis"
echo "-------------------"
echo "Total Number of Students: $count"
echo ""
echo "Subject Averages: "
awk -F, 'BEGIN{sum=0;count=0;} NR > 1 {sum+=$3;count++;} END{printf "Math:     %.2f\n", sum/count;}' $file
awk -F, 'BEGIN{sum=0;count=0;} NR > 1 {sum+=$4;count++;} END{printf "Science:  %.2f\n", sum/count;}' $file
awk -F, 'BEGIN{sum=0;count=0;} NR > 1 {sum+=$5;count++;} END{printf "English:  %.2f\n", sum/count;}' $file
awk -F, 'BEGIN{sum=0;count=0;} NR > 1 {sum+=$6;count++;} END{printf "History:  %.2f\n", sum/count;}' $file

echo "Subject Extreme Performers:"
#mat
awk -F, 'BEGIN{max=0;min=101; imemax=""; imemin=""} NR > 1 {
if ($3 > max) { max=$3;imemax=$2; } 
if ($3 < min) { min=$3;imemin=$2; }
} 
END{ print "Math - Highest: " imemax " (Score: " max "), Lowest: " imemin " (Score: " min ")"}' $file

#science
awk -F, 'BEGIN{max=0;min=101; imemax=""; imemin=""} NR > 1 {
if ($4 > max) { max=$4;imemax=$2; } 
if ($4 < min) { min=$4;imemin=$2; }
} 
END{ print "Science - Highest: " imemax " (Score: " max "), Lowest: " imemin " (Score: " min ")"}' $file

#english
awk -F, 'BEGIN{max=0;min=101; imemax=""; imemin=""} NR > 1 {
if ($5 > max) { max=$5;imemax=$2; } 
if ($5 < min) { min=$5;imemin=$2; }
} 
END{ print "English - Highest: " imemax " (Score: " max "), Lowest: " imemin " (Score: " min ")"}' $file

# history
awk -F, 'BEGIN{max=0;min=101; imemax=""; imemin=""} NR > 1 {
if ($6 > max) { max=$6;imemax=$2; } 
if ($6 < min) { min=$6;imemin=$2; }
} 
END{ print "History - Highest: " imemax " (Score: " max "), Lowest: " imemin " (Score: " min ")"}' $file


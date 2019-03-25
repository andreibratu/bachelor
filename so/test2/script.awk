BEGIN {SUM=0; count=0;}
{SUM += $2; count += 1;}
END {print SUM/count} 

i=0
if [ -n $1 ]; then
	find $1 -name "*.c" | while read file; do
		if [ $i -eq 10 ]; then
			exit 0
		fi
		if [ `cat $file | wc -l` -ge 100 ]; then
			echo $file
			i=`expr $i + 1`
		fi
	done
fi

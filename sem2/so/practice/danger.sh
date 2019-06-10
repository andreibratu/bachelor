if [ -z $1 ]; then
	echo Please input a program
fi

while true; do
	output=`ps | grep $1`
	if [ "$output" ]; then
		pid=`ps | grep $1 | awk '{print $1}'`
		echo $pid
		kill -9 $pid
		echo Just shot a mongrel called $1
	fi
done


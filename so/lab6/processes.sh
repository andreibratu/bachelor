finger | awk 'NR>1 {print $1}' | while read user; do
	name=`cat /etc/passwd | grep $user | awk -F: '{print $5}'`
	procs=`ps -U $user | awk 'NR>1 {print $1}' | wc -l`
	echo $name $procs
done

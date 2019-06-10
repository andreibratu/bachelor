ls -l | grep '^..w..w..w.' | while read file; do
	name=`echo $file | awk '{print $9}'`
	chmod a-w $name
done

find . -name "*.log" | while read file; do
	cat $file | sort > $file
done

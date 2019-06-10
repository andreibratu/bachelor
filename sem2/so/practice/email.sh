finger | awk 'NR > 1 {print $1}' | while read username; do
	echo "$username@scs.ubbcluj.ro"
done

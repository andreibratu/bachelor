function contains() {
  if echo $1 | grep -q $2; then
    return 0
  else
    return 1
  fi
}

if [ $# -ne 3 ] ; then
  echo Invalid number args..
else
  for i in `seq $1 $2`; do
    if contains $i $3; then
      echo $i
    fi
  done
fi

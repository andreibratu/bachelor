#!/bin/bash

function prime() {
  local i=0
  ub=`expr $1 - 1`
  ub=`expr $ub / 2`
  for i in `seq 2 $ub`; do
    if [ `expr $1 % $i` -eq 0 ]; then
      return 1
    fi
  done

  return 0
}

if [ $# -ne 2 ] ; then
  echo Invalid number args..
else
  for i in `seq $1 $2`; do
    if prime $i; then
      echo $i
    fi
  done
fi

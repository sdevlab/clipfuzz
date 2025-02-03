#!/bin/bash

ROOT=/home/sungbin/dyfuzz

T_DIR="${ROOT}/submodule/libprotobuf-mutator/src"

DIR_1="${ROOT}/mutation_operator/origin" # Origin mutation
DIR_2="${ROOT}/mutation_operator/v2" # v2: Multiple Clone
DIR_3="${ROOT}/mutation_operator/v3" # v3: select 'Mutate' by 80%


T_NAME_0=mutator.cc
T_NAME_1=field_instance.h

if [ -z "$1" ]; then
    echo "Usage: $0 [1,2,3] or --check"
    exit 1
fi

T_CONTENT_0=$(cat "${T_DIR}/${T_NAME_0}")
DIR_1_CONTENT_0=$(cat "${DIR_1}/${T_NAME_0}")
DIR_2_CONTENT_0=$(cat "${DIR_2}/${T_NAME_0}")
DIR_3_CONTENT_0=$(cat "${DIR_3}/${T_NAME_0}")

if [ $1 == '--check' ]; then

  if [ "$T_CONTENT_0" == "$DIR_1_CONTENT_0" ]; then
	  echo "Current: (Origin mutation)"
  elif [ "$T_CONTENT_0" == "$DIR_2_CONTENT_0" ]; then
	  echo "Current: V2 (Mutiple Clone mutation)"
  elif [ "$T_CONTENT_0" == "$DIR_3_CONTENT_0" ]; then
	  echo "Current: V3 (select 'Mutate' by 80%)"
  fi
  exit
fi

if [ "$1" == "1" ]; then
    cat "${DIR_1}/${T_NAME_0}" > "${T_DIR}/${T_NAME_0}"
    cat "${DIR_1}/${T_NAME_1}" > "${T_DIR}/${T_NAME_1}"
    echo "(Origin)"
elif [ "$1" == "2" ]; then
    cat "${DIR_2}/${T_NAME_0}" > "${T_DIR}/${T_NAME_0}"
    cat "${DIR_2}/${T_NAME_1}" > "${T_DIR}/${T_NAME_1}"
    echo "V2 (Multiple Clone)"
elif [ "$1" == "3" ]; then
    cat "${DIR_3}/${T_NAME_0}" > "${T_DIR}/${T_NAME_0}"
    cat "${DIR_3}/${T_NAME_1}" > "${T_DIR}/${T_NAME_1}"
    echo "V3 ('Mutate' by 80%)"
else
    echo "No match found. ${T_DIR} remains unchanged."
fi

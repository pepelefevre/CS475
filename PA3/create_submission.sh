#!/usr/bin/env sh

if [ -e "README.txt" ]
then
  echo "Code is commented. Good!"
  echo "Did you include your report?"
else
  echo "Please create a readme file named: README.txt"
  exit
fi

if [ -z "$1" ]
  then
    echo "Usage: ./create_submission.sh 'FirstNameLastName-PA#' "
    exit
  else
    make -s
    if [[ $? -ne 0 ]] ; then
      echo "make should work"
      exit 1
    fi 
    make clean -s
    echo "Creating archive"
    STUDENT=$1
    tar cvf $STUDENT.tar *.pdf *.txt *.c *.h  makefile
fi


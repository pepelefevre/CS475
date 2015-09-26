num_threads=1 schedule=

while getopts t:s: opt; do
  case $opt in
  t)
      num_threads=$OPTARG
      ;;

  s)
      schedule=$OPTARG
      ;;
  esac
done

shift $((OPTIND - 1))

make sieve2

while [ $num_threads -lt 9 ]; do  
  export OMP_NUM_THREADS=$num_threads
#  export OMP_SCHEDULE=$schedule
#  echo $schedule
  echo $num_threads
  echo 500000000
  for run in {1..5}
  do
    ./sieve2 500000000
  done
  echo 1000000000
  for run in {1..5}
  do
    ./sieve2 1000000000
  done
  echo 1500000000
  for run in {1..5}
  do
    ./sieve2 1500000000
  done
let num_threads=num_threads+1
done

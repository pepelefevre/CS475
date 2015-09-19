
num_threads=1 schedule=

while getopts t: opt; do
  case $opt in
  t)
      num_threads=$OPTARG
      ;;
#  s)
#      schedule=$OPTARG
#      ;;
  esac
done

shift $((OPTIND - 1))

make jacobi_2D

while [ $num_threads -lt 9 ]; do  
  export OMP_NUM_THREADS=$num_threads
#  export OMP_SCHEDULE=$schedule
#  echo $schedule
  echo $num_threads
  for run in {1..5}
  do
    ./jacobi_2D 800 2000
  done
let num_threads=num_threads+1
done

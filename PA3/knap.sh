
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

make knap

while [ $num_threads -lt 9 ]; do  
  export OMP_NUM_THREADS=$num_threads
#  export OMP_SCHEDULE=$schedule
#  echo $schedule
  echo $num_threads >> k120.res
  echo $num_threads >> k240.res
  for run in {1..5}
  do
    ./knap k120.txt >> k120.res
    ./knap k240.txt >> k240.res
  done
let num_threads=num_threads+1
done

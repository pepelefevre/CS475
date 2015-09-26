
make sieve1

echo 100000
for run in {1..5}
do

  ./sieve1 500000000
done
echo 200000
for run in {1..5}
do
  ./sieve1 1000000000
done
echo 300000
for run in {1..5}
do
  ./sieve1 1500000000
done

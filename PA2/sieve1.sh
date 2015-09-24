
make sieve1

echo 100000
for run in {1..3}
do
  ./sieve1 100000
done
echo 200000
for run in {1..3}
do
  ./sieve1 200000
done
echo 300000
for run in {1..3}
do
  ./sieve1 300000
done


make sieve

echo 100000
for run in {1..5}
do
  ./sieve 100000
done
echo 200000
for run in {1..5}
do
  ./sieve 200000
done
echo 300000
for run in {1..5}
do
  ./sieve 300000
done

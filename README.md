# APS_PROJECT_2018
## Comparisions of Probabilistic and Deterministic Primality testing algorithms based on accuracy and speed

Probabilistic and Deterministic algorithms are studied and implemented in C++.
For handling big numbers mpz module of GMP library is used. you can install gmp libary using commaand:
```
sudo apt-get install libgmp3-dev
```
For compiling any code make sure to use -lgmp flag such as:
```
$ g++ aks.cpp -lgmp -o aks
```
You can give arbitrary input number and code will return if number is prime or not such as:
```
$ ./aks
AKS Primality test
number:12354532527675755756757547547
composite
time = 0.042260
```
or you can give file input as argument with file consisting of numbers separated by newline example
for file consisting of all numbers 2, 4, 5 ,7 ,8, 9:
```
$ ./aks input.txt
AKS Primality test
2: prime
4: composite
5: prime
7: prime
8: composite
9: composite
total time = 0.200113
total primes = 4
```
Some sample test cases for testing are provided such as prime numbers till 10^6, composite numbers, pseudoprime nubmers etc. You can make your own test cases if you want.

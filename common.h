// Farhin Bhuiyan 
#ifndef COMMON_H // Include guard to prevent multiple inclusions of this header file
#define COMMON_H

#include <cstddef>  // Include cstddef for size_t definition

// Function to check if a number is prime
bool IsPrime(size_t n) {
  if (n == 2 || n == 3) // 2 and 3 are prime numbers
    return true;
  if (n == 1 || n % 2 == 0) // 1 is not prime, even numbers greater than 2 are not prime
    return false;
  for (int i = 3; i * i <= n; i += 2) // Check for factors from 3 to sqrt(n), increment by 2 (skip even numbers)
    if (n % i == 0) // If n is divisible by any i, it's not prime
      return false;
  return true; // If no divisors found, n is prime
}

// Function to find the next prime number greater than or equal to n
int NextPrime(size_t n) {
  if (n % 2 == 0) // If n is even, increment by 1 to make it odd (even numbers > 2 are not prime)
    ++n;
  while (!IsPrime(n)) n += 2; // Increment by 2 (skip even numbers) until a prime number is found
  return n; // Return the next prime number
}

#endif  // COMMON_H // End of include guard



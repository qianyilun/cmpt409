#include <cmath>
#include <cstdio>
#include <iostream>

int quick_modpow(long a, long n, long mod) {
    if(n == 0)
        return 1;  
    long res = quick_modpow(a * a % mod, n/2, mod);  
    if(n & 1) // If this is odd
        res = res * a % mod;  
    return res;
}

bool passFemat(int number) {
    for (int a = 2; a < number; ++a) {
        // std::cout << quick_modpow(a, number, number) << std::endl;
        if (quick_modpow(a, number, number) != a) {
            return false;
        }
    }
    return true;
}

bool isPrime(int number) {
    int sqrtN = (int) sqrt(number);
    for (int i = 2; i <= sqrtN; ++i) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

int main() {

    int number;
    while (std::cin.peek() != EOF) {
        scanf("%d\n", &number);
        if (number == 0) {
            break;
        }


        if (!isPrime(number) && passFemat(number)) {
            std::cout << "The number " << number << " is a Carmichael number." << std::endl;
        } else {
            std::cout << number << " is normal." << std::endl;
        }
    }


}
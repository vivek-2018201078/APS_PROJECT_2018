
#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

unsigned long seed = 73;

bool miillerTest(mpz_t d, mpz_t n)
{

    mpz_t temp, rand, a, x, nminus;
    mpz_init(temp);
    mpz_init(rand);
    mpz_init(x);
    mpz_init(a);
    mpz_init(nminus);
    mpz_sub_ui(temp, n, 4);

    gmp_randstate_t state;
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    mpz_urandomm(rand, state, n);
    mpz_mod(rand, rand, temp);
    mpz_add_ui(rand, rand, 2);
    gmp_randclear(state);
    seed = seed + mpz_get_ui(rand);
    mpz_powm(x, rand, d, n);


    mpz_sub_ui(nminus, n, 1);
    if(mpz_cmp_d(x, 1) == 0 || mpz_cmp(x, nminus) == 0)
        return true;

    while(mpz_cmp(d, nminus) != 0) {
        mpz_mul(x, x, x);
        mpz_mod(x, x, n);
        mpz_mul_ui(d, d, 2);

        if(mpz_cmp_d(x, 1) == 0)
            return false;
        if(mpz_cmp(x, nminus) == 0)
            return true;
    }

    return false;
}


bool isPrime(mpz_t n, int k)
{
    if(mpz_cmp_d(n, 1) <= 0 || mpz_cmp_d(n, 4) == 0) {
        return false;
    }
    if (mpz_cmp_d(n, 3) == 0 || mpz_cmp_d(n, 2) == 0) {
        return true;
    }

    mpz_t d, temp;
    mpz_init(d);
    mpz_init(temp);
    mpz_sub_ui(d, n, 1);

    while(mpz_divisible_ui_p(d, 2) != 0)
        mpz_cdiv_q_ui(d, d, 2);
    for (int i = 0; i < k; i++)
        if (!miillerTest(d, n)) {
            return false;
        }

    return true;
}


int main(int argc, char* argv[])
{
    printf("Miller-Rabin primality test\n");
    int k = 10;
    mpz_t n;
    mpz_init(n);
    if(argc == 1) {
        printf("number:");
        char n_str[1000];
        scanf("%s", n_str);
        mpz_set_str(n, n_str, 10);
        mpz_t i;
        mpz_init(i);
        int count = 0;
        clock_t start = clock();
            if(isPrime(n, k)) {
                count++;
                printf("prime\n");
            } else
                printf("composite\n");
        double total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
        gmp_printf("time = %f\n",total_time);
    }
    else {
        FILE* fp = fopen(argv[1], "r");
        char n_str[1000];
        int count = 0;
        clock_t start = clock();
        while (fscanf(fp, "%s", n_str) != EOF) {
            mpz_set_str(n, n_str, 10);
            if (isPrime(n, k)) {
                cout << n_str << " prime\n";
                count++;
            }
            else {
                cout << n_str << " composite\n";
            }
        }
        double total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
        gmp_printf("total time = %f seconds\n",total_time);
        cout << "total primes = " << count << "\n";
        fclose(fp);
    }
    return 0;
}

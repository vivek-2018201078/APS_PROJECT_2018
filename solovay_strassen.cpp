#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

unsigned long seed = 73;

bool Solovay(mpz_t p, int iteration)
{
    mpz_t p_1;
    mpz_t p_2;
    mpz_t mod;
    mpz_t rand;
    mpz_t p_mod_2;
    mpz_t jacobian;
    mpz_t p_1_div_2;

    gmp_randstate_t state;

    mpz_init(p_2);
    mpz_init(p_1);
    mpz_init(mod);
    mpz_init(rand);
    mpz_init(p_mod_2);
    mpz_init(jacobian); 
    mpz_init(p_1_div_2);

    mpz_sub_ui(p_2, p, 2);
    mpz_sub_ui(p_1, p, 1);
    mpz_cdiv_q_ui(p_1_div_2, p_1, 2);

    if ((mpz_cmp_ui(p,2)) < 0) 
        return false;

    mpz_cdiv_r_ui(p_mod_2,p,2);

    if ( ((mpz_cmp_ui(p,2)) != 0) && ((mpz_sgn(p_mod_2) == 0)) ) 
        return false;

    for (int i = 0; i < iteration; i++)
    {
        gmp_randinit_mt(state);
        gmp_randseed_ui(state, seed);
        
        mpz_urandomm(rand, state, p_2);
        mpz_add_ui(rand, rand, 1);
                
        gmp_randclear(state);
        seed = seed + mpz_get_ui(rand);

        int jacobi = mpz_jacobi(rand, p);
        if(jacobi < 0){
            jacobi = -jacobi;
            mpz_sub_ui(jacobian, p, jacobi);
        }
        else
            mpz_add_ui(jacobian, p, jacobi);

        mpz_mod(jacobian,jacobian,p);

        mpz_powm(mod, rand, p_1_div_2, p);
        
        if ( (mpz_sgn(jacobian) == 0) || (mpz_cmp(jacobian,mod) !=0) )
        { 
            return false;
        }

    }
    return true;
}


int main(int argc, char const* argv[])
{
    printf("Solovay primality test\n");
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
            if(Solovay(n, k)) {
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
            if (Solovay(n, k)) {
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

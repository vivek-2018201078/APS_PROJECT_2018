#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>

using namespace std;

unsigned long seed = 73;
bool lehmann(mpz_t n, int k){
    
    const char* n_str = to_string(k).c_str();

	mpz_t i;
	mpz_t l;
	mpz_t n_1;
	mpz_t n_2;
	mpz_t temp;
	mpz_t rand;
	mpz_t cnt_1;
	mpz_t cnt_n_1;
	mpz_t n_1_div_2;
	
	mpz_init(i);
	mpz_init(l);
	mpz_init(n_1);
	mpz_init(n_2);
	mpz_init(temp);	
	mpz_init(rand);	
	mpz_init(cnt_1);
	mpz_init(cnt_n_1);
	mpz_init(n_1_div_2);

	mpz_sub_ui(n_1, n, 1);
	mpz_sub_ui(n_2, n, 2);
	mpz_set_str(l, n_str, 10);	
	mpz_cdiv_q_ui(n_1_div_2, n_1, 2);

    gmp_randstate_t state;

	while(mpz_cmp(l,i) > 0){
		gmp_randinit_mt(state);
		gmp_randseed_ui(state, seed);
		
		mpz_urandomm(rand, state, n_2);
		mpz_add_ui(rand, rand, 1);
		mpz_powm(temp, rand, n_1_div_2, n);		
   	 			
   	 	gmp_randclear(state);
    	seed = seed + mpz_get_ui(rand);

		if( mpz_cmp_ui(temp,1) != 0 && mpz_cmp(temp,n_1) != 0){
			return false;
		}

		if( mpz_cmp_ui(temp,1) == 0){
			mpz_add_ui(cnt_1,cnt_1,1);
		}

		mpz_add_ui(i,i,1);
	}

	if(mpz_cmp(cnt_1,l) == 0)
		return false;

	return true;
}

int main(int argc, char const *argv[])
{
	printf("Lehmann primality test\n");
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
            if(lehmann(n, k)) {
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
            if (lehmann(n, k)) {
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

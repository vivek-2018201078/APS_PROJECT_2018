#include <bits/stdc++.h>
#include <gmp.h>
#include <gmpxx.h>
using namespace std;

unsigned long seed = 2;

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


bool isPrime_miller(mpz_t n, int k)
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
    mpz_t n;
	mpz_init(n);
	clock_t start;
	double total_time;
	bool prime;
	

	if (argc == 1){
		string n_str;

		cout<<"Enter Number:";
		cin>>n_str;

		int k = n_str.size();

    	mpz_set_str(n, n_str.c_str(), 10);

        start = clock();

        prime = isPrime_miller(n, k);

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Miller Rabin = %f\n",total_time);

	    if(prime){
	    	cout<<"Prime\n";
	    }
	    else{
	    	cout<<"Composite\n";
	    }

        start = clock();

        prime = Solovay(n, k);

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Solovay = %f\n",total_time);

	    if(prime){
	    	cout<<"Prime\n";
	    }
	    else{
	    	cout<<"Composite\n";
	    }

        start = clock();

        prime = lehmann(n, k);

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Lehmann = %f\n",total_time);

	    if(prime){
	    	cout<<"Prime\n";
	    }
	    else{
	    	cout<<"Composite\n";
	    }

	}

	else{
		int count_miller  = 0;
		int count_solvay  = 0;
		int count_lehmann = 0;
		int k = 15;
		char n_str[1000];

    	FILE* fp = fopen(argv[1], "r");
        start = clock();

    	while (fscanf(fp, "%s", n_str) != EOF) {
    		mpz_set_str(n, n_str, 10);

        	if (isPrime_miller(n,k)) {
            	count_miller++;
        	}
		}    

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Miller Rabin = %f\n",total_time);
		fclose(fp);

	    cout<<"Total Primes Miller:"<<count_miller<<"\n";

    	FILE* fp1 = fopen(argv[1], "r");
        start = clock();
    	
    	while (fscanf(fp1, "%s", n_str) != EOF) {
    		mpz_set_str(n, n_str, 10);
        	if (Solovay(n,k)) {
            	count_solvay++;
        	}
		}    

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Solovay Strassen = %f\n",total_time);
		fclose(fp1);

	    cout<<"Total Primes Solovay Strassen:"<<count_solvay<<"\n";    	

	    FILE* fp2 = fopen(argv[1], "r");
        start = clock();
    	
    	while (fscanf(fp2, "%s", n_str) != EOF) {
    		mpz_set_str(n, n_str, 10);
        	if (lehmann(n,k)) {
            	count_lehmann++;
        	}
		}    

	    total_time = (double) (clock() - start) / (double) CLOCKS_PER_SEC;
	    gmp_printf("Total Time Lehmann = %f\n",total_time);
		fclose(fp2);

	    cout<<"Total Primes Lehmann:"<<count_lehmann<<"\n";
	}

    return 0;
}
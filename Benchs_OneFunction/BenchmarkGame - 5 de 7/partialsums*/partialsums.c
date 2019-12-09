//  The Computer Language Shootout
//  http://shootout.alioth.debian.org/
//  contributed by Greg Buchholz
//
//  compile with:  -O3 -msse2 -lm

#include<math.h>
#include<stdio.h>

typedef double v2df __attribute__ ((vector_size (16)));

int main(int argc, char* argv[])
{
    double  twoThrd = 0, sqrts = 0, Flint = 0, Cookson = 0;
    v2df    Harmonic, zeta, poly, alt, Gregory;
    v2df    zero, one, two, init, m_one, kv, av;

    double  k, k3, s, c;
    int n;  n = 2500000;

    //zero
    v2df vzero;
    double *tmpzero;
    tmpzero = (double *)&vzero; 
    *(tmpzero) = 0.0; 
    *(tmpzero+1) = 0.0;
    zero  = vzero;  
    
    //one
    v2df vone;
    double *tmpone;
    tmpone = (double *)&vone; 
    *(tmpone) = 1.0; 
    *(tmpone+1) = 1.0;
    one  = vone;
    
    //two
    v2df vtwo;
    double *tmptwo;
    tmptwo = (double *)&vtwo; 
    *(tmptwo) = 2.0; 
    *(tmptwo+1) = 2.0;
    two  = vtwo;
    
    //m_one
    v2df vm_one;
    double *tmpm_one;
    tmpm_one = (double *)&vm_one; 
    *(tmpm_one) = -1.0; 
    *(tmpm_one+1) = -1.0;
    m_one  = vm_one;
    
    //init
    v2df vinit;
    double *tmpinit;
    tmpinit = (double *)&vinit; 
    *(tmpinit) = 1.0; 
    *(tmpinit+1) = 2.0;
    init  = vinit;  
    
    //av
    v2df vav;
    double *tmpav;
    tmpav = (double *)&vav; 
    *(tmpav) = 1.0; 
    *(tmpav+1) = -1.0;
    av  = vav;

    //end

    Harmonic = zeta = poly = alt = Gregory = zero;

    for (k=1; k<=n; k++)
    {
        twoThrd += pow(2.0/3.0, k-1);
        sqrts   += 1.0/sqrt(k);
              k3 = k*k*k;
              s  = sin(k); c = cos(k);
        Flint   += 1.0/(k3 * s*s);
        Cookson += 1.0/(k3 * c*c);
    }

    for (kv=init; *(double *)(&kv)<=n; kv+=two)
    {
        poly    += one /(kv*(kv+one));
        Harmonic+= one / kv;
        zeta    += one /(kv*kv);
        alt     +=  av / kv;
        Gregory +=  av /(two*kv - one);
    }

    char name1[] = "(2/3)^k";
    double num = twoThrd;
    printf("%.9f\t%s\n",num,name1);


    char name2[] = "k^-0.5";
    num = sqrts;
    printf("%.9f\t%s\n",num,name2);


    //poly    
    double *tmp_poly = (double *)&poly;
    double ans_poly = *(tmp_poly) + *(tmp_poly+1);
    
    char name3[] = "1/k(k+1)";
    num = ans_poly;
    printf("%.9f\t%s\n",num,name3);
    //end poly

    char name4[] = "Flint Hills";
    num = Flint;
    printf("%.9f\t%s\n",num,name4);

    char name5[] = "Cookson Hills";
    num = Cookson;
    printf("%.9f\t%s\n",num,name5);    

    //Harmonic
    double *tmp_Harmonic = (double *)&Harmonic;
    double ans_Harmonic = *(tmp_Harmonic) + *(tmp_Harmonic+1);
    
    char name6[] = "Harmonic";
    num = ans_Harmonic;
    printf("%.9f\t%s\n",num,name6);
    
    //zeta
    double *tmp_zeta = (double *)&zeta;
    double ans_zeta = *(tmp_zeta) + *(tmp_zeta+1);
    
    char name7[] = "Riemann Zeta";
    num = ans_zeta;
    printf("%.9f\t%s\n",num,name7);


    //alt
    double *tmp_alt = (double *)&alt;
    double ans_alt = *(tmp_alt) + *(tmp_alt+1);

    char name8[] = "Alternating Harmonic";
    num = ans_alt;
    printf("%.9f\t%s\n",num,name8);
    
        
    //Gregory
    double *tmp_Gregory = (double *)&Gregory;
    double ans_Gregory = *(tmp_Gregory) + *(tmp_Gregory+1);
    
    char name9[] = "Gregory";
    num = ans_Gregory;
    printf("%.9f\t%s\n",num,name9);

    //end
    return 0;
}
#include <stdio.h>
#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <string.h>


int main(int argc, char **argv){
pairing_t pairing;

pbc_demo_pairing_init(pairing, argc, argv);

int n,ver,i_dash,m;
i_dash = 6;
m = 8;
n = 10;
int I[8]={1,2,3,5,6,-8,-9,-4};
element_t t[3*n],T[3*n],g,y,Y,temp_g1
          ,temp_zr,s,D_hat,D_tilde,D[n],u
          ,temp_gt,temp_gt2,h;

for(int i=0;i<3*n;i++)
{
    element_init_Zr(t[i], pairing);
    element_init_G1(T[i], pairing);
}



for(int i=0;i<n;i++)
{
    element_init_G1(D[i], pairing);
}

 element_init_Zr(y, pairing);

 element_init_Zr(temp_zr, pairing);
 element_init_Zr(s, pairing);
 element_init_Zr(u, pairing);
 element_init_Zr(h, pairing);


 element_init_G1(g, pairing);
 element_init_G1(temp_g1, pairing);
 element_init_G1(D_hat, pairing);



 element_init_GT(Y, pairing);
 element_init_GT(D_tilde, pairing);
 element_init_GT(temp_gt, pairing);
 element_init_GT(temp_gt2, pairing);



printf("\n************************* SYSTEM SETUP *************************\n\n\n");



element_random(g);
FILE *fptr;
fptr = fopen("setup.txt", "w");
ver = 1;

element_fprintf(fptr, "%d\n", n);
element_fprintf(fptr, "%d\n", i_dash);
element_fprintf(fptr, "%d\n", ver);

element_fprintf(fptr, "%B\n", g);
element_random(s);

for(int i=0 ; i<3*n;i++)
    {
    element_random(t[i]);

    element_pow_zn(T[i], g, t[i]);
  
    }

element_random(y);
element_pow_zn(temp_g1, g,y);
element_pairing(Y, g, temp_g1);
element_fprintf(fptr, "%B\n", Y);
element_fprintf(fptr, "%B\n", y);
element_fprintf(fptr, "%B\n", s);

    
    for(int i=0 ; i<3*n;i++)
    {
    element_fprintf(fptr, "%B\n", t[i]);
    }  
    for(int i=0 ; i<3*n;i++)
    {
    element_fprintf(fptr, "%B\n", T[i]);
    }  

fclose(fptr);


printf("\n************************* SECURE INDEX GENERATION *************************\n\n\n");

FILE *fptr2;
fptr2 = fopen("index.txt", "w");

element_pow_zn(D_hat,g,s);
element_fprintf(fptr2, "%B\n", D_hat);
element_pow_zn(D_tilde,Y,s);
element_fprintf(fptr2, "%B\n", D_tilde);

element_printf("D_hat = %B \nD_tilde = %B \n", D_hat,D_tilde);

for(int i=0;i<n;i++)
{
    element_pow_zn(D[i],T[2*n + i],s);
    
}

for(int i=0;i<m;i++)
{
    if(I[i]>=0)
    {
        element_pow_zn(D[I[i]],T[I[i]],s); //element_pow_zn(D[I[i]-1],T[i],s);
    }
    else
    {  
        int j = (-1)*I[i];
        element_pow_zn(D[j], T[n + j], s); //element_pow_zn(D[((-1)*I[i])-1],T[n+i],s);
    }
} 


//i'

element_from_hash(h, "hashofmessage", 13);

element_printf("%d\n",h);


element_invert(temp_zr,h);
element_mul_zn(temp_zr,s,temp_zr);
element_printf("%d\n\n",temp_zr);
element_pow_zn(D[i_dash],T[i_dash],temp_zr);
element_printf("D[%d]= %B \n\n",i_dash, D[i_dash]);

//i'


for(int i=0;i<n;i++)
{    
    element_printf("D[%d]= %B \n\n",i, D[i]);
    element_fprintf(fptr2, "%B\n", D[i]);
}








fclose(fptr2);
return 0;
}

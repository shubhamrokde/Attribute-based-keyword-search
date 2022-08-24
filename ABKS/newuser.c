#include <stdio.h>
#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <string.h>

int main(int argc, char **argv){
pairing_t pairing;

pbc_demo_pairing_init(pairing, argc, argv);

//printf("%s\n",argv[1]);
int n,m,o,i_dash,ver;
FILE *fptr2;
fptr2 = fopen("setup.txt", "r");
fscanf(fptr2,"%d",&n);
o = 6;
int I[8];
int S[6]={1,2,6,3,5,8};
 
element_t t[3*n],g,y,Y,temp_g1,xf,Yf_,
          ri[n],r,K_hat,temp_zr,K[n],F[n],s,
          Df_bar,temp_gt,temp_gt2;

for(int i=0;i<3*n;i++)
{
    element_init_Zr(t[i], pairing);

}

for(int i=0;i<n;i++)
{
    element_init_G1(K[i], pairing);
    element_init_G1(F[i], pairing);
    element_init_Zr(ri[i], pairing);
}

 element_init_Zr(y, pairing);
 element_init_Zr(xf, pairing);  
 element_init_Zr(r, pairing);
 element_init_Zr(temp_zr, pairing);
 element_init_Zr(s, pairing);

 element_init_G1(g, pairing);
 element_init_G1(temp_g1, pairing);
 element_init_G1(K_hat, pairing);

 element_init_GT(Y, pairing);
 element_init_GT(Yf_, pairing);
 element_init_GT(Df_bar, pairing);
 element_init_GT(temp_gt, pairing);
 element_init_GT(temp_gt2, pairing);





            printf("\n************************* NEW USER ENROLLMENT*************************\n\n\n");
            
            printf("n= %d\n",n);
            fscanf(fptr2,"%d",&i_dash);
            printf("n= %d\n",i_dash);
            fscanf(fptr2,"%d",&ver);
            printf("n= %d\n",ver);
         

            size_t si = 350;

            char *str;
            str = (char *) malloc (si);

            getline(&str,&si,fptr2);
            
            getline(&str,&si,fptr2);
            element_set_str(g,str,10);
            element_printf("g= %B\n",g);

            getline(&str,&si,fptr2);
            element_set_str(Y,str,10);
            element_printf("Y= %B\n",Y);
            
            getline(&str,&si,fptr2);
            element_set_str(y,str,10);
            element_printf("y= %B\n",y);

            getline(&str,&si,fptr2);
            element_set_str(s,str,10);
            element_printf("s= %B\n",s);
                
            
           for(int i=0;i<3*n;i++){
             getline(&str,&si,fptr2);
             element_set_str(t[i],str,10);
             element_printf("t[%d]= %B\n",i,t[i]);
            
           }
            
            fclose(fptr2);
           
            char* f="shubham";
            //gmp_scanf("%s",f);
            char* extension = ".txt";
            char fileSpec[strlen(f)+strlen(extension)+1];
            FILE *fptr;
            snprintf( fileSpec, sizeof( fileSpec ), "%s%s", f, extension );
            fptr = fopen(fileSpec, "w");


            element_random(xf);
            element_printf("xf= %B \n", xf);
            element_fprintf(fptr, "%B\n", xf);
            

            element_pow_zn(Yf_, Y, xf);
            element_printf("Yf_= %B \n", Yf_);
            
            for(int i=0;i<n;i++)
            {
                
                element_random(ri[i]);
                element_add(r, r, ri[i]);
                
            }
            
            element_printf("r= %B \n",r );
            element_sub(temp_zr, y, r);
            element_pow_zn(K_hat, g,temp_zr);
            element_printf("K_hat= %B \n", K_hat);
            element_fprintf(fptr, "%B\n", K_hat);

            element_printf("\n\n");
            for(int i=0;i<n;i++)
            {
                element_invert(temp_zr,t[n+i]);
                element_mul_zn(temp_zr,ri[i],temp_zr);
                element_pow_zn(K[i],g,temp_zr);
                //element_printf("K[%d]= %B \n",i,K[i] );
            }

            element_printf("\n\n");

            for(int i = 0 ;i < o; i++)
            {
                element_invert(temp_zr,t[S[i]]);
                element_mul_zn(temp_zr,ri[S[i]],temp_zr);
                element_pow_zn(K[S[i]],g,temp_zr);
                //element_printf("K[%d]= %B \n",S[i],K[S[i]] );
            } 

            for(int i=0;i<n;i++)
            {
              
                element_printf("K[%d]= %B \n",i,K[i] );
                element_fprintf(fptr, "%B\n", K[i]);
            }
            element_printf("\n\n");

            for(int i=0;i<n;i++)
            {
                element_invert(temp_zr,t[2*n + i]);
                element_mul_zn(temp_zr,ri[i],temp_zr);
                element_pow_zn(F[i],g,temp_zr);
                element_printf("F[%d]= %B \n",i,F[i] );
                element_fprintf(fptr, "%B\n", F[i]);
            }

            element_printf("\n\n");

            
            element_neg(temp_zr, s);
            element_pow_zn(Df_bar,Yf_,temp_zr);
            element_printf("Df_bar = %B \n",Df_bar );
            element_fprintf(fptr, "%B\n", Df_bar);

            fclose(fptr);



return 0;
}
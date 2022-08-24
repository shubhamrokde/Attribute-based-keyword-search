#include <stdio.h>
#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <string.h>


int main(int argc, char **argv){
pairing_t pairing;

pbc_demo_pairing_init(pairing, argc, argv);


int n,m,o,i_dash,ver;
n = 10;
i_dash = 6;
m = 8;
o = 6;
int I[8]={1,2,3,5,6,-8,-9,-4};
int S[6]={1,2,6,3,5,7};
 
element_t t[3*n],T[3*n],g,y,Y,temp_g1,xf,Yf_,
          ri[n],r,K_hat,temp_zr,K[n],F[n],s,
          Df_bar,D_hat,D_tilde,D[n],u,Q_hat,
          Q_tilde,Q[n],Qf[n],temp_gt,lhs,
          Q_star[n],rhs,temp_gt2,h,h_dash;





for(int i=0;i<3*n;i++)
{
    element_init_Zr(t[i], pairing);
    element_init_G1(T[i], pairing);
}

for(int i=0;i<n;i++)
{

    element_init_G1(K[i], pairing);
    element_init_G1(F[i], pairing);
    element_init_Zr(ri[i], pairing);
    element_init_G1(D[i], pairing);
    element_init_G1(Q[i], pairing);
    element_init_G1(Qf[i], pairing);
    element_init_G1(Q_star[i], pairing);

}

 element_init_Zr(y, pairing);
 element_init_Zr(xf, pairing);  
 element_init_Zr(r, pairing);
 element_init_Zr(temp_zr, pairing);
 element_init_Zr(s, pairing);
 element_init_Zr(u, pairing);
 element_init_Zr(Q_tilde, pairing);
 element_init_Zr(h, pairing);
 element_init_Zr(h_dash, pairing);

 element_init_G1(g, pairing);
 element_init_G1(temp_g1, pairing);
 element_init_G1(K_hat, pairing);
 element_init_G1(D_hat, pairing);
 element_init_G1(Q_hat, pairing);


 element_init_GT(Y, pairing);
 element_init_GT(Yf_, pairing);
 element_init_GT(Df_bar, pairing);
 element_init_GT(D_tilde, pairing);
 element_init_GT(temp_gt, pairing);
  element_init_GT(temp_gt2, pairing);
 element_init_GT(lhs, pairing);
 element_init_GT(rhs, pairing);



printf("\n************************* TRAPDOOR GENERATION *************************\n\n\n");

            element_random(u);


            FILE *fptr;
            fptr = fopen("shubham.txt", "r");
            
            size_t si = 350;
            char* str;
            str = (char *) malloc (si);


            getline(&str,&si,fptr);
            element_set_str(xf,str,10);
            element_printf("xf=%B\n",xf);

            getline(&str,&si,fptr);
            element_set_str(K_hat,str,10);
            element_printf("K_hat=%B\n",K_hat);

            for(int i=0;i<n;i++)
            {
                
            getline(&str,&si,fptr);
            element_set_str(K[i],str,10);
            element_printf("K[%d]=%B\n",i,K[i]);
            }

            printf("1234\n");

            for(int i=0;i<n;i++)
            {
            getline(&str,&si,fptr);
            element_set_str(F[i],str,10);
            element_printf("F[%d]=%B\n",i,F[i]);
            }

            printf("12345\n");
            getline(&str,&si,fptr);
            element_set_str(Df_bar,str,10);
            element_printf("Df_bar=%B\n",Df_bar);

            element_add(Q_tilde, u, xf);
            element_printf("Q_tilde= %B \n",Q_tilde);
            element_pow_zn(Q_hat,K_hat,u);
            element_printf("Q_hat= %B \n",Q_hat);

            for(int i=0;i<n;i++)
            {
              element_pow_zn(Q[i],K[i],u);
              element_pow_zn(Qf[i],F[i],u);
              element_printf("Q[%d]= %B \nQf[%d]= %B\n",i,Q[i],i,Qf[i]);
            }
            fclose(fptr);

            //i'
            
            
            
            FILE *fptr2;
            fptr2 = fopen("setup.txt", "r");
            fscanf(fptr2,"%d",&n);
            fscanf(fptr2,"%d",&i_dash);
            fclose(fptr2);
            printf("n = %d  i = %d\n",n,i_dash);
            
            FILE *fptr3;
            fptr3 = fopen("index.txt", "r");

            getline(&str,&si,fptr3);
            element_set_str(D_hat,str,10);
            element_printf("D_hat=%B\n",D_hat);

            getline(&str,&si,fptr);
            element_set_str(D_tilde,str,10);
            element_printf("D_tilde=%B\n",D_tilde);

            for(int i=0;i<n;i++)
            {
                getline(&str,&si,fptr);
                element_set_str(D[i],str,10);
                element_printf("D[%d]=%B\n",i,D[i]);
            }

            fclose(fptr3);

            
            element_from_hash(h_dash, "hashofmessage", 13);
            
            element_mul_zn(temp_zr,h_dash,u);
            element_printf("%d\n\n",temp_zr);
            element_pow_zn(Q[i_dash],K[i_dash],temp_zr);
            element_pow_zn(Qf[i_dash],F[i_dash],temp_zr);
            element_printf("Q[%d]= %B \nQf[%d]= %B\n",i_dash,Q[i_dash],i_dash,Qf[i_dash]);
            //i'
            
            
            
          
        
            printf("\n************************* SEARCH *************************\n\n\n");

            element_pow_zn(temp_gt,D_tilde,Q_tilde);
            element_mul(lhs,temp_gt,Df_bar);
            element_printf("LHS= %B \n",lhs);

            for(int i=0;i<n;i++)
            {
              element_set(Q_star[i],Qf[i]);
            }
            for(int i=0;i<m;i++)
            {
                if(I[i]>=0)
                {
                element_set(Q_star[I[i]],Q[I[i]]); // element_set(Q_star[I[i]-1],Q[i]); 
                }
                else{
                    int j = -I[i];
                    element_set(Q_star[j],  Q[j]); // element_set(Q_star[(-1)*I[i]-1],Q[i]);
                }

            }

            for(int i=0;i<n;i++)
            {
              
              element_printf("Q_star[%d]= %B \n",i,Q_star[i]);
            }



            element_pairing(temp_gt, D[0], Q_star[0]);
            element_set(rhs,temp_gt);
            //element_printf("RHS= %B \n",rhs);
            for(int i=1;i<n;i++)
            {
                element_pairing(temp_gt, D[i], Q_star[i]);
                element_mul(rhs,rhs,temp_gt);
                //element_printf("RHS= %B \n",rhs);
            }

            element_mul_zn(temp_zr,s,u);
            element_mul_zn(temp_zr,temp_zr,r);
            element_pairing(temp_gt,g,g);
            element_pow_zn(temp_gt,temp_gt,temp_zr);
              if (!element_cmp(temp_gt, rhs))
              {
                //printf("\n*******************************   CORRECTNESS   **************************************\n\n\n");
                //printf("MESSAGE IS VALID!\n\n\n\n");
              }
              else
              {
                //printf("WRONG\n");
              }


            element_pairing(temp_gt, D_hat, Q_hat);
            element_mul(rhs,temp_gt,rhs);
            element_printf("RHS= %B \n",rhs);

              if (!element_cmp(lhs, rhs))
              {
                printf("\n*******************************   CORRECTNESS   **************************************\n\n\n");
                printf("USER IS VERIFIED !\n\n\n\n");
              }
              else
              {
                printf("USER IS NOT VERIFIED\n");
              }


return 0;
}
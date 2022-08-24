#include <pbc/pbc.h>
#include <pbc/pbc_test.h>
#include <string.h>

int main(int argc, char **argv)
{
  pairing_t pairing;
  pbc_demo_pairing_init(pairing, argc, argv);
   double Ri,Rj;
  FILE *file;
  file=fopen("rmatrix.txt", "r");
  fscanf(file, "%lf", &Ri);
  fscanf(file, "%lf", &Rj);
  double r[(int)Ri][(int)Rj];
 for(int i = 0; i < Ri; i++)
  {
      for(int j = 0; j < Rj; j++) 
      {
  //Use lf format specifier, %c is for character
       if (!fscanf(file, "%lf", &r[i][j])) 
           break;

       printf("%d\n",(int)r[i][j]);    

      }

  }
  fclose(file);


  mpz_t R[(int)Ri][(int)Rj] ;
  element_t s, v2, w2, v[(int)Rj], w[(int)Rj], lambda[(int)Ri], omega[(int)Ri], t1, t2, M, g, C0, gs, t3, C1[(int)Ri], C2[(int)Ri], C3[(int)Ri], rho, alpha[(int)Ri], y[(int)Ri], t4, t5, t6, t7, t8, t9, t10, t11, sk[(int)Ri], user, t12, t13, t14, t15, t16, t17, t18, dec[(int)Ri], t20;
 
  // ******************Initialize Pairing********************


 for(int i = 0; i < Ri; i++)
  {
      for(int j = 0; j < Rj; j++) 
      {
          mpz_init_set_d(R[i][j], r[i][j]);
      }

  }
  

  for (int i = 0; i < Rj; i++)
  {
    element_init_Zr(v[i], pairing);
    element_init_Zr(w[i], pairing);
  }
 
  for (int i = 0; i < Ri ; i++)
  {
    element_init_Zr(lambda[i], pairing);
    element_init_Zr(omega[i], pairing);
    element_init_GT(C1[i], pairing);
    element_init_G1(C2[i], pairing);
    element_init_G1(C3[i], pairing);
    element_init_Zr(alpha[i], pairing);
    element_random(alpha[i]);
    element_init_Zr(y[i], pairing);
    element_random(y[i]);
    element_init_G1(sk[i], pairing);
    element_init_GT(dec[i], pairing);
  }
  
  element_init_Zr(t20, pairing);
  element_init_Zr(rho, pairing);
  element_init_Zr(t1, pairing);
  element_init_Zr(t2, pairing);
  element_init_Zr(s, pairing);
  element_init_Zr(v2, pairing);
  element_init_Zr(w2, pairing);
  element_init_Zr(t6, pairing);
  element_init_Zr(t9, pairing);

  element_init_G1(g, pairing);
  element_init_G1(gs, pairing);
  element_init_G1(t4, pairing);
  element_init_G1(t7, pairing);
  element_init_G1(t10, pairing);
  element_init_G1(t11, pairing);
  element_init_G1(user, pairing);
  element_init_G1(t12, pairing);
  element_init_G1(t13, pairing);

  element_init_GT(t3, pairing);
  element_init_GT(t5, pairing);
  element_init_GT(C0, pairing);
  element_init_GT(M, pairing);
  element_init_GT(t8, pairing);
  element_init_GT(t14, pairing);
  element_init_GT(t15, pairing);
  element_init_GT(t16, pairing);
  element_init_GT(t17, pairing);
  element_init_GT(t18, pairing);

  element_random(s);

  
  element_random(g);
  element_set(v[0], s); // setting first element of vector as s
  for(int i=1 ; i<Rj;i++)
  {
      element_random(v2);
    element_set(v[i], v2);
  }
  element_set0(w[0]); // setting first element as zero
  for(int i=1 ; i<Rj ;i++)
  {
    element_random(w2);
    element_set(w[i], w2);
  }
  printf("*******************************   ENCRYPTION   **************************************\n\n\n");

  printf("VALUES OF V AND W\n");
  element_printf("%B  %B %B %B\n", v[0], v[1], w[0], w[1]);
  printf("\n\n");

  printf("VALUES OF LAMBDA\n");
  for (int i = 0; i < Ri; i++)
  {
    element_mul_mpz(lambda[i], v[0], R[i][0]);
    for(int j=1 ;j<Rj ;j++){
      element_mul_mpz(t2, v[j], R[i][j]);
      element_add(lambda[i], lambda[i], t2);
    }
    element_printf(" lambda [%d] is  %B \n", i, lambda[i]);
  }
  element_add(t20, lambda[1], lambda[2]);
  printf("\n");

  printf("VALUES OF T1,T2,OMEGA");
  printf("\n");
  for (int i = 0; i < Ri; i++)
  {
    element_mul_mpz(omega[i], w[0], R[i][0]);
    for(int j=1 ;j<Rj ;j++){
      element_mul_mpz(t2, w[j], R[i][j]);
      element_add(omega[i], omega[i], t2);
    }

    element_printf("Omega[%d] is %B \n", i, omega[i]);
  }
  printf("\n");

  FILE *fp;
    char str[100];
    char* filename = "input.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, 100, fp) != NULL);
    fclose(fp);
     printf("%s", str);
  printf("\n\n\n\n");

  element_from_hash(M, str, strlen(str));
  element_pow_zn(gs, g, s);
  element_pairing(t3, gs, g);
  element_mul(C0, M, t3);

  printf("public\n\n");
  printf("VALUE OF C0\n");
  element_printf("%B \n\n\n\n ", C0);

  for (int i = 0; i < Ri; i++)
  {
    element_random(rho);

    //for C1
    printf("VALUE OF C1 FOR ROW : %d\n", i);
    element_pow_zn(t4, g, lambda[i]);
    element_pairing(t5, t4, g);
    element_mul_zn(t6, alpha[i], rho);
    element_pow_zn(t7, g, t6);
    element_pairing(t8, t7, g);
    element_mul(C1[i], t5, t8);
    element_printf("%B \n", C1[i]);
    //for C2   

    printf("VALUE OF C2 FOR ROW : %d\n", i);
    element_pow_zn(C2[i], g, rho);
    element_printf("%B \n", C2[i]);
    //for C3
    printf("VALUE OF C3 FOR ROW : %d\n", i);
    element_mul_zn(t9, y[i], rho);
    element_pow_zn(t10, g, t9);
    element_pow_zn(t11, g, omega[i]);
    element_mul(C3[i], t10, t11);

    element_printf("%B \n", C3[i]);
  }

  printf("Sender sends C1[i],C2[2],C3[3],C0, R matrix\n\n ");

  printf("*******************************   DECRYPTION   **************************************\n\n\n");

  element_from_hash(user, "Alice Bob Eve", 14);

  // Secret Key of user
  for (int i = 0; i < Ri; i++)
  {
    element_pow_zn(t12, user, y[i]);
    element_pow_zn(t13, g, alpha[i]);
    element_mul(sk[i], t12, t13);
  }

  // step a
  for (int i = 0; i < Ri; i++)   // Ri ko Rj kar ke dekh
  {
    element_pairing(t14, user, C3[i]);
    element_mul(t15, C1[i], t14);
    element_pairing(t16, sk[i], C2[i]);

    element_div(dec[i], t15, t16);
    element_printf("DEC VALUE: %B\n", dec[i]);
  }
  printf("PRODUCT OF DEC[I]s \n\n");
  element_mul(t17, dec[3], dec[4]);
  element_mul(t17, t17 , dec[0]);
  element_printf("\n\n%B \n\n", t17);

  element_div(t18, C0, t17);
  printf("COMPARISON BETWEEN ORIGINAL MESSAGE AND DECRYPTED MESSAGE\n\n");
  element_printf("%B \n %B\n\n ", M, t18);
  if (!element_cmp(t18, M))
  {
    printf("*******************************   CORRECTNESS   **************************************\n\n\n");
    printf("MESSAGE IS VALID!\n\n\n\n");
  }
  else
  {
    printf("WRONG\n");
  }

  element_clear(s);
  element_clear(v2);
  element_clear(w2);
  element_clear(v[0]);
  element_clear(v[1]);
  element_clear(w[0]);
  element_clear(w[1]);
  element_clear(lambda[0]);
  element_clear(lambda[1]);
  element_clear(lambda[2]);
  element_clear(lambda[3]);
  element_clear(lambda[4]);
  element_clear(omega[0]);
  element_clear(omega[1]);
  element_clear(omega[2]);
  element_clear(omega[3]);
  element_clear(omega[4]);
  element_clear(t1);
  element_clear(t2);
  element_clear(t3);
  element_clear(t4);
  element_clear(t5);
  element_clear(t6);
  element_clear(t7);
  element_clear(t8);
  element_clear(t9);
  element_clear(t10);
  element_clear(t11);
  element_clear(t12);
  element_clear(t13);
  element_clear(t14);
  element_clear(t15);
  element_clear(t16);
  element_clear(t17);
  element_clear(t18);
  element_clear(t20);
  element_clear(M);
  element_clear(g);
  element_clear(C0);
  element_clear(C1[0]);
  element_clear(C1[1]);
  element_clear(C1[2]);
  element_clear(C1[3]);
  element_clear(C1[4]);
  element_clear(C2[0]);
  element_clear(C2[1]);
  element_clear(C2[2]);
  element_clear(C2[3]);
  element_clear(C2[4]);
  element_clear(C3[0]);
  element_clear(C3[1]);
  element_clear(C3[2]);
  element_clear(C3[3]);
  element_clear(C3[4]);
  element_clear(gs);
  element_clear(rho);
  element_clear(alpha[0]);
  element_clear(alpha[1]);
  element_clear(alpha[2]);
  element_clear(alpha[3]);
  element_clear(alpha[4]);
  element_clear(y[0]);
  element_clear(y[1]);
  element_clear(y[2]);
  element_clear(y[3]);
  element_clear(y[4]);
  element_clear(sk[0]);
  element_clear(sk[1]);
  element_clear(sk[2]);
  element_clear(sk[3]);
  element_clear(sk[4]);
  element_clear(user);
  element_clear(dec[0]);
  element_clear(dec[1]);
  element_clear(dec[2]);
  element_clear(dec[3]);
  element_clear(dec[4]);
  pairing_clear(pairing);

  return 0;
}


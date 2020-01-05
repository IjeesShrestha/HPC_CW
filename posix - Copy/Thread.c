#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>

/***********************************************************************
*******
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2
uppercase
  letters and a 2 digit integer. Your personalised data set is included
in the
  code.

  Compile with:
    cc -o Thread Thread.c -lcrypt -pthread

  If you want to analyse the results then use the redirection operator
to send
  output to a file that you can view using an editor or the less
utility:

    ./Thread > ijThread_results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
************************************************************************
******/
int n_passwords = 4;

char *encrypted_passwords[] = {

"$6$KB$5B3KGhhav2/OsufUGxdicHWDBJM7ojVt0DvSVVwcpHL2OiiiBnq.b6hHZ/uYsi9PETZ6XDOW9/xOOrcbIXcfE/",
  "$6$KB$1vCJQRsKAizZvuTjEqLE./zeAqZ7AdqzTdx5Tob.bQDRGlXOEVkNhuqMorBSvCp4fP0eoNm2wULs3DRABbrLQ/",
  "$6$KB$F1y/Jfx/DeNeEL7YbiYjdZoJsNCQ.6RYAe4U3ucZPHNGfSjaFd1.f9fLOkbQ6mq/IhbuFOuPs74HgnfZBMhjV/",
  "$6$KB$3DdCMYkSjEZX4kRXiSK2ZW9XksbV7j162Eg6xOlzC3C7qxRIAetCB6Sm7m4soWwVc7hmnYXDNtDoxlfD.2LPa0"
};

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

/**
 This function can crack the kind of password explained above. All
combinations
 that are tried are displayed and when the password is found, #, is put
at the
 start of the line. Note that one of the most time consuming operations
that
 it performs is the output of intermediate results, so performance
experiments
 for this kind of program should not include this. i.e. comment out the
printfs.
*/

void ynw_a()
{
  int i;
pthread_t t1, t2;

    void *kernel_function_1();
    void *kernel_function_2();
for(i=0;i<n_passwords;i<i++) {
   
    
    pthread_create(&t1, NULL,kernel_function_1, encrypted_passwords[i]);
    pthread_create(&t2, NULL,kernel_function_2, encrypted_passwords[i]);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
 }
}

void *kernel_function_1(char *salt_and_encrypted){
  int e, h, s;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(e='A'; e<='M'; e++){
    for(h='A'; h<='Z'; h++){
      for(s=0; s<=99; s++){
        sprintf(plain, "%c%c%02d", e,h,s);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } 
      }
    }
  }
  printf("%d solutions explored\n", count);
}


void *kernel_function_2(char *salt_and_encrypted){
  int m, n, o;     // Loop counters
  char salt[7];    // String used in hahttps://www.youtube.com/watch?v=L8yJjIGleMwshing the password. Need space
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(m='N'; m<='Z'; m++){
    for(n='A'; n<='Z'; n++){
      for(o=0; o<=99; o++){
        sprintf(plain, "%c%c%02d", m,n,o);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

//Calculating time

int time_difference(struct timespec *start, struct timespec *finish, long long int *difference)
 {
	  long long int ds =  finish->tv_sec - start->tv_sec; 
	  long long int dn =  finish->tv_nsec - start->tv_nsec; 

	  if(dn < 0 ) {
	    ds--;
	    dn += 1000000000; 
  } 
	  *difference = ds * 1000000000 + dn;
	  return !(*difference > 0);
}
int main(int argc, char *argv[])
{
  	
	struct timespec start, finish;   
  	long long int time_elapsed;

  	clock_gettime(CLOCK_MONOTONIC, &start);

  	
	
    		ynw_a();
  	
	clock_gettime(CLOCK_MONOTONIC, &finish);
	  time_difference(&start, &finish, &time_elapsed);
	  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
		                                 (time_elapsed/1.0e9)); 
  return 0;
}

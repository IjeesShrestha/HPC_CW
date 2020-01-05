#include <stdio.h>
#include <cuda_runtime_api.h>
#include <time.h>

/****************************************************************************
 * An experiment with cuda kernel invocation parameters. 2x3x4 threads on  
 * one block should yield 24 kernel invocations.
 *
 * Compile with:
 *   nvcc -o cudapass cudapass.cu
 *
 * Dr Kevan Buckley, University of Wolverhampton, January 2018
 *****************************************************************************/
__device__ int is_a_match(char *attempt){
char plain_password1[] ="BB1111";
char plain_password2[] ="CC2112";
char plain_password3[] ="AB3113";
char plain_password4[] ="AC4114";

char *t = attempt;
char *y = attempt;
char *u = attempt;
char *r = attempt;
char *ppp1 = plain_password1;
char *ppp2 = plain_password2;
char *ppp3 = plain_password3;
char *ppp4 = plain_password4;

 while(*t ==*ppp1){
  if(*t == '\0')
{
printf("password:%s\n", plain_password1);
break;
}
t++;
ppp1++;
}
while(*y ==*ppp2){
  if(*y == '\0')
{
printf("password:%s\n", plain_password2);
break;
}
y++;
ppp2++;
}
while(*u ==*ppp3){
  if(*u == '\0')
{
printf("password:%s\n", plain_password3);
break;
}
u++;
ppp3++;
}
while(*r ==*ppp4){
  if(*r == '\0')
{
printf("password: %s\n", plain_password4);
return 1;
}
r++;
ppp4++;
}
return 0;
}

__global__ void kernel(){
char i1, i2, i3, i4;

char password[7];
password[6] ='\0';

int i = blockIdx.x +65;
int j = threadIdx.x+65;
char firstMatch =i;
char secondMatch =j;

password[0] =firstMatch;
password[1] =secondMatch;
for(i1='0'; i1<='9'; i1++){
for(i2='0'; i2<='9'; i2++){
for(i3='0'; i3<='9'; i3++){
for(i4='0'; i4<='9'; i4++){
password[2] =i1;
password[3] =i2;
password[4] =i3;
password[5] =i4;
if(is_a_match(password)){
}
else{
//printf("tried: %s\n",password);
}
     }
    }
  }
}
}

int time_difference(struct timespec *start, struct timespec *finish,long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec;
  long long int dn =  finish->tv_nsec - start->tv_nsec;

  if(dn < 0 ) {
    ds--;
    dn += 1000000000;
  }
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}


int main() {

 struct timespec start, finish;  
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);

  kernel<<<26,26>>>();
cudaThreadSynchronize();
 

 clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));
return 0;
}

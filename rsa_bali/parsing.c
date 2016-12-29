#include <stdio.h>
#include <string.h>

/*

we have n size of 8 bytes

BLOCK FORMAT:
FIRST BLOCK
  1ST CHAR = CURRENT BLOCK NUMBER
  2ND CHAR = HOW MANY BLOCKS MESSAGE IS SLICED TO
  3RD CHAR = 'R'
  4TH CHAR = 'S'
  5TH CHAR = 'A'
  6TH CHAR = '\0'


*/
//unsigned long long parse(unsigned char msg, unsigned char blksiz){

//*
int main(void){
  char msg[] = "Ebesinin";
  unsigned char blksiz = 4;
//*/

  unsigned long long msg_siz = sizeof(msg) - 1;
  unsigned long long prsdblks_siz = (msg_siz / blksiz) + 1;

  if (!(prsdblks_siz <254)) {
    return 0;
  }

  unsigned long long prsdblks[prsdblks_siz + 2][blksiz];
  char m[prsdblks_siz * blksiz] = {65};

  strncpy(m, msg, (prsdblks_siz * blksiz));

  /*  PADDING
  */

  /*  SLICING   */

printf("%s\n", m);
printf("%s\n", msg);

prsdblks[0][0] = 0;
prsdblks[0][1] = prsdblks_siz + 2;
prsdblks[0][2] = 82;
prsdblks[0][3] = 83;
prsdblks[0][4] = 65;
prsdblks[0][5] = 0;
// {0, prsdblks_siz, "R", "S", "A", 0}
unsigned char j;
unsigned long long i;
unsigned long long c;
for (i = 1; i < prsdblks_siz + 1; i++) {
  prsdblks[i][0] = i;
  for (j = 1; j < blksiz + 1; j++) {
    prsdblks[i][j] =(unsigned long long) m[c];
    printf("%c", prsdblks[i][j]);
    c++;
  }
}

for (i = 0; i < prsdblks_siz + 2; i++) {
        printf("\n");
        for (j = 0; j < blksiz+2; j++) {
            printf("%c", prsdblks[i][j]);
        }
    }

prsdblks[prsdblks_siz + 1][0] = prsdblks_siz + 1;
prsdblks[prsdblks_siz + 1][1] = 69;
prsdblks[prsdblks_siz + 1][2] = 79;
prsdblks[prsdblks_siz + 1][3] = 77;
prsdblks[prsdblks_siz + 1][4] = 66;
prsdblks[prsdblks_siz + 1][5] = 0;
//prsdblks[prsdblks_siz + 1] = {(prsdblks_siz + 1), "E", "O", "F", "M", 0}




printf("%s\n", prsdblks[0]);
}

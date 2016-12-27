//DECRYPTING or the side that wants to receive encrypted messages

//Public Key Initiation
#define E 3
#define BITSIZE 32
//public key with smallest data type possible
unsigned long long p = rsaprime_gen (E);
//generate prime p with gcd(e, p-1)=1
unsigned long long q = rsaprime_gen (E);
//generate prime q with gcd(e, q-1)=1
unsigned long long n = p * q;
//calculate n
unsigned long long d = modInverse(E, n);//////////////////
//calculate the modular inverse of E
send(E, n);
//send the public key E, and modulus n to the encrypting side

//
//WAIT FOR RECEIVER TO ENCRYPT THE MESSAGE AND SEND YOU THE CIPHERTEXT
//

receive(ct);
//take the ciphertext ct = p^e % n
unsigned long long pt = pow_mod (ct, d, n);
//calculate the pt as a number
unsigned char *m = numToText(pt);
//convert the number to text so it can be read

//ENCRYPTING or the side that wants to send encrpted messages

unsigned char *m = "the message";
//construct the message
unsigned long long pt = textToNum(*m);
//convert the messsage to number so that it can be used algebraically
receive(e, n);
//take the public keys
unsigned long long ct = pow_mod (pt, e, n);
//calculate the ct with sent public keys e and n
send(ct);
//send the ciphertext

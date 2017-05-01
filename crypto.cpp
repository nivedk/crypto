/*Write functions to implement the following:-
    1. Modulo addition, Multiplication and Exponentiation
    2. GCD and inverse Modulo n.
    3. Discrete logarithm (using either Pohlig-Hellman, index calculus, Pollard-rho
or the basic Baby Step Giant Step algorithm)
    4. RSA Key generation
    5. RSA encryption
    6. RSA decryption
    7. Field Operations in Prime Fields and Binary Fields.

NOTE that the project is optional, it does not count towards your final score.
However, you receive brownie points for completing the project which may be of use
if your final score is between two grade ranges.

Instructions:
        A team of two person works on a project. You should collaborate with your
team member. However collaborating across teams is not permitted. Violation
of this rule will be strictly dealt with.

======================================================================================================
This program has been written by

Pradumn Kumar : D3 : 16d260009
Kodavali Nived: D3 : 16d260012

The program includes the following functions:

>>int modAdd(int a, int b, int n) (this function returns the modulo of the sum of a and b with respect to n)

>>int modMult(int a, int b, int n) (this function returns the modulo of the sum of a and b with respect to n.)

>>int modExp(int a, int b, int n) (this function computes (a^b)mod n)

>>int computeInverse(int b,int c) (This function returns inverse c mod b)

>>int gcd(int m, int n)  (this is a recursive function that returns the gcd of two numbers m and n. however m>=n)

>>bool isPrime(int a)  (This function returns a boolean value indicating whether the parameter provided is a prime number)

>>vector<int> primeList()  (This function generates a list of the primes within the range of 100000. It returns a vector containing the prime numbers. Two of these prime numbers picked at random are used in the rsa encryption.)

>>map<string,int> keyGen()  (This function generates the public key and the private key which are needed for RSA standard encryption)

>>int encrypt(int m,int e,int n)  (This function takes care of the encryption part of the message according to the RSA standards)

>>int decrypt(int d, int c, int n)  (This function decrypts the message encrypted by the encrypt function according to RSA standard)

>>int main() (This function starts the execution and a substantial part of discrete logarithm is also in this function)

The present version of rsa uses int and can deal with messages of the size 7 digits and a few small 8 digit numbers within reasonable time. The prime numbers it uses range between 2 and 10000 (randomly selected) keeping the size int in mind.



 */

#include<iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
//#include <math>
#include <map>
#include<time.h>
using namespace std;

//this function returns the modulo of the sum of a and b with respect to n
int modAdd(int a, int b, int n){
        return((a%n + b%n)%n);
}

// this function returns the modulo of the sum of a and b with respect to n.
int modMult(int a, int b, int n){
        return((a%n*b%n)%n);
}

// this function computes (a^b)mod n
int modExp(int a, int b, int n){
        long int result = 1;;
        int temp = a%n;
        for(int i = 0; i<b; i++){
                result = (result*temp)%n;
                //cout<<"******"<<result<<endl;

        }

        //if(result < 0)result += n;

        return result;
}

//returns multiplicative inverse of a(mod b)
//assuming a, b are relatively prime
//implements extended euclidean algorithm (i dont know how it works)
int modInv(int a, int b){

}

// this method is based on sir's version from his book along with a few modifications. write own version later if time permits
//This function returns inverse c mod b
int computeInverse(int b,int c){
        int old1 = 1;
        int new1 = 0;
        int old2 = 0;
        int new2 = 1;
        int b1 = b;
        int c1 = c;
        int r = 2;
        while(r>1){
                int q = b1/c1;
                r = b1%c1;
                int temp1 = old1-new1*q;
                old1 = new1;
                new1 = temp1;
                int temp2 = old2-new2*q;
                old2 = new2;
                new2 = temp2;
                b1 = c1;
                c1 = r;
        }
        if(new2<0) new2 = new2+b;
        return new2;
}

// m>=n
//this is a recursive function that returns the gcd of two numbers m and n. however m>=n
int gcd(int m, int n){
        if(m%n == 0) return n;
        else return gcd(n,m%n);

}

//This function returns a boolean value indicating whether the parameter provided is a prime number
bool isPrime(int a){
    for(int i = 2;i<sqrt(a)+1;i++){
        if((a%i)== 0)return 0;
    }
    return 1;
}

//This function generates a list of the primes within the range of 100000. It returns a vector containing the prime numbers. Two of these prime numbers picked at random are used in the rsa encryption.
vector<int> primeList(){
    vector<int> primes(0);
	int x,count = 0;
	for(int i = 0; i<10000;i++){

		if(isPrime(i)) {
		    primes.push_back(1);
			primes[count] = i;
			count++;
			x = i;
		}
	}
	//cout<<x<<endl<<count;
	return primes;
}

//This function generates the public key and the private key which are needed for RSA standard encryption
map<string,int> keyGen(){
	vector<int> primes = primeList();
	int size = primes.size() -2;
	/*for(int i = 0;i<15;i++){
		cout<<primes[rand()%size]<<endl;
	}*/
	
	// sets a seed which is a random number based on the current time
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	int p = primes[rand()%size-1];
	int q = primes[rand()%size];
	//int p = 11;
	//int q = 13;
	int totient = (p-1)*(q-1);
	int e = rand()%10000;
	while(gcd(e,totient)!=1){
		e = rand()%10000;
	}
	//e = 7;
	int n = p*q;
	//int n = 86609;
	//totient = 86016;

	int d = computeInverse(totient,e);
	cout<<"p(first prime)   "<<p<<endl;
	cout<<"q(second prime)   "<<q<<endl;
	cout<< "tot(euler totient)  "<<totient<<endl;
	cout<<"d(private key)  "<<d<<endl;
	cout<<"e (public key) "<<e<<endl;
	cout<<" n (public key  modulo) "<<n<<endl;

	map<string,int>values;
	values["p"] = p;
	values["q"] = q;
	values["tot"] = totient;
	values["e"] = e;
	values["n"] = n;
	values["d"] = d;
	return values;

}

//This function takes care of the encryption part of the message according to the RSA standards
int encrypt(int m,int e,int n){
	/*int c = m%n;
	for(int i = 0;i<e-1;i++){
		c = modMult(c,m,n);
	}*/
	//cout<<" message  "<<m<<endl;
	int c = modExp(m,e,n);
	//cout<<"c  "<<c<<endl;
	return c;
}

//This function decrypts the message encrypted by the encrypt function according to RSA standard
int decrypt(int d, int c, int n){
	//int m = c%n;
	/*for(int i = 0; i<d-1;i++){
		m = modMult(m,c,n);
	}*/
	int m = modExp(c,d,n);
	cout<<"message after decryption   "<<m<<endl;
	return m;
}

//This function starts the execution and a substantial part of discrete logarithm is also in this function
int main(){
        //cout<<modAdd(34567,123,156)<<endl;
        //cout<<modMult(34567,123,156)<<endl;
        //cout<<modExp(34567,123,156)<<endl;
        //cout<<ComputeInverse(23487633,100030001)<<endl;
        //cout<<gcd(11134572,2234156)<<endl;


	int a,b,c,count=5,result;
	cout<<"please enter the parameters a,b,c for discrete logarithm"<<endl;
    	cin>>a>>b>>c;
    	int arr[5];
    	arr[0]=1;
    	int r=a;
   	 for(int i=1;i<5;i++)
    	{
    	    arr[i]=(arr[i-1]*a)%c;
   	 }
   	 int n=computeInverse(a,c);
   	 n=int(pow(n,5))%c;
  	  int x=(n*b)%c;
  	  bool found=0;
  	  while(found==0)
  	  {
   	     for(int i=0;i<5;i++)
   	     {
   	         if(x==arr[i])
    	        {
     	           found=1;result=count+i;break;
      	      }
     	   }
      	  x=(n*x)%c;
      	  count+=5;
   	 }
   	 cout<<"The result is"<<result<<endl;
        map<string, int> values = keyGen();
	cout<< "please enter a message you would like to transmit using rsa encryption.(Max 7 digits and small 8 digit integers"<<endl;
	
        int m = 10000000;
	cin>>m;
        int crypt = encrypt(m,values["e"],values["n"]);
        int k = decrypt(values["d"], crypt, values["n"]);
        cout<<"message  "<<m<<"    encrypted    "<<crypt<<"    decrypted    "<<k<<endl;

}

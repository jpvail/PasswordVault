#include<iostream> 
#include<memory> 
using namespace std; 


void rword (char *word)
{
int len = rand () % 6 + 1;
word [len] = 0;
while (len) word [--len] = 'a' + rand () % 26;
}

int main ()
{
	char word[7];
	char word2[7];
	int x=0;
	srand(time(0));
	while (x<100000) 
	{
	  rword(word);
	  rword(word2);
	  cout << word << ' ' << word2 << endl; 
	  //printf ("%s\n", word);
	  x++;
	}
}

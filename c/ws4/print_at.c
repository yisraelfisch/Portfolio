/* A program to to return A-pressed or T-pressed 
on the terminal if pressed A/T keys respectively and exit terminal if Esc
ker is pressed*/
/* Author: yisrael fisch*/

#include <stdio.h> /*printf, scanf*/

/*function that write commands to the termunal*/
int system (const char *command);

/*function that execute the purpose of the program with nestted if*/
void IfEchoTOrA()
{	
	char tipe = 0;

	
	while(27 != tipe)
	{
		scanf("%c", &tipe);
		if('A' == tipe || 'a' == tipe)
		{
			printf("A-pressed\n");
		}	
		else if ('T' == tipe || 't' == tipe)
			{
			printf("T-pressed\n");
			}
	}
}	

/*function that execute the purpose of the program with switch/case */
void SwitchEchoTOrA()
{
char tipe = 0;
	while(27 != tipe)
	{
	scanf("%c", &tipe);

		switch(tipe)
    	{
        	case 't': /*you can order different cases to do the same thing*/
        	case 'T':
            	printf("T-pressed\n");
            	break;

        	case 'a':
        	case 'A':
            	printf("A-pressed\n");
            	break;
    	}
    }	
}
/*the function that the lookup table pointing to at index 'a' and 'A'*/
void Apressed()
{
	printf("A-pressed\n");	
}
/*the function that the lookup table pointing to at index 't' and 'T'*/
void Tpressed()
{
	printf("T-pressed\n");	
}
/*the function that the lookup table pointing to at all other indexes*/
void Nothing()
{

}

/*function that execute the purpose of the program with lookup table*/
void LutEchoTOrA()
{
	size_t i = 0;
	char tipe = 0;
	typedef void (*fp)();/*are lookup table is actually  ann array of function pointers*/
	fp lut[128];
	for(i = 0 ; i < 128; ++i)
	{
		lut[i] = Nothing;/*i initiate all the indexes to point to Nothing function*/
	} 
	lut['a'] = Apressed;/*i initiate  those indexes to point to Apressed/Tpressed function*/
	lut['A'] = Apressed;
	lut['t'] = Tpressed;
	lut['T'] = Tpressed;

	
	while(27 != tipe)
	{
		scanf("%c", &tipe);
		(*lut[(size_t)tipe])();/*i called the function in index[tipe] according to the user's typing*/
	}

}

int main ()
{


system("stty -icanon -echo");

/*IfEchoTOrA();
SwitchEchoTOrA();*/
LutEchoTOrA();
system("stty icanon echo");

return 0;
}




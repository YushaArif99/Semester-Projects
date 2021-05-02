
#include<math.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<string.h>

double numi = 0, den = 0, fact[10];

char arr[12];




void Display ()
{

printf ("Degree\t\tRadian\t\t\tRadian In Form Of Fraction    ");

printf ("\n0\t\t(0*PIE)/180\t\t0/1");

printf ("\n10\t\t(10*PIE)/180\t\t1746/10000");

printf ("\n20\t\t(20*PIE)/180\t\t3491/10000");

printf ("\n30\t\t(30*PIE)/180\t\t5236/10000");

printf ("\n40\t\t(40*PIE)/180\t\t6982/10000");

printf ("\n45\t\t(45*PIE)/180\t\t7855/10000");

printf ("\n60\t\t(60*PIE)/180\t\t10473/10000");

printf ("\n70\t\t(70*PIE)/180\t\t12219/10000");

printf ("\n80\t\t(80*PIE)/180\t\t13964/10000");

printf ("\n90\t\t(90*PIE)/180\t\t15710/10000");

printf ("\n120\t\t(120*PIE)/180\t\t2095/1000");

printf ("\n150\t\t(150*PIE)/180\t\t2618/1000");

printf ("\n180\t\t(180*PIE)/180\t\t3142/1000");

}


void *Parsing (void *temp)
{

int i=0, tem = 1;

if(arr[0]=='-')
{

    i++;
}

while (1)

    {


if (arr[i] == '/')

	{

break;

}



numi *= tem;

numi += (arr[i] - '0');


tem = 10;

i++;

}

tem = 1;

i++;


while (1)


    {

if (i == strlen (arr))

	{

break;

}

den *= tem;

den += (arr[i] - '0');


tem = 10;

i++;


}


}




void *Fact (void *temp)
{

double t = 1;

int i, j;

int count = 0;

for (i = 2; i < 20; i += 2)

    {


for (j = i; j > 0; j--)

	{


t *= j;


}


fact[count] = t;


t = 1;

count++;

}


}




void *Cosine (void *temp)
{

double n_tem1 = 0, d_tem2 = 0, s1 = 1, s2 = 1;

int i, j = 0, flag = 0, counter1 = 0, counter2 = 0, sflag = 0;



for (i = 2; i < 9; i += 2)

    {

n_tem1 = pow (numi, i);

d_tem2 = pow (den, i);



d_tem2 *= fact[j];

j++;


s1 *= d_tem2;

n_tem1 *= s2;

s2 *= d_tem2;



if (flag == 0)

	{

s1 -= n_tem1;


flag = 1;


}


      else if (flag == 1)

	{

s1 += n_tem1;


flag = 0;


}


}

numi = s1;

den = s2;


if (s1 > 0)

    {


while (s1 > 1)

	{


s1 /= 10;

counter1++;


}


}


  else if (s1 < 0)


    {

while ((int) s1 < 0)

	{

sflag = 1;

s1 /= 10;

counter1++;


}


}



char up[counter1];

sprintf (up, "%.0lf", numi);


while (s2 > 1)

    {


s2 /= 10;

counter2++;


}


char down[counter2];

sprintf (down, "%.0lf", den);



i = counter1 - 1;

j = counter2 - 1;


if (strlen (up) < 2 || strlen (down) < 2)

    {

printf ("\n\nVALUE OF ENTERED ANGLE IS: 0/0 ");

exit (0);

}




while (up[i] == '0' && down[j] == '0')

    {

i--;

j--;

}

   if(sflag==1)
   {
      i++;
      up[i]='0';
   }


int kk, ll;

printf ("\n\nVALUE OF ENTERED ANGLE IS: ");

for (kk = 0; kk <= i; kk++)

    {

printf ("%c", up[kk]);

}

printf ("  /  ");

for (ll = 0; ll <= j; ll++)

    {

printf ("%c", down[ll]);

}

printf("\n");

}





int main ()
{


Display ();

printf ("\n\nENTER VALUE FROM ABOVE TABLE ( FRACTION FORM ) ");

scanf("%[^\n]", &arr);

pthread_t thread1,thread2,thread3;

pthread_create(&thread1,NULL,&Parsing, NULL);
pthread_create(&thread2,NULL,&Fact, NULL);
pthread_create(&thread3,NULL,&Cosine, NULL);



pthread_join(thread1,NULL);
pthread_join(thread2,NULL);
pthread_join(thread3,NULL);
return 0;


}

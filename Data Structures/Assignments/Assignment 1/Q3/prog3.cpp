#include <iostream>
#include <cstring>
#include <ctype.h>
#include <fstream>

using namespace std ;

void StringMutator(char* str,int len)
{
    char* newstring = new char[len+1]; // +1 for the NULL character
    char* same_letters = new char[len+1];
    bool repeatition ; // true if a letter repeats, else false
    static int siz = 0 ; // used as a counter for the same letters array

    memset(same_letters,0,len+1) ;
    newstring[0]= str[0] ; // store the 1st character
    same_letters[0] = str[0] ; // store the character in the same_letters array
    siz++ ;

    for (int i = 1 ; i < len ; i++)
    {
        repeatition = false ; // initially no repetitions
        for (int j=0;j<siz;j++) // compare a character of str with all same_letters to check repetition
        {
             if ( tolower(str[i]) == same_letters[j] && str[i]!= ' ') // repetition found
             {
                 newstring[i] = '-' ;
                 repeatition =  true ;
                    break ;
             }
        }
            if (!repeatition)
            {
                newstring[i] = str[i] ;
                same_letters[siz] = str[i] ;
                siz++ ;
            }

    }
    cout<<str<<endl ;
    cout<<newstring<<endl ;
    ofstream Outfile ;
    Outfile.open("Output3.txt") ;
    Outfile<<newstring ;

    delete[] newstring ;
    delete[] same_letters ;

}


int main()
{
    ifstream Infile ;
    char str[80] ;

  Infile.open("Input3.txt") ;
    if(!Infile)
    {
        cout<<"File could not be opened"<<endl ;
        return 1 ;
    }
    else
    {
        Infile.getline(str,80) ;
    }

    StringMutator( str,strlen(str) ) ;
    return 0 ;
}

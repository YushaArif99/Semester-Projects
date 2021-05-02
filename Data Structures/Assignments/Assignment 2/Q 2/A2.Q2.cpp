/*****************************************************
Code: Yusha Arif
ID: 18K-1289
Sec: B
Description: Breaks the numbers in the linked list
into digits. Uses exhaustive searching to find
all possible palindromes in the list of digits
Once found, stores the palindrome in a vector passed
as argument. Then continues to check for other palindrome
and if a larger palindrome is found, replaces the new
palindrome with the old one, otherwise continues the search.

Functions:
@ Largest_Palindrome
@ Separate_Digits


Data Structures used:
-> Linked list
-> Vectors (Dynamic Arrays)

******************************************************/


#include <bits/stdc++.h>

using namespace std ;


template<class T>
class Node
{
    public:
    T data ;
    Node<T>* next ;
    Node() : data(0), next(0) {}
    Node(T val) : data(val), next(0) {}
};


template<class T>
class SLL
{
    Node<T>* head ;
    Node<T>* tail ;
    int size ;
public:
    SLL() : head(0), tail(0), size(0) {}
    SLL(T val)
    {
        Node<T>* newNode = new Node<T>(val) ;
        head = newNode ;
        tail = newNode ;
        size = 0 ;
    }

    void Insert_tail(T val)
    {
        Node<T>* newNode = new Node<T>(val) ;

        if (head == 0)
        {
            head = newNode ;
            tail = newNode ;
            size++ ;
        }
        else
        {
            tail->next = newNode ;
            tail = newNode ;
            size++ ;
        }
    }

    void Insert_head(T val)
    {
        Node<T>* newNode = new Node<T>(val) ;

        if (head == 0)
        {
            head = newNode ;
            tail = newNode ;
            size++ ;
        }
        else
        {
            newNode->next = head ;
            head = newNode ;
            size++ ;
        }
    }

    bool Insert_index(T val, int index)
    {
        Node<T>* newNode = new Node<T>(val) ;

        if (head == 0 || index < 0 || index > size) return false ;

        else
        {
           Node<T>* current = head ;
           for(int i=0;i<index-1 ;i++) current= current->next ;

           newNode->next = current->next ;
           current->next = newNode ;
           size++ ;
        }

        return true ;
    }

    bool Delete_index(T val, int index)
    {
        Node<T>* temp = 0 ;

        if (head == 0 || index < 0 || index > size) return false ;

        else
        {
            Node<T>* current = head ;
           for(int i=0;i<index-1 ;i++) current= current->next ;

           current->next = temp ;
           current->next = temp->next ;

           temp->next = 0 ;
           delete temp ;

           size-- ;
        }

        return true ;
    }

    Node<T>** get_head()
    {
        return &head ;
    }
    Node<T>** get_tail()
    {
        return &tail ;
    }
    void set_head(Node<T>* h)
    {
        head = h ;
    }
    void print()
    {
        Node<T>* current = head ;
        while(current!= -0)
        {
            cout<<current->data<<"-> " ;
            current= current->next ;
        }
        cout<<endl<<endl ;

    }
};


void seperate_digits(int val,vector<int>& v)
{
    while (val != 0)
    {
      v.insert(v.begin(), val%10);
       val /= 10;
    }

}

template <class T>
void largest_palindrome( Node<T>** head, int length, vector<int>& my_palindrome )
{
        Node<T>* current = *head ;
        vector<int> digits ;
        vector<int> temp ;
        int start_fixed, start_dyn, end_fixed, end_dyn ;
        int size ;


        /// break the values stored in the linked list into separate digits and store them in a vector
        while(current!=0)
        {
            temp.insert(temp.begin(),current->data) ;
            current = current->next ;
        }

        for (int i=0;i<temp.size();i++)
        {
            seperate_digits(temp[i],digits) ;
        }

        cout<<"Digits Vector: "<<endl ;
         for (int i=0;i<digits.size();i++)
        {
            cout<<digits[i]<<" " ;
        }
        cout<<endl<<endl ;
        /// now time to find the palindrome!!

        start_fixed = start_dyn = 0 ; ///_fixed will stay fixed for the inner loop, _dyn will continuously move
        end_fixed = end_dyn = digits.size() - 1 ;

        while(start_fixed != (digits.size()-1) )
      {
          end_fixed = digits.size() -1  ; /// reset end_fixed to check possible palindromes from next starting index

           while (end_fixed!=start_fixed) /// tries all possible palindromes with start_fixed fixed
           {
                 end_dyn = end_fixed ;  /// setting the indexes for checking palindromes
                 start_dyn = start_fixed ; /// setting the indexes for checking palindromes

                while(end_dyn >= start_dyn)
                {
                    if (digits[start_dyn] == digits[end_dyn])
                    {
                        temp.push_back(digits[start_dyn]) ;
                        start_dyn++ ;
                        end_dyn-- ;

                    }
                    else break ;

                }

                if (end_dyn > start_dyn) /// means palindrome not found
                {
                    temp.clear() ; /// clear the contents of temp and start again
                }
                else /// palindrome found
                {

                   if (temp.size() > my_palindrome.size() ) /// larger palindrome found
                    {
                        my_palindrome.clear() ;
                        /// copy into my_palindrome
                        size = temp.size()  ;

                        for (int i=0;i<size;i++) /// left side
                        {
                            my_palindrome.push_back(temp[i]) ;
                        }

                        if (end_dyn==start_dyn) size -=1 ; /// don't copy the common element of the palindrome

                       for (int i=size-1 ;i>=0;i--) /// right side
                        {
                            my_palindrome.push_back(temp[i]) ;
                        }

                    }

                }

                end_fixed-- ; /// palindrome from last index not possible, so move to the previous index

            }

          start_fixed++ ; /// no possible palindrome from 1st index, so move to the next index
        }

        return ;

}

int main()
{

    ifstream InFile ;
    ofstream OutFile ;
    SLL<int> lnklist ;
    vector<int> my_palindrome ;
    int val ;

    InFile.open("inputQ2.txt") ;
    int length ;
    InFile>>length ;


    for (int i=0;i<length;i++)
    {
        InFile>>val;
        lnklist.Insert_tail(val) ;

    }

     lnklist.print() ;
    InFile.close() ;

    largest_palindrome<int>(lnklist.get_head(), length, my_palindrome) ;

    cout<<"Largest palindrome in the given linked list is: "<<endl<<endl ;

    for (int i=0;i<my_palindrome.size();i++)
    {
        cout<<my_palindrome[i]<<" " ;
    }
    cout<<endl<<endl ;

    /// writing to file
    OutFile.open("output_palindrome.txt") ;
    if (!OutFile) return -1 ;

    for (int i=0;i<my_palindrome.size();i++)
    {
        OutFile<<my_palindrome[i]<<" " ;
    }

    OutFile.close() ;

    return 0 ;

}

/*****************************************************

Code: Yusha Arif
ID: 18K-1289
Sec: B

Description:
Sum: Takes 2 linked lists. finds all the terms whose exponent
match and adds them. Then,adds the remaining terms( those
that weren't added ). Finally, Converts the whole equation
into standard form.

Derivative: Takes the Sum polynomial in standard form.
Multiplies the exponent with the corresponding
coefficient for each term.


Functions:
@ Add_Polynomials()
@ Derivative()
@ convert_to_standard()

Data Structures:
->Linked List
->Vectors (Dynamic Arrays)


****************************************************/

#include <bits/stdc++.h>

using namespace std ;

template <class T>
class Polynomial
{
    T coeff ;
    char base ;
    char sign ;
    int expo ;
public:
    Polynomial(char s='+', T c=1, char b=0, int e=0)
    {
        coeff = c ;
        base  = b ;
        sign = s ;
        expo = e ;
    }

    Polynomial(const Polynomial& rhs)
    {
        coeff = rhs.coeff ;
        base = rhs.base ;
        sign = rhs.sign ;
        expo = rhs.expo ;
    }

    Polynomial& operator = (const Polynomial& rhs)
    {
       if (this != &rhs)
       {
           Destroy() ;

            coeff = rhs.coeff ;
            base = rhs.base ;
            sign = rhs.sign ;
            expo = rhs.expo ;
       }

       return *this ;

    }

    void Destroy()
    {
        coeff = 0 ;
        base = 0 ;
        sign = 0 ;
        expo = 0 ;
    }

    void print_polynomial()
    {
        cout<<sign ;

        if (expo==0 && coeff!=0) { cout<<coeff ; return ; }

        if (coeff==0) {return ;}
        if (coeff !=1) cout<<coeff ;

        if (expo!=0) cout<<base ;

        if (expo >1) cout<<"^"<<expo ;


    }

    friend ofstream& operator<< (ofstream& fout, const Polynomial<T>& rhs)
    {
        fout<<rhs.get_sign() ;

        /// const term
         if (rhs.get_coeff()==1 && rhs.get_expo()==0) fout<<rhs.get_coeff()<<"X^"<<rhs.get_expo() ;

        else
        {
         if (rhs.get_coeff() >1) fout<<rhs.get_coeff() ;
         if (rhs.get_base()!=0) fout<<rhs.get_base() ;
         fout<<"^"<<rhs.get_expo() ;
        }
    }

    int get_expo() const
    {
        return expo ;
    }

    char get_base() const
    {
        return base ;
    }

    T get_coeff() const
    {
        return coeff ;
    }

    char get_sign() const
    {
        return sign ;
    }


    void set_sign(char s='+')
    {
        sign = s ;
    }
    void set_coeff(T c=1)
    {
        coeff =c ;
    }
    void set_base(char b=0)
    {
        base = b ;
    }
    void set_expo(int e=1)
    {
        expo= e ;
    }
};


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
            current->data.print_polynomial() ;
            cout<<" " ;
            current= current->next ;
        }
        cout<<"= 0" ;
        cout<<endl<<endl ;

    }
};

template<class T>
Node<T>* convert_to_standard(Node<T>** head)
{
    Node<T>* current = *head ;
    Node<T>* current2 = *head ;
    Polynomial<double> temp ;

    while (current!=0)
    {
        current2 = *head ;
        while (current2->next!=0)
        {
            if (current2->next->data.get_expo() > current2->data.get_expo() )
            {
                /// swap the data of the 2 nodes
                temp = current2->next->data ;
                current2->next->data = current2->data ;
                current2->data = temp ;
            }

            current2= current2->next ;
        }

        current = current->next ;

    }

    return *head ;

}


template <class T>
Node<T>* Add_Polynomials(Node<T>** head1, Node<T>** head2, Node<T>** sum )
{
    Node<T>* tail_sum = *sum ;
    Node<T>* current1 = *head1 ;
    Node<T>* current2 = *head2 ;
    Polynomial<double> poly ;
    int sign_check ; /// checks for sign to include in the sum linked list
    bool sum_found = false ; /// checks whether the 2 linked lists have a same exponent. If not, adds the 1st term to the sum, else adds their sum.
    vector<int> add_performed ; /// checks whether addition has been performed on this term. If so, skips it, otherwise, adds it to the sum list
    bool found = false ; /// used in conjunction with add_performed
    while (current1!=0)
    {
        /* fixes a node of 1st link list, and searches for all other nodes in
        the 2nd linked list with similar exponent and add their coefficients.
         avoid adding a term twice with the help of sum_found and add_performed */

        if (sum_found) current2 = current2->next ;
        current2 = *head2 ;
        while(current2!=0)
        {

            sum_found = false ;
            if( current2->data.get_expo() == current1->data.get_expo() )
            {
                /// create a new polynomial node


                poly.set_expo(current1->data.get_expo()) ;
                poly.set_base(current1->data.get_base()) ;

                    /// sign check
                   if ( current1->data.get_sign() != current2->data.get_sign() )  /// if different signs
                    {
                         sign_check = current1->data.get_coeff() - current2->data.get_coeff() ;
                         if (sign_check < 0)
                         {
                              poly.set_sign(current2->data.get_sign()) ;
                              poly.set_coeff( current2->data.get_coeff() - current1->data.get_coeff() ) ;
                         }

                        else if (sign_check > 0)
                        {
                            poly.set_sign(current1->data.get_sign()) ;
                            poly.set_coeff( current1->data.get_coeff() - current2->data.get_coeff() ) ;
                        }
                        else /// sign_check==0
                        {
                            poly.set_sign(0) ;
                            poly.set_coeff(0) ;
                            poly.set_expo(0) ;
                            poly.set_base(0) ;
                        }

                    }
                   else  /// copy the sign of any of the 2 terms
                   {
                        poly.set_sign(current1->data.get_sign()) ;
                        poly.set_coeff( current1->data.get_coeff() + current2->data.get_coeff() ) ;
                   }


                     Node<T>* newNode = new Node<T>(poly) ;

                    if(*sum==0) /// list is empty
                    {
                      if (poly.get_base()!=0 && poly.get_coeff()!=0)
                        {
                            *sum = newNode ;
                             tail_sum = newNode ;
                        }
                    }
                    else
                    {
                        if (poly.get_base()!=0 && poly.get_coeff()!=0)
                        {
                            tail_sum->next = newNode ;
                            tail_sum = newNode ;
                        }
                    }

                    sum_found = true ;
                    add_performed.push_back( current2->data.get_expo() ) ; /// marks this term to avoid it being checked again
                    break ;

             }

                current2 = current2->next ;

        }

            if (!sum_found)
            {

                Node<T>* newNode = new Node<T>(current1->data) ;

                if(*sum==0) /// list is empty
                {
                    *sum = newNode ;
                    tail_sum = newNode ;
                }
                else
                {
                    tail_sum->next = newNode ;
                    tail_sum = newNode ;
                }

            }

              current1 = current1->next ;
        }

        current2 = *head2 ;
        while(current2!=0)
        {
             for (int i=0;i<add_performed.size();i++)
             {
                 found = false ;
                 if (current2->data.get_expo() == add_performed[i])
                 {
                     found = true ;
                     break;
                 }
             }
                 if (!found)
                 {
                        Node<T>* newNode = new Node<T>(current2->data) ;

                        if(*sum==0) /// list is empty
                        {
                            *sum = newNode ;
                            tail_sum = newNode ;
                        }
                        else
                        {
                            tail_sum->next = newNode ;
                            tail_sum = newNode ;
                        }
                 }

                 current2 = current2->next ;

        }

        return *sum ;
}



template <class T>
Node<T>* Derivative(Node<T>** head, Node<T>** derivative)
{
    Node<T>* current = *head ;
    Node<T>* tail_deriv = *derivative ;
    Polynomial<double> poly ;

    while(current!=0)
    {
        if (current->data.get_expo() == 0) {} /// do nothing
        else if (current->data.get_expo() == 1)
        {
            poly.set_coeff(current->data.get_coeff()) ;
            poly.set_base(0) ;
            poly.set_sign(current->data.get_sign()) ;
            poly.set_expo(0) ;

            Node<T>* newNode = new Node<T>(poly) ;
            if (*derivative==0)
            {
                *derivative = newNode ;
                tail_deriv = newNode ;
            }
            else
            {
                tail_deriv->next = newNode ;
                tail_deriv  = newNode ;
            }

        }
        else
        {
            poly.set_coeff(current->data.get_coeff() * current->data.get_expo() ) ;
            poly.set_base(current->data.get_base()) ;
            poly.set_sign(current->data.get_sign()) ;
            poly.set_expo(current->data.get_expo() - 1 ) ;

            Node<T>* newNode = new Node<T>(poly) ;
            if (*derivative==0)
            {
                *derivative = newNode ;
                tail_deriv = newNode ;
            }
            else
            {
                tail_deriv->next = newNode ;
                tail_deriv  = newNode ;
            }
        }

        current  = current->next ;

    }

    return *derivative ;

}

template<class T>
void clear_all(T& inp_polynomial)
{
   /// reset all 4 parameters
    inp_polynomial.set_sign('+') ;
    inp_polynomial.set_coeff(1);
    inp_polynomial.set_base(0) ;
    inp_polynomial.set_expo(0) ;

}

int get_power(int base, int exp)
{
    int sum=1;
    for (int i=0;i<exp;i++)
    {
        sum*=base ;
    }

    return sum ;
}

template<class T>
int read_poly(SLL<T>& lnklist, SLL<T>& lnklist2)
{

    Polynomial<double> inp_polynomial ;
    ifstream Infile ;
    ofstream Outfile ;

    Infile.open("input.txt") ;
    if (!Infile)return -1 ;
    char str[150] ;
    int length,temp,coeff,power;


    for (int eqn_no = 1 ; eqn_no <=2 ; eqn_no++)

    {
           Infile.getline(str,150) ;
            length = strlen(str) ;

            power = 0 ;
            coeff = 0 ;
            for (int i=0;i<length;i++)
            {
                    /// if reached = , then break from loop
                    if (str[i]== 61)
                    {
                        break ;
                    }

                    /// check sign : + / -
                    if (str[i] == 43 || str[i] == 45 )
                    {
                        inp_polynomial.set_sign(str[i])  ;
                        continue ;
                    }

                    ///check coeff : num->base
                    if (str[i] >= 48 && str[i] <= 57  )
                    {
                        if ( str[i+1] == 88)  /// if num->base (ie 1 digit coeff)
                        {
                                inp_polynomial.set_coeff(str[i]-48)  ;
                                continue ;
                        }

                        if (str[i+1] >= 48 && str[i+1] <= 57) /// num->num (ie more than 1 digit coeff)
                        {
                            temp = i ;

                            while(str[i]!=88 ) /// while not encountering a base
                            {
                                i++ ;
                            }
                            power = 0;
                            coeff = 0 ;
                            for (int j = i-1 ;j>=temp;j--)
                            {
                                coeff  +=  ( (str[j] - 48) * get_power(10,power) ) ;
                                 power++ ;
                            }


                            inp_polynomial.set_coeff(coeff)  ;
                            i-- ;

                            continue ;
                        }

                    }

                    /// check base : letter
                    if (str[i] == 88)
                    {
                        inp_polynomial.set_base(str[i]) ;
                        continue ;
                    }

                    /// check expo :  '^'->num
                    if (str[i]=='^')
                    {
                        if ( str[i+2] == 43 || str[i+2]==45 || str[i+2]==61)  /// if expo-> +/-
                        {
                                inp_polynomial.set_expo(str[i+1]-48)  ;
                                i++ ;

                        }

                        else if (str[i+1]>=48 && str[i+1]<=57)/// num->num (ie more than 1 digit coeff)
                        {
                            i++ ;
                            temp = i ;

                            while(1) /// while not encountering a sign or =
                            {
                                if ((str[i]==43 || str[i]==45) || str[i]==61) break ;

                                i++ ;
                            }
                            power = 0;
                            coeff = 0 ;
                            for (int j = i-1 ;j>=temp;j--)
                            {
                                coeff  +=  ( (str[j] - 48) * get_power(10,power) ) ;
                                 power++ ;
                            }

                            inp_polynomial.set_expo(coeff)  ;
                            i-- ;

                        }

                        else inp_polynomial.set_expo(1) ;
                    }

                    if(str[i+1] == 43 || 45  || str[i+1]==61) /// eg -3x^4 =
                    {
                        if (eqn_no == 1) lnklist.Insert_tail(inp_polynomial) ;
                        else lnklist2.Insert_tail(inp_polynomial) ;

                        clear_all<Polynomial<double> >(inp_polynomial) ; /// resets the values for the input polynomial
                    }

            }

    }

    Infile.close() ;

}


template<class T>
int read_deriv(SLL<T>& lnklist )
{

    Polynomial<double> inp_polynomial ;
    ifstream Infile ;

    Infile.open("outputQ1.1.txt") ;
    if (!Infile)return -1 ;
    char str[150] ;
    int length,temp,coeff,power;

          Infile.getline(str,150) ;
            length = strlen(str) ;
            power = 0 ;
            coeff = 0 ;
            for (int i=0;i<length;i++)
            {
                    /// if reached = , then break from loop
                    if (str[i]== 61)
                    {
                        break ;
                    }

                    /// check sign : + / -
                    if (str[i] == 43 || str[i] == 45 )
                    {
                        inp_polynomial.set_sign(str[i])  ;
                        continue ;
                    }

                    ///check coeff : num->base
                    if (str[i] >= 48 && str[i] <= 57  )
                    {
                        if ( str[i+1] == 88)  /// if num->base (ie 1 digit coeff)
                        {
                                inp_polynomial.set_coeff(str[i]-48)  ;
                                continue ;
                        }

                        if (str[i+1] >= 48 && str[i+1] <= 57) /// num->num (ie more than 1 digit coeff)
                        {
                            temp = i ;

                            while(str[i]!=88 ) /// while not encountering a base
                            {
                                i++ ;
                            }
                            power = 0;
                            coeff = 0 ;
                            for (int j = i-1 ;j>=temp;j--)
                            {
                                coeff  +=  ( (str[j] - 48) * get_power(10,power) ) ;
                                 power++ ;
                            }

                            inp_polynomial.set_coeff(coeff)  ;
                            i-- ;

                            continue ;
                        }

                    }

                    /// check base : letter
                    if (str[i] == 88)
                    {
                        inp_polynomial.set_base(str[i]) ;
                        continue ;
                    }

                    /// check expo :  '^'->num
                    if (str[i]=='^')
                    {
                        if ( str[i+2] == 43 || str[i+2]==45 || str[i+2]==61 )  /// if expo-> +/-
                        {
                                inp_polynomial.set_expo(str[i+1]-48)  ;
                                i++ ;

                        }

                        else if (str[i+1]>=48 && str[i+1]<=57)/// num->num (ie more than 1 digit coeff)
                        {
                            i++ ;
                            temp = i ;
                            while(1) /// while not encountering a sign or =
                            {
                                if ((str[i]==43 || str[i]==45) || str[i]==61) break ;

                                i++ ;
                            }
                            power = 0;
                            coeff = 0 ;
                            for (int j = i-1 ;j>=temp;j--)
                            {
                                coeff  +=  ( (str[j] - 48) * get_power(10,power) ) ;
                                 power++ ;
                            }

                            if (coeff<0) coeff = (str[temp]-48) ;
                            inp_polynomial.set_expo(coeff)  ;
                            i-- ;

                        }

                        else inp_polynomial.set_expo(1) ;

                    }

                    if(str[i+1] == 43 || 45  || str[i+1]==61) /// eg -3x^4 =
                    {
                         lnklist.Insert_tail(inp_polynomial) ;

                        clear_all<Polynomial<double> >(inp_polynomial) ; /// resets the values for the input polynomial
                    }

            }

    Infile.close() ;

}

int main()
{

    SLL< Polynomial<double> > lnklist, lnklist2, lnklist3 ;
    SLL< Polynomial<double> > sum ;
    SLL<Polynomial<double> > derivative ;
    ofstream Outfile ;

    /// reading the 2 equations
    read_poly< Polynomial<double> >(lnklist,lnklist2) ;
    cout<<"Linked list 1: "<<endl ;
    lnklist.print() ;
    cout<<"Linked list 2: "<<endl ;
    lnklist2.print() ;


    /// calculating the sum
    Add_Polynomials< Polynomial<double> >(lnklist.get_head(),lnklist2.get_head(),sum.get_head()) ;

    /// now convert the sum list to standard form
    convert_to_standard<Polynomial<double> > (sum.get_head());
    cout<<"Sum of the 2 linked list is "<<endl<<endl ;
    sum.print() ;

    /// write sum to file
    Outfile.open("outputQ1.1.txt") ;
    if (!Outfile) return -1 ;

    Node<Polynomial<double> > **current = sum.get_head() ;
    while(*current !=0)
    {
        Outfile<<(*current)->data ;
        *current = (*current)->next ;
    }

    Outfile<<" = 0"<<endl ;
    Outfile.close() ;



    /// inputing derivative
    read_deriv< Polynomial<double> > (lnklist3) ;

    /// taking derivative of the sum
    Derivative<Polynomial<double> > (lnklist3.get_head(), derivative.get_head()) ;
    cout<<"The Derivative of the sum is "<<endl<<endl ;
    derivative.print() ;


    /// write derivative to file
    Outfile.open("outputQ1.2.txt") ;
    if (!Outfile) return -1 ;

    current = derivative.get_head() ;

    while(*current !=0)
    {
        Outfile<<(*current)->data ;
        *current = (*current)->next ;
    }

    Outfile<<" = 0"<<endl ;

    Outfile.close() ;


    return 0 ;


}





int main_standardform_filing()  /// filing of original test cases of the form +2x6 -4x2 + 4=0
{
    Polynomial<double> inp_polynomial ;
    SLL< Polynomial<double> > lnklist, lnklist2 ;
    ifstream Infile ;
    ofstream Outfile ;

    Infile.open("input.txt") ;
    if (!Infile)return -1 ;
    char str[150] ;
    int length,temp,coeff,power;


    for (int eqn_no = 1 ; eqn_no <=2 ; eqn_no++)

    {
           Infile.getline(str,150) ;
              length = strlen(str) ;

            power = 0 ;
            coeff = 0 ;
            for (int i=0;i<length;i++)
            {
                    /// if reached = , then break from loop
                    if (str[i]== 61)
                    {
                        break ;
                    }

                    /// check sign : + / -
                    if (str[i] == 43 || str[i] == 45 )
                    {
                        inp_polynomial.set_sign(str[i])  ;
                        continue ;
                    }

                    ///check coeff : num->base
                    if (str[i] >= 48 && str[i] <= 57  )
                    {
                        if ( str[i+1] == 88)  /// if num->base (ie 1 digit coeff)
                        {
                                inp_polynomial.set_coeff(str[i]-48)  ;
                                continue ;
                        }

                        if (str[i+1] >= 48 && str[i+1] <= 57) /// num->num (ie more than 1 digit coeff)
                        {
                            temp = i ;

                            while(str[i]!=88 && str[i]!=61) /// while not encountering a base
                            {
                                i++ ;
                            }
                            power = 0;
                            coeff = 0 ;
                            for (int j = i-1 ;j>=temp;j--)
                            {
                                coeff  +=  ( (str[j] - 48) * get_power(10,power) ) ;
                                 power++ ;
                            }

                            inp_polynomial.set_coeff(coeff)  ;
                            i-- ;

                            continue ;
                        }

                    }

                    /// check base : letter
                    if (str[i] == 88)
                    {
                        inp_polynomial.set_base(str[i]) ;
                        if (str[i+1] == 43 || str[i+1] == 45  || str[i+1]== 61) /// no exponent ie: +2x + ....
                        {
                              inp_polynomial.set_expo(1) ;

                            if (eqn_no == 1) lnklist.Insert_tail(inp_polynomial) ;
                            else lnklist2.Insert_tail(inp_polynomial) ;

                            clear_all<Polynomial<double> >(inp_polynomial) ; /// resets the values for the input polynomial

                        }
                        continue ;
                    }

                    /// check constant term
                    if (str[i] >= 48 && str[i] <= 57 ) /// eg: +4 =
                    {
                        if ( str[i+1] == 61)
                        {
                            inp_polynomial.set_coeff(str[i] - 48) ;
                            if (inp_polynomial.get_base() == 88 ) inp_polynomial.set_expo(1) ;
                            else inp_polynomial.set_expo(0) ;

                            if (eqn_no == 1) lnklist.Insert_tail(inp_polynomial) ;
                            else lnklist2.Insert_tail(inp_polynomial) ;

                            clear_all<Polynomial<double> >(inp_polynomial) ; /// resets the values for the input polynomial

                            continue ;
                        }


                    }

                    /// check expo :  base<-num
                    if (str[i] >= 48 && str[i] <= 57 && str[i-1] == 88)
                    {
                        inp_polynomial.set_expo(str[i]-48) ;
                    }


                    if(str[i+1] == 43 || 45  || str[i+1]==61) /// eg -3x^4 =
                    {
                        if (eqn_no == 1) lnklist.Insert_tail(inp_polynomial) ;
                        else lnklist2.Insert_tail(inp_polynomial) ;

                        clear_all<Polynomial<double> >(inp_polynomial) ; /// resets the values for the input polynomial
                    }

            }

    }



    Infile.close() ;
     cout<<"linked list 1"<<endl ;
    lnklist.print() ;

    cout<<"linked list 2"<<endl ;
    lnklist2.print() ;

    cout<<"Sum of the 2 linked list is "<<endl<<endl ;

    /// calculating the sum
    SLL< Polynomial<double> > sum ;
    Add_Polynomials< Polynomial<double> >(lnklist.get_head(),lnklist2.get_head(),sum.get_head()) ;
    /// now convert the sum list to standard form
    convert_to_standard<Polynomial<double> > (sum.get_head());

    sum.print() ;

    /// taking derivative of sum
    SLL<Polynomial<double> > derivative ;
    Derivative<Polynomial<double> > (sum.get_head(), derivative.get_head()) ;
    cout<<"The Derivative of the sum is "<<endl<<endl ;
    derivative.print() ;

    /// write sum to file
    Outfile.open("output.txt") ;
    if (!Outfile) return -1 ;

    Node<Polynomial<double> > **current = sum.get_head() ;
    while(*current !=0)
    {
        Outfile<<(*current)->data ;
        *current = (*current)->next ;
    }

    Outfile<<"= 0"<<endl ;


    /// write sum to file
    current = derivative.get_head() ;

    while(*current !=0)
    {
        Outfile<<(*current)->data ;
        *current = (*current)->next ;
    }

    Outfile<<" = 0"<<endl ;

    Outfile.close() ;

    return 0 ;
}


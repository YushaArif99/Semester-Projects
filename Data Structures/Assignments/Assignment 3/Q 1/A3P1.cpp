/****************************************************************************
NAME: Yusha Arif
SEC: GR-2(SEC: B)
ID: 18K-1289

DATA STRUCTURES USED:
->  BST
-> Vectors
-> Queues

FUNCTIONS:
-> GetLongestSequence() : counts the longest sequence of increasing/decreasing order of nodes
Traversal: The tree is traversed in a zig-zag manner to avoid redundancy when counting no of nodes
eg: root: countLeftwards && countRightwards
    root->left : countRightwards ( no need to countLeftwards as it will always be smaller )
    root->left->right: countLeftwards (  no need to countRightwards as it will always be smaller )
    .
    .

****************************************************************************/




#include <bits/stdc++.h>

using namespace std ;

struct Tnode
{
    int key ;
    Tnode* left ;
    Tnode* right ;

};

template<class T>
class BST
{
private:
    Tnode* root ;
public:
    BST(){ root = 0 ; }
    BST(T val)
    {
        root = createTnode(val);
    }

    Tnode* get_root() {return root ;}

    Tnode* insertNode(T val) ;
    Tnode* createTnode(T val) ;
    void printInorder() ;
    void printPreorder() ;
    void printPostorder() ;

    /// overloaded functions
    Tnode* insertNode(Tnode* root,T val) ;
    void printInorder(Tnode* root) ;
    void printPreorder(Tnode* root) ;
    void printPostorder(Tnode* root) ;


};

template <class T>
Tnode* BST<T>::createTnode( T val)
{
   Tnode* newnode = new Tnode() ;
   newnode->key = val ;
   newnode->left = 0 ;
   newnode->right = 0 ;

}



template <class T>
Tnode* BST<T>::insertNode( T val)
{
   root = insertNode(root,val) ;
   return root ;
}

template <class T>
void BST<T>::printInorder()
{
    printInorder(root) ;
    cout<<endl<<endl ;
}

template <class T>
void BST<T>::printPreorder()
{
    printPreorder(root) ;
    cout<<endl<<endl ;
}

template <class T>
void BST<T>::printPostorder()
{
    printPostorder(root) ;
    cout<<endl<<endl ;
}

template <class T>
Tnode* BST<T>::insertNode(Tnode* rt, T val)
{
   if (rt == 0)
   {
       rt = createTnode(val) ;
       return rt ;
   }

    if (rt->key < val ) rt->right = insertNode(rt->right,val) ;
    if (rt->key > val ) rt->left = insertNode(rt->left,val) ;

   return rt ;
}


template <class T>
void BST<T>::printInorder(Tnode* rt)
{
    if (rt != 0 )
    {
        printInorder(rt->left) ;
        cout<<rt->key<<", "  ;
        printInorder(rt->right) ;
    }
}

template <class T>
void BST<T>::printPreorder(Tnode* rt)
{
    if (rt != 0 )
    {
        cout<<rt->key<<", "  ;
        printInorder(rt->left) ;
        printInorder(rt->right) ;
    }

}

template <class T>
void BST<T>::printPostorder(Tnode* rt)
{
    if (rt != 0 )
    {
        printInorder(rt->left) ;
        printInorder(rt->right) ;
        cout<<rt->key<<", "  ;
    }

}




/// functions that are part of the algorithm start here:

void printLeft(Tnode* root)
{
    if (root != 0)
    {
        cout<<root->key<<", " ;
        printLeft(root->left) ;
    }

    else cout<<endl<<endl ;
}

void printRight(Tnode* root)
{
    if (root != 0)
    {
        cout<<root->key<<", " ;
        printRight(root->right) ;
    }

    else cout<<endl<<endl ;
}


void writetoFile(Tnode* root, char direction, ofstream& fout)
{
    if (root != 0)
    {
        fout<<root->key<<", " ;
        if (direction=='l') writetoFile(root->left,direction,fout) ;
        else writetoFile(root->right,direction,fout) ;
    }

}


void count_Leftwards(Tnode* root, int& counter)
{
    if (root != 0 )
    {
        counter++ ;
       count_Leftwards(root->left, counter) ;
    }


}

void count_Rightwards(Tnode* root, int& counter)
{
    if (root != 0 )
    {
        counter++ ;
        count_Rightwards(root->right, counter) ;
    }

}

void get_LeftlongestSequence(Tnode* root, Tnode** l_root, int& l_counter, int chosen, char& direction)
{
   int new_count=0 ;
    /// chosen acts as a switch for the leftward and rightward traversal
    Tnode* curr = root;


    if (root!=0)
    {

        if (chosen%2==0 ) /// even-> count leftwards
        {
            new_count = 0 ;
            count_Leftwards(curr->left, new_count) ;

           if ( new_count > l_counter )
           {

               l_counter = new_count ;
               *l_root = root ;

               direction = 'l' ;
           }
        }

        else /// odd-> count_rightwards
        {
            new_count = 0 ;
            count_Rightwards(curr->right, new_count) ;

           if ( new_count > l_counter )
           {
               l_counter = new_count ;
               *l_root = root ;

               direction = 'r' ;
           }
        }

        if (chosen %2==0) get_LeftlongestSequence(root->left, l_root, l_counter, chosen+1,direction) ;
        else get_LeftlongestSequence(root->right, l_root, l_counter, chosen+1, direction) ;

    }

}

void get_RightlongestSequence(Tnode* root, Tnode** r_root, int& r_counter, int chosen, char& direction)
{
    int new_count=0 ;
    /// chosen acts as a switch for the leftward and rightward traversal
    Tnode* curr = root;


    if (root!=0)

    {

        if (chosen%2==0 ) /// even-> count rightwards
        {
            new_count = 0 ;
            count_Rightwards(curr->right, new_count) ;

           if ( new_count > r_counter )
           {
               r_counter = new_count ;
               *r_root = root ;
               direction = 'r' ;
           }
        }

        else /// odd-> count_leftwards
        {
            new_count = 0 ;
            count_Leftwards(curr->left, new_count) ;

           if ( new_count > r_counter )
           {
               r_counter = new_count ;
               *r_root = root ;
               direction = 'l' ;
           }

        }

        if (chosen %2==0) get_RightlongestSequence(root->right, r_root, r_counter, chosen+1, direction) ;
        else get_RightlongestSequence(root->left, r_root, r_counter, chosen+1,direction) ;

    }

}

Tnode* get_longestSequence(Tnode* root, int& counter, char& direction)
{
    int new_count = 0;
    Tnode* longest_root = root ;
    Tnode* temp = 0;


    if (root != 0 )
    {
        new_count = 0 ;
        count_Leftwards(longest_root->left,new_count) ;

        if (new_count > counter)
        {
            longest_root = root ;
            counter = new_count ;
            direction = 'l' ;
        }

        new_count = 0 ;
        count_Rightwards(longest_root->right, new_count) ;

        if (new_count > counter)
        {
            longest_root = root ;
            counter = new_count ;
            direction = 'r' ;
        }


        new_count = 0 ;
        get_RightlongestSequence(root->right,&temp,new_count,1, direction) ;
        if (new_count > counter)
        {
            longest_root = temp;
            counter = new_count ;
        }



        get_LeftlongestSequence(root->left,&temp, new_count,1, direction) ;
        if (new_count > counter)
        {
            longest_root = temp ;
            counter = new_count;
        }

    }

    return longest_root ;
}



int main()
{
    ifstream Infile ;
    ofstream Outfile ;
    BST<int> tree ;
    int val, counter=0 ;

    Infile.open("InputQ1.txt") ;
    if (!Infile) return -1 ;

    Outfile.open("OutputQ1.txt") ;
    if (!Outfile) return -1 ;


    while (!Infile.eof())
    {
        Infile>>val ;
        tree.insertNode(val) ;
    }

    Infile.close() ;

    tree.printInorder() ;

    /// getting the longest count
    Tnode* root = tree.get_root() ;
    char print_dir = 'r' ;
    Tnode* largest_root = 0 ;


  largest_root =  get_longestSequence(root,counter,print_dir) ;

    cout<<"Longest sequence has length: "<<++counter<<endl<<endl ;
    cout<<"The sequence is as follows:  " ;

    if (print_dir =='l') printLeft(largest_root) ;
    else printRight(largest_root) ;

     if (largest_root != 0 )
    {
        Outfile<<counter<<endl ;
        writetoFile(largest_root,print_dir,Outfile) ;
    }

    else { cout<<"The tree is empty"<<endl ; Outfile.clear() ; }


    Outfile.close() ;
    return 0 ;
}

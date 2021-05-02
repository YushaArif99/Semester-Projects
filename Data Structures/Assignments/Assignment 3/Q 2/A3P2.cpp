/************************************************************************************************************
NAME: Yusha Arif
SEC: GR-2(SEC: B)
ID: 18K-1289

DATA STRUCTURES USED:
->  Binary Tree
-> Vectors
-> Queues

FUNCTIONS:
-> find_min_max() : finds the min/max value in the binary tree
-> check_sum() : checks if the sum of the given subtree is equal to a certain given value
->is_bst() : checks if a given subtree is a valid BST. Uses find_min_max() to determine that
-> find_bst() : generates all possible complete subtrees from the given binary tree
    .

ASSUMPTION:  The subtree must contain all nodes in the same order as in the original tree
and also be complete at a certain level. Leaf & internal nodes are also considered as valid subtrees.

Eg:    20
     10  40         VALID

     20
   10  40           INVALID
  5

***********************************************************************************************************/





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

    Tnode* createTnode(T val) ;
    void insertNode(T val) ;
    void printInorder() ;
    void printPreorder() ;
    void printPostorder() ;

    /// overloaded functions
    void insertNode(Tnode* root,T val) ;
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

   return newnode ;

}



template <class T>
void BST<T>::insertNode( T val)
{
    insertNode(root,val) ;
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
void BST<T>::insertNode(Tnode* rt, T val)
{
   Tnode* newnode = createTnode(val) ;

    if (rt == 0 )
    {
       this->root = newnode;
       return;
    }


        queue<Tnode*> q ;
        Tnode* temp = 0 ;
        Tnode* out = 0 ;

        q.push(rt);
        while (! q.empty())
        {
           temp = q.front() ;
           q.pop() ;

           if (temp->left == 0)
           {
               temp->left  = newnode ;
               return ;
           }

           else q.push(temp->left) ;

            if (temp->right == 0)
           {
               temp->right  = newnode ;
               return ;
           }
           else q.push(temp->right) ;
        }


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
        printPreorder(rt->left) ;
        printPreorder(rt->right) ;
    }

}

template <class T>
void BST<T>::printPostorder(Tnode* rt)
{
    if (rt != 0 )
    {
        printPostorder(rt->left) ;
        printPostorder(rt->right) ;
        cout<<rt->key<<", "  ;
    }

}

/// functions that are part of the algorithm start here:

void writetoFile(vector<int>&v, ofstream& fout)
{
    for (int i=0;i< v.size() ;i++)
    {
        fout<<v[i]<<" " ;
    }
}


void find_min_max(Tnode* root, int level,int& val, char& loc, char direction)
{
    if (level==0) return ;

    if (direction== 'r')
    {
        if (root->left !=0)
        {
            if (root->left->key < val) { val = root->left->key ; loc = 'l' ; }
        }

        if (root->right !=0)
        {
            if (root->right->key < val) { val = root->right->key ; loc = 'r' ; }
        }
        find_min_max(root->left,level-1,val,loc, direction)  ;
        find_min_max(root->right,level-1,val,loc, direction) ;
    }

    else
    {
        if (root->left !=0)
        {
            if (root->left->key > val) { val = root->left->key ; loc = 'l' ; }
        }

        if (root->right !=0)
        {
            if (root->right->key > val) { val = root->right->key ; loc = 'r' ; }
        }
        find_min_max(root->left,level-1,val,loc, direction)  ;
        find_min_max(root->right,level-1,val,loc, direction) ;
    }
}

bool is_bst(Tnode* root, int level)
{
    if (level==0) return true ;

    else
    {

        int max = root->left->key ;
        int min = root->right->key ;
        char min_loc = 'l' ;
        char max_loc = 'r' ;
       find_min_max(root->left,level-1,max,max_loc,'l') ;
       find_min_max(root->right,level-1,min,min_loc,'r') ;

      if(root->key < max || root->key > min || max_loc=='l' || min_loc== 'r') return false ;

        is_bst(root->left,level-1) ;
        is_bst(root->right,level-1) ;

    }


}
bool check_sum(vector<int>& chosen_val, int x)
{
    int sum = 0;
    for (int i=0 ; i<chosen_val.size();i++)
    {
        sum+=chosen_val[i] ;
    }

    if(sum==x) { return true ; }
    else return false ;

}


void print_vector(vector<int> v)
{
    for (int i = 0 ;i <v.size() ;i ++)
    {
        cout<<v[i]<<" " ;
    }

    cout<<endl<<endl ;

}


bool find_BST(Tnode* root, vector<int> chosen_val, int sum)
{
    queue<Tnode*> q ;
    Tnode* temp = 0 ;
    int level = 0 ;
    int node_no = 0 ;
    ofstream Outfile ;

    Outfile.open("OutputQ2.txt") ;
    if (! Outfile) { cout<<"could not open file!!"<<endl ; return false ; }

    if (root==0) return false ;

    if (root->key==sum  &&  ( ( root->left !=0 && root->right !=0 ) || (root->left ==0 && root->right ==0 ) ) )
    {
        chosen_val.push_back(root->key) ;
        print_vector(chosen_val) ;
        writetoFile(chosen_val, Outfile) ;
        return true ;
    }


    q.push(root) ;

    chosen_val.push_back(root->key) ;

    cout<<"level: "<<level<<endl ;
    print_vector(chosen_val) ;
    level++ ;

    node_no= 0 ;

    while (! q.empty())
    {
        temp  = q.front() ;
        q.pop() ;

        if (temp->left !=0)
        {
            chosen_val.push_back(temp->left->key) ;
            node_no++ ;

            q.push(temp->left) ;
        }

        else return false ;

        if (temp->right !=0)
        {
            chosen_val.push_back(temp->right->key) ;
            node_no++ ;

            q.push(temp->right) ;
        }
        else return false ;


        if (node_no == pow(2,level))
        {

            if (check_sum(chosen_val, sum) && is_bst(root,level) )
            {
                cout<<"level: "<<level<<endl ;
                print_vector(chosen_val) ;
                writetoFile(chosen_val,Outfile) ;
                return true ;
            }

            cout<<"level: "<<level<<endl ;
            level++ ;
            node_no = 0;

            print_vector(chosen_val) ;
        }

    }

    return false ;

}

int main()
{
    ifstream Infile ;
    ofstream Outfile ;
    BST<int> tree ;
    int  node_count, sum, val, counter = 0 ;
    Infile.open("InputQ2.txt") ;
    if (!Infile) return -1 ;

    Infile>>node_count ;
    Infile>>sum ;

    cout<<node_count<<" "<<sum<<endl ;

    while (1)
    {
        if (counter == node_count) break ;
        Infile>>val ;
      tree.insertNode(val) ;
      counter++ ;
    }

    Infile.close() ;

    tree.printInorder() ;

    Outfile.open("OutputQ2.txt") ;
    if(!Outfile) return -1 ;


    Tnode* curr = 0 ;
    Tnode* root = tree.get_root() ;
    Tnode* temp = 0 ;
    queue<Tnode*> q ;
    vector<int> v ;
    bool found = false ;

    q.push(root) ;

  if( find_BST(root,v,sum ) )
  {
       cout<<"found the answer !! "<<endl  ;
       return 0 ;

  }

    while (! q.empty() )
    {
        temp = q.front() ;
        q.pop() ;

        if (temp->left !=0)
       {
           if ( find_BST(temp->left,v,sum) )
           {
               found = true ;
               break ;
           }
           q.push(temp->left) ;
       }

       if (temp->right !=0)
       {
          if ( find_BST(temp->right,v,sum) )
          {
               found  = true ;
               break ;
          }

           q.push(temp->right) ;
       }

    }

    if (! found ) { cout<<"Sum not found !!"<<endl ; Outfile.clear() ; }
    else cout<<"found the answer!!"<<endl ;

    Outfile.close() ;
    return 0 ;

}


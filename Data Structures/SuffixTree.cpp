#include <bits/stdc++.h>

using namespace std ;


class End
{
public:

    int end_index ;
public:
    End(int e=0): end_index(e) {}
};


class ST_Node
{
    public:
    ST_Node** nucleotide ;
    ST_Node* suffixLink ;
    int start_index ;
    End* end_sn ;
    int index;

public:
    ST_Node()
    {
        nucleotide = new ST_Node*[256] ;
        for (int i = 0 ; i<256 ; i++)
        {
            nucleotide[i] = 0 ;
        }

        suffixLink =  0 ;
        start_index = -1 ;
        end_sn = 0 ;
        index = 0 ;

    }

    ST_Node* createSuffix_Node(int start, End* end)
    {

        ST_Node* newnode = new ST_Node() ;
        newnode->start_index = start ;
        newnode->end_sn = end ;

        return newnode ;

    }
};


class ActivePoints
{
public:

    ST_Node* act_node ;
    int act_edge ;
    int act_len ;

public:
    ActivePoints(ST_Node* &n)
    {
        act_node = n ;
        act_edge = -1 ;
        act_len = 0 ;
    }

    ActivePoints()
    {
        act_edge = -1 ;
        act_len = 0 ;
        act_node = 0 ;
    }
};


class SuffixTree:public ST_Node
{
    ST_Node* root ;
    ActivePoints* active ;
    int rem_suffix ;
    End* end_st ;
    char *text ;


public:

    SuffixTree()
    {
        root = 0 ;
        active = 0 ;
        end_st = 0 ;
        text = 0 ;
        rem_suffix = 0 ;
    }

    void  getText(char text[])
    {
        this->text = new char[strlen(text)+2];
        memcpy(this->text,text,sizeof(char)*strlen(text) ) ;

        this->text[strlen(text)] = '$';
        this->text[strlen(text)+1] = '\0';
        cout<<text<<endl ;

    }

    void buildSuffixTree()
    {

        root = createSuffix_Node( 1, new End(0) );
        root->index = -1;
        active = new ActivePoints(root);

        this->end_st = new End(-1);
        //loop through string to start new phase
        for(int i=0; i < strlen(text); i++)
        {
            beginPhase(i);
        }

        cout<<endl<<endl<<endl ;
        set_Suffix_Indexes(root, 0, strlen(text) );  // set indexes of the suffixes. eg: 0: Yusha$, 1: usha$ 2: sha$ etc


    }

    void beginPhase(int i)
    {
        ST_Node* latestInt_Node = 0;
        //Increment end before every phase
        end_st->end_index++;

        rem_suffix++;
        while( rem_suffix > 0 )
        {
            if(active->act_len == 0) // traversal starts from root
            {
                if( selectNode(i) != 0 )
                {
                    active->act_edge = selectNode(i)->start_index;
                    active->act_len++;
                    break;
                } //create a new leaf node with current character from leaf
                else
                {

                    root->nucleotide[text[i]] = createSuffix_Node(i, end_st);

                    rem_suffix--;
                }
            }

            else
            {

                //Active Length!=0  means traversal is Not from root. Therefore,check for next character
                try
                {
                    char ch = nextChar(i);

                    //if next character is same as current character then do a walk down.
                    if(ch == text[i])
                    {
                        //if latestInt_Node!=0 means rule 2 was applied in the previous phase. Point suffix link of that node
                        //to selected node using active_point.
                        if( latestInt_Node != 0)
                        {

                            latestInt_Node->suffixLink = selectNode();
                        }
                        //Move along the edge and update act_node if required.
                        WalkAlongPath(i);
                        break;
                    }
                    else
                    {
                        // ch!=text[i] -> create an internal node and leaf node (Branching).

                        ST_Node* node = selectNode();
                        int oldStart = node->start_index;
                        node->start_index = node->start_index + active->act_len;
                        //create new internal node
                        ST_Node* new_IntNode = createSuffix_Node(oldStart, new End(oldStart + active->act_len - 1) );

                        //create new leaf node
                        ST_Node* new_LeafNode = createSuffix_Node(i, this->end_st);

                        //set internal nodes nucleotide as old node and new leaf node.
                        new_IntNode->nucleotide[text[new_IntNode->start_index + active->act_len]] = node;
                        new_IntNode->nucleotide[text[i]] = new_LeafNode;
                        new_IntNode->index = -1;
                        active->act_node->nucleotide[text[new_IntNode->start_index]] = new_IntNode;

                        //if another internal node was created in current phase then suffixLink of that
                        //node will be this new node.
                        if (latestInt_Node != 0)
                        {
                            latestInt_Node->suffixLink = new_IntNode;
                        }

                        //set new_IntNode as latestInt_Node and if new int_node is created in next phase.
                        //then point suffixLink of this node to that newly created node. Meanwhile set suffixLink of this node to root.
                        latestInt_Node = new_IntNode;
                        new_IntNode->suffixLink = root;

                        //if act_node is not root then follow SuffixLink
                        if(active->act_node != root)
                        {
                            active->act_node = active->act_node->suffixLink;
                        }

                        else // act_node == root -> act_edge++ ; act_len-- ;
                        {
                            active->act_edge = active->act_edge  + 1;
                            active->act_len--;
                        }


                        rem_suffix--;
                    }

                }

                catch (NoPath& e)
                {
                    // create a new LeafNode and followSuffixLink.

                    ST_Node* node = selectNode();
                    node->nucleotide[text[i]] = createSuffix_Node(i, end_st);

                    if (latestInt_Node != 0)
                    {

                        latestInt_Node->suffixLink = node;
                    }

                    latestInt_Node = node;
                    //if act_node is not root then follow suffixLink
                    if(active->act_node != root)
                    {
                        active->act_node = active->act_node->suffixLink;
                    }

                    //act_node == root-> act_edge++ ; act_len-- ;
                    else
                    {
                        active->act_edge = active->act_edge + 1;
                        active->act_len--;
                    }

                    rem_suffix--;
                }
            }
        }
    }

     void WalkAlongPath(int index)
     {
        ST_Node* node = selectNode();

        if(diff(node) < active->act_len)
        {
            active->act_node = node;
            active->act_len = active->act_len - diff(node);
            active->act_edge = node->nucleotide[text[index]]->start_index;
        }

        else
        {
            active->act_len++ ;
        }

    }

    class NoPath: public exception
    {

    };

    //finds the next character to be compared to current phase character.
     char nextChar(int i)
     {

        ST_Node* node = selectNode();

        if(diff(node) >= active->act_len)
        {
            return text[active->act_node->nucleotide[text[active->act_edge]]->start_index + active->act_len];
        }

        if(diff(node) + 1 == active->act_len )
        {
            if( node->nucleotide[text[i]] != 0)
            {

                return text[i];
            }
        }

        else
        {
            active->act_node = node;
            active->act_len = active->act_len - diff(node) -1;
            active->act_edge = active->act_edge + diff(node)  +1;

            return nextChar(i) ;
        }

        throw NoPath(); // if there is no path from the current edge, throw an exception
    }


    ST_Node* selectNode() // returns the node based on where activePoint is
    {
        return active->act_node->nucleotide[text[active->act_edge]];
    }

     ST_Node* selectNode(int index) // returns the node based on the index provided
    {
        return active->act_node->nucleotide[text[index]];
    }


    int diff(ST_Node* node) // calculates the difference b/w end_index and start_index of a node
    {
        return node->end_sn->end_index - node->start_index;
    }


     void set_Suffix_Indexes(ST_Node* root,int val, int size)
     {
        if(root == 0)
        {
            return;
        }

        val += root->end_sn->end_index - root->start_index + 1;

        if(root->index != -1)
        {
            root->index = size - val;
            return;
        }

        ST_Node* node = 0 ;
        for (int i=0;i<256;i++)
        {
            node  = root->nucleotide[i] ;
            set_Suffix_Indexes(node, val, size);
        }


    }

        bool isValid(ST_Node* root, char* text, int index, int curr) // checks wheather the tree was built successfully or not
       {
          if (curr >= strlen(this->text) ) return true ;

        if(root == 0)
        {

            cout<<"Failed at "<<curr<<" for index "<<index<<endl ;
            return false;
        }

        if(root->index != -1)
        {
            if(root->index != index)
            {
                cout<<"Index not same. Failed at "<<curr<<" for index "<<index<<endl;
                return false;
            }

        else
            {
                return true;
            }

        }

        if(curr >= strlen(text) )
        {
            cout<<"Index not same. Failed at "<<curr<<" for index "<<index<<endl ;
            return false;
        }

        ST_Node* node = root->nucleotide[text[curr]];
        if(node == 0)
        {
           cout<<"Failed at "<<curr<<" for index "<<index;
            return false;
        }

        int j = 0;
        for(int i=node->start_index ; i <= node->end_sn->end_index; i++)
        {
            if( text[curr+j] != text[i] )
            {
                cout<<"Mismatch found at "<<text[curr+j]<<" "<<text[i]<<endl;
                return false;
            }

            j++;

        }

        curr += node->end_sn->end_index - node->start_index + 1;
        return isValid(node, text, index, curr);
    }

    bool isValid()
    {
        for(int i=0; i <strlen(this->text); i++)
        {
            if( !isValid(this->root, this->text, i, i) )
            {
                cout<<"Failed validation"<<endl;
                return false;
            }
        }

        return true ;
    }

/// pattern matching Algo
void Traverse_Path(int idx, int start, int end,char *str, int &status)
{
	//Traverse the edge with character by character matching
	for(int k=start; k<=end && str[idx] != '\0'; k++, idx++)
	{
		if(text[k] != str[idx])
			{
			    status = -1; // no match found
			    return ;
			}
	}
	if(str[idx] == '\0') { status =  1; return ; } // match found

	status =  0; // more characters yet to match
}

int Count_and_Traverse(ST_Node* &n,int active, int& count)
{
	if(n == 0) return 0;

	if(n->index > -1)
	{
		cout<<"\n\t\t->  Found at index:    "<<n->index<<endl ;
		count+=1 ;
		return 1;
	}
    for (int i = 0; i < 256; i++)
	{
		if(n->nucleotide[i] != 0)
		{
            Count_and_Traverse(n->nucleotide[i],active, count);
		}
	}
	return count;
}

int Leaves_count(int c ,ST_Node* &n)
{
	if(n == 0)
		return 0;

    int act=0;
    int count =  0 ;
	Count_and_Traverse(n,act, count);
	return count ;
}

int Traverse_Tree( int idx,ST_Node* &n,char* str )
{
	if(n == 0)
	{
		return -1; // no match found
	}
	int result = -1;

	if(n->start_index != -1)
	{
		Traverse_Path(idx, n->start_index, n->end_sn->end_index,str, result );
		if(result == -1) //no match found
			return -1;

		if(result == 1) //match found
		{
			int count= 0;
		    int counter = Leaves_count(count,n) ;
		    cout<<endl<<endl ;
            cout<<"\n\t\t->  substring count: "<<counter<<endl<<endl ;
			return 1;
		}
	}
	//Get the index of next character
	idx = idx + diff(n)+1;
	//If a path exists from curr_node, traverse that path
	if(n->nucleotide[str[idx]] != 0)
		return Traverse_Tree( idx ,n->nucleotide[str[idx]], str);

	else
		return -1; // no match found
}

void find_Substrings(int no,char* str,bool chxk)
{
	int result = Traverse_Tree( 0,root, str);
	if(result == 1)
	{
		chxk=true;
		cout<<"    || Corpus<"<<str<<"> belongs to Corpus "<<no<<" ||"<<endl<<endl<<endl ;
}
	else{
		chxk=false;
		cout<<"    || Corpus<"<<str<<"> DOES NOT belong to Corpus "<<no<<" ||"<<endl<<endl<<endl ;
        }

}



};



int main()
{

    SuffixTree tree1,tree2  ;
    ofstream Outfile ;
    ifstream Infile ;
    char* str =  new char[2000] ;
    char* str2 = new char[2000] ;
    char* str3 = new char[500];

    Infile.open("input1.txt");
    if (!Infile) return -1 ;

    char ch ;
    int c = 0;
    while(Infile>>ch) { str[c] = ch ; c++ ; }
    cout<<"---------------------------------|| Corpus1 ||--------------------------------- "<<endl ;

    cout<<"*******************************************************************************"<<endl;

	tree1.getText(str) ;
     cout<<endl;
     cout<<"********************************************************************************"<<endl;
    tree1.buildSuffixTree() ;
    if ( tree1.isValid() ) cout<<"---------------------|| Suffix Tree Built Successfully!! ||---------------------"<<endl<<endl ;

    Infile.close() ;

    Infile.open("input2.txt");
    if (!Infile) return -1 ;

    c = 0 ;
    while(Infile>>ch) {  str2[c] = ch ; c++ ; } ;


 cout<<"--------------------------------|| Corpus2 ||-------------------------------- "<<endl ;

    cout<<"*******************************************************************************"<<endl;
    tree2.getText(str2);
    cout<<endl;
     cout<<"*******************************************************************************"<<endl;
    tree2.buildSuffixTree();
    if(tree2.isValid() )  cout<<"---------------------|| Suffix Tree Built Successfully!! ||---------------------"<<endl<<endl ;


    Infile.close();
    cout<<endl ;
    cout<<"                   ||!i|| Enter The Corpus You Want To Match:  ||!i|| "<<endl<<endl;
    cin>>str3;

    cout<<"-----------------------------Checking For Corpus1  -----------------------------"<<endl;
    bool check ;
    tree1.find_Substrings(1,str3,check) ;
    cout<<endl<<endl ;
   cout<<"----------------------------Checking For Corpus2  ------------------------------"<<endl;
    tree2.find_Substrings(2,str3,check) ;

    delete[] str ;
    delete[] str2 ;
    delete[] str3 ;

    return 0 ;
}

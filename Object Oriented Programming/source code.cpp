#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;


class account
{
protected:
    int Account_no;
	string name ;
	int deposit;
public:
	virtual void newAccount() = 0 ;

    virtual void write_to_file() =0 ;

    virtual void DeleteAccount(int n) =0 ;

    virtual void Deposit(int amt) = 0 ;

	void dep(int x)
	{
	    deposit+=x;
	}
	void draw(int x)
	{
	    deposit-=x;
	}
	int get_Account_no() const
	{
	    return Account_no ;
	}
	int get_deposit() const
	{
	    return deposit ;
	}

} ;
class CurrentAccount : public account
{

double min_balance;
char type  ;

public:
CurrentAccount()

{
    min_balance= 500 ;
    type = 'C' ;

}

~CurrentAccount(void){}

void report() const
	{
	    cout<<Account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<deposit<<setw(10)<<" "<<type<<endl;
	}

void newAccount()
{
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>Account_no ;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
	cin>>name ;
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\t\t\tAccount Created..";
}
void write_to_file()
{
	CurrentAccount ac;
	ofstream outFile;
	outFile.open("CurrentAccount.txt",ios::binary|ios::app|ios::out);
	ac.newAccount(); // create a new account and then write it to file
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
	outFile.close();
}

void DeleteAccount( int n)
{
	CurrentAccount ac;
	ifstream inFile;
	ofstream outFile;
	bool match =0 ;
	inFile.open("CurrentAccount.txt",ios::in);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount)))
	{
		if(ac.get_Account_no()!=n ) // copy all contents of file except the one which you want to delete
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
		}
		else match =1  ;
	}
	if (!match)
    { cout<<"account does not exist"<<endl  ;
    return ; }
    inFile.close();
	outFile.close();
	int check = remove("CurrentAccount.txt"); // deletes the file (true if successful else false)
	rename("Temp.txt","CurrentAccount.txt"); // renaming the temp file (which contains all data except the one you wanted to delete)
	if (!check)  cout<<"\n\nRecord Deleted .." ;
	else cout<<"\n\nRecord could not be Deleted .." ;

}

void withd(double amount)
{
    if (deposit-amount < 0)
    {
      cout << "Insufficient funds: the entered amount cannot be withdrawn "<< endl;

      return;
    }
    else if (amount<=500) cout<<"enter amount above Rs500 "<<endl ;
     else
    deposit -= amount;
}
void withdraw(int n)
{
    double amt;
	bool flag=false;
	int counter =0 ;
	CurrentAccount ac;
	fstream File;
    File.open("CurrentAccount.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && flag==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
		if(ac.get_Account_no()!=n) // read from file and compare the account numbers
		{
		    // method 1
                counter++ ; // while the required data is not found, keep incrementing the counter

             /* method 2
			 pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur); */ // move BACKWARDS sizeof(ac) no of bytes from current position
		}
		else
        {
				cout<<"\n\n\t\t\tEnter The amount to be withdrawn: ";
				cin>>amt;
				ac.withd(amt);
				//method 1
				File.seekp(counter*sizeof(ac),ios::beg) ; // move FORWARD counter*sizeof(ac) no of bytes from beginning
				File.write(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
			    cout<<"\n\t\t\tRecord Updated"<<endl;
			    flag = true ;

        }


    }
             File.close();
	      if(flag==false)
        cout<<"\n\n\t\t\tRecord Not found ";
}

void Deposit(int n)
{
    int amt;
	bool flag=false;
	int counter = 0;
	CurrentAccount ac;
	fstream File;
    File.open("CurrentAccount.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && flag==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
		if(ac.get_Account_no()!=n)
		{
		    // method 1
                counter++ ;

             /* method 2
			 pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur); */
		}
		else
        {
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
				//method 1
				File.seekp(counter*sizeof(ac),ios::beg) ;
				File.write(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount));
			    cout<<"\n\t\t\tRecord Updated"<<endl;
			    flag = true ;

        }

	}
    File.close();
	if(flag==false)
		cout<<"\n\n\t\t\tRecord Not found ";
}
friend ostream& operator << (ostream& o, CurrentAccount& obj)
{
    o<<"Name : "<<obj.name<<endl ;
    o<<"Account No : "<<obj.Account_no<<endl ;
    o<<"Type : "<<obj.type<<endl ;
    o<<"Amount : "<<obj.deposit<<endl ;
}
void show(int n)
{
    CurrentAccount ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("CurrentAccount.txt",ios::binary|ios::in);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount)))
	{
		if(ac.get_Account_no()==n)
		{
            cout<<ac ;
            flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}

};

class savingsAccount : public account
{
char type ;
public:
savingsAccount ()

{
    type = 'S' ;
}

~savingsAccount(void)
{
}

void report() const
	{
	    cout<<Account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<deposit<<setw(10)<<" "<<type<<endl;
	}
void newAccount()
{
	cout<<"\n\t\t\tEnter the Account No. : ";
	cin>>Account_no ;
	cout<<"\n\n\t\t\tEnter the Name of the Account holder : ";
    cin>>name ;
	cout<<"\n\t\t\tEnter The Initial amount : ";
	cin>>deposit;
	cout<<"\n\n\t\t\tAccount Created..";
}
void write_to_file()
{
	savingsAccount ac;
	ofstream outFile;
	outFile.open("SavingAccount.txt",ios::binary|ios::app|ios::out);
	ac.newAccount();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(savingsAccount));
	outFile.close();
}

void DeleteAccount( int n)
{
	savingsAccount ac;
	ifstream inFile;
	ofstream outFile;
	bool match =0 ;
	inFile.open("SavingAccount.txt",ios::in);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.txt",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(savingsAccount)))
	{
		if(ac.get_Account_no()!=n )
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(savingsAccount));
		}
		else match =1  ;
	}
	if (!match)
    { cout<<"account does not exist"<<endl  ;
    return ; }
    inFile.close();
	outFile.close();
	int check = remove("SavingAccount.txt");
	rename("Temp.txt","SavingAccount.txt");
	if (!check)  cout<<"\n\nRecord Deleted .." ;
	else cout<<"\n\nRecord could not be Deleted .." ;

}


void withd(double amount)
{
    if (deposit-amount < 0)
    {
      cout << "Insufficient balance: cannot withdraw the given amount " << endl;
      return;
    }
    deposit -= amount;
}
void withdraw(int n)
{
     double amt;
	bool flag=false;
	int counter =0 ;
	savingsAccount ac;
	fstream File;
    File.open("SavingAccount.txt",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && flag==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(savingsAccount));
		if(ac.get_Account_no()!=n)
		{
		    // method 1
                counter++ ;

             /* method 2
			 pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur); */
		}
		else
        {
				cout<<"\n\n\t\t\tEnter The amount to be withdrawn: ";
				cin>>amt;
				ac.withd(amt);
				//method 1
				File.seekp(counter*sizeof(ac),ios::beg) ;
				File.write(reinterpret_cast<char *> (&ac), sizeof(savingsAccount));
			    cout<<"\n\t\t\tRecord Updated"<<endl;
			    flag = true ;

        }

	}
    File.close();
	if(flag==false)
		cout<<"\n\n\t\t\tRecord Not found ";
}
void Deposit(int n)
{
    int amt;
	bool flag=false;
	savingsAccount ac;
	int counter = 0 ;
	fstream File;
    File.open("SavingAccount.txt", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && flag==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(savingsAccount) );
		if(ac.get_Account_no()!=n)
		{
		    // method 1
                counter++ ;

             /* method 2
			 pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur); */
		}
		else
        {
				cout<<"\n\n\t\t\tEnter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
				//method 1
				File.seekp(counter*sizeof(ac),ios::beg) ;
				File.write(reinterpret_cast<char *> (&ac), sizeof(savingsAccount));
			    cout<<"\n\t\t\tRecord Updated"<<endl;
			    flag = true ;

        }
	}
    File.close();
	if(flag==false)
		cout<<"\n\n\t\t\tRecord Not found ";

}

friend ostream& operator << (ostream&o, savingsAccount& obj)
{
    o<<"Name : "<<obj.name<<endl ;
    o<<"Account No : "<<obj.Account_no<<endl ;
    o<<"Type : "<<obj.type<<endl ;
    o<<"Amount : "<<obj.deposit<<endl ;
}
void show(int n)
{
    savingsAccount ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("SavingAccount.txt",ios::in);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\t\t\tBALANCE DETAILS\n";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(savingsAccount)) )
	{
		if(ac.get_Account_no()==n)
		{
			cout<<ac ;
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"\n\n\t\t\tAccount number does not exist";
}

};

// Global Function

void display_all()
{
	CurrentAccount ac;
	savingsAccount ac2;
	ifstream inFile, inFile2;
	inFile.open("CurrentAccount.txt",ios::binary);
	inFile2.open("SavingAccount.txt",ios::binary);

	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME            Balance      TYPE\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(CurrentAccount)))
	{
		ac.report();
	}
	inFile.close();
	if(!inFile2)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME            Balance      TYPE\n";
	cout<<"====================================================\n";
	while(inFile2.read(reinterpret_cast<char *> (&ac2), sizeof(savingsAccount)))
	{
		ac2.report();
	}
	inFile2.close();

}

int main()
{
	int opt;
    int num;
    int type ;

	cout<<"\n\n\t\t\t\t=====================\n";
	cout<<"\t\t\t\tBANK MANAGEMENT SYSTEM";
	cout<<"\n\t\t\t\t======================\n";
            while (1) {
		cout<<"\t\t\t\t    ::MAIN MENU::\n";
		cout<<"1) Current Account"<<endl<<endl<<"2) Savings Account"<<endl<<endl<<"3) EXIT"<<endl ;
		cin>>type ;
		if (type==1)
        {
            opt=0 ;
            CurrentAccount acct ;
            while (opt!=7) {
            cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-7): ";
		cin>>opt;

		switch(opt)
		{
		case 1:
			acct.write_to_file();
			break;
		case 2:
			cout<<"\n\n\t\t\tEnter The account No. : ";
            cin>>num;
			acct.Deposit(num) ;
			break;
		case 3:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.withdraw(num);
			break;
		case 4:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.show(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.DeleteAccount(num);
			break;
		 case 7:
			break;

		 default :cout<<"Please chose a valid option";
		}
        }
        }

         if (type==2) {
                 opt=0 ;
                savingsAccount acct ;
                while(opt!=7) {
		cout<<"\n\t\t\t\t1. NEW ACCOUNT";
		cout<<"\n\t\t\t\t2. DEPOSIT AMOUNT";
		cout<<"\n\t\t\t\t3. WITHDRAW AMOUNT";
		cout<<"\n\t\t\t\t4. BALANCE ENQUIRY";
		cout<<"\n\t\t\t\t5. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\t\t\t\t6. CLOSE AN ACCOUNT";
		cout<<"\n\t\t\t\t7. EXIT";
		cout<<"\n\n\t\t\t\tSelect Your Option (1-7): ";
		cin>>opt;

		switch(opt)
		{
		case 1:
			acct.write_to_file();
			break;
		case 2:
			cout<<"\n\n\t\t\tEnter The account No. : ";
            cin>>num;
			acct.Deposit(num) ;
			break;
		case 3:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.withdraw(num) ;
			break;
		case 4:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.show(num);
			break;
		case 5:
			display_all();
			break;
		case 6:
			cout<<"\n\n\t\t\tEnter The account No. : "; cin>>num;
			acct.DeleteAccount(num);
			break;
		 case 7:
		     break ;

		 default :cout<<"Please chose a valid option";
		}

                }
    }

    if (type==3) break ;
            }
	return 0 ;
}

/*NOTE: There is a small  bug in this program. Reading from the SavingAccount.txt file is displaying random characters
instead of the name. Rest is fine. */

/* TOPICS COVERED
- ABSTRACTION
- INHERITANCE
- POLYMORPHISM
- ABSTRACT CLASSES
- FRIEND FUNCTION
- OPERATOR OVERLOADING
- FILE HANDLING
*/

#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
using namespace std;

class Bank
{
	protected:
		string name, acc_no;
		char acc_type;
		float balance;
		
	public:
		void get()
		{
			cout<<"\t\t\t\t------------------------------------------------"<<endl;
			cout<<"\t\t\t\tENTER DETAILS: "<<endl<<endl;
			cout<<"\t\t\t\tEnter name: ";
			cin.ignore();
			getline(cin, name);
			cout<<"\t\t\t\tEnter account number: ";
			cin>>acc_no;
			cout<<"\t\t\t\tEnter type of account \n\t\t\t\t(Savings-S / Current-C): ";
			cin>>acc_type;
			cout<<"\t\t\t\tEnter opening balance: ";
			cin>>balance;
			cout<<endl<<endl<<"\t\t\t\tAccount created successfully"<<endl;
			cout<<"\t\t\t\t------------------------------------------------"<<endl;
		}
		
		void display()
		{
			cout<<"\t\t\t\t"<<left<<setw(15)<<acc_no<<setw(20)<<name<<setw(10)<<balance<<setw(3)<<(char)toupper(acc_type)<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
		}
		
		void deposit(float amt)
		{
			balance+=amt;
			cout<<endl<<"\t\t\t\tTransaction successful"<<endl;
		}
		
		void withdraw(float amt)
		{
			if (balance-amt>1000)
			{
				balance-=amt;
				cout<<endl<<"\t\t\t\tTransaction successful"<<endl;
			}
			
			else
			{
				cout<<endl<<"\t\t\t\tInsufficient fund"<<endl;
			}
		}
		
		string get_acc_no()
		{
			return acc_no;
		}
		
		float get_balance()
		{
			return balance;
		}
};

Bank b;
fstream f;

void write()
{
	f.open("Bank.dat", ios::app|ios::binary);
	b.get();
	f.write((char*)&b, sizeof(b));
	f.close();
}

void read()
{
	f.open("Bank.dat", ios::in|ios::binary);
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	while(f.read((char*)&b, sizeof(b)))
	{
		b.display();
	}
	f.close();
}
void bank_deposit()
{
	f.open("Bank.dat", ios::out|ios::in|ios::binary);
	float amt; string a_no; bool d=0;
	cout<<"\t\t\t\tEnter account number: ";
	cin>>a_no;
	while(f.read((char*)&b, sizeof(b)))
	{
		int l=f.tellp();
		if(a_no==b.get_acc_no())
		{
			cout<<"\t\t\t\tEnter amount to be deposited: ";
			cin>>amt;
			b.deposit(amt);
			f.seekp(l-sizeof(b));
			f.write((char*)&b, sizeof(b));
			f.close();
			cout<<endl<<"\t\t\t\tUpdated balance:"<<endl<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			b.display();
			d=1;
			break;
		}
	}
	if(d==0)
	{
		cout<<"\t\t\t\tInvalid acconut number"<<endl;
	}
}

void bank_withdraw()
{
	f.open("Bank.dat", ios::out|ios::in|ios::binary);
	float amt; string a_no; bool d=0;
	cout<<"\t\t\t\tEnter account number: ";
	cin>>a_no;
	while(f.read((char*)&b, sizeof(b)))
	{
		int l=f.tellp();
		if(a_no==b.get_acc_no())
		{
			cout<<"\t\t\t\tEnter amount to be withdrawn: ";
			cin>>amt;
			b.withdraw(amt);
			f.seekp(l-sizeof(b));
			f.write((char*)&b, sizeof(b));
			f.close();
			cout<<endl<<"\t\t\t\tUpdated balance:"<<endl<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
			cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
			b.display();
			d=1;
			break;
		}
	}
	if (d==0)
	{
		cout<<"\t\t\t\tInvalid account number"<<endl;
	}
}

void specific_acc()
{
	f.open("Bank.dat", ios::out|ios::in|ios::binary);
	string a_no; bool d=0;
	cout<<"\t\t\t\tEnter account number: ";
	cin>>a_no;
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
	cout<<"\t\t\t\t------------------------------------------------------------------------"<<endl;
	while(f.read((char*)&b, sizeof(b)))
	{
		if (a_no==b.get_acc_no())
		{
			d=1;
			b.display();
			f.close();
			break;
		}
	}
	
	if (d==0)
	{
		cout<<"Invalid account number"<<endl;
	}
}

void greater_than_2_lakh()
{
	f.open("Bank.dat", ios::in|ios::out|ios::binary);
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	while(f.read((char*)&b, sizeof(b)))
	{
		if(b.get_balance()>200000)
		{
			b.display();
		}
	}
}

void minimum_balance()
{
	f.open("Bank.dat", ios::in|ios::out|ios::binary);
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	cout<<"\t\t\t\tACCOUNT DETAILS: "<<endl<<endl;
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	cout<<"\t\t\t\t"<<left<<setw(15)<<"Account id"<<setw(20)<<"Name"<<setw(10)<<"Balance"<<setw(3)<<"Account type"<<endl;
	cout<<"\t\t\t\t------------------------------------------------"<<endl;
	while(f.read((char*)&b, sizeof(b)))
	{
		if(b.get_balance()<1000)
		{
			b.display();
		}
	}
}

int main()
{
	int n, trial=0;
	string user_id="admin", password[]={"a", "d", "m", "i", "n", "1", "2", "3"}, user_name;
	int size=sizeof(password)/sizeof(password[0]);
	string user_password[size]={};
	string confirm_password[size]={};
	int i=0, k=0;
	
	while(trial<3)
	{
		system("cls");
		cout<<"\t\t\t\tSIGN IN TO YOUR ACCOUNT"<<endl<<endl;
		cout<<"\t\t\t\t------------------------------------------------"<<endl;
		cout<<"\t\t\t\tUsername:";
		cin>>user_name;
		cout<<"\t\t\t\t------------------------------------------------"<<endl;
		cout<<"\t\t\t\tPassword:";
		{
			char c=getch();
			if (c==13)
				break;
				
			else if (c==8)
			{
				i-=2;
				cout<<"\b \b";
			}
			else
			{
				user_password[i]=c;
				cout<<"*";
			}
			i++;	
		}	
		cout<<endl;
		int f=0;
		for(int j=0; j<size; j++)
		{
			if (password[j]==user_password[j])
				f++;
		}
		cout<<"\t\t\t\t------------------------------------------------"<<endl;
		cout<<"\t\t\t\tConfirm Password:";
		{
			char c=getch();
			if (c==13)
				break;
				
			else if (c==8)
			{
				k-=2;
				cout<<"\b \b";
			}
			else
			{
				confirm_password[k]=c;
				cout<<"*";
			}
			k++;	
		}	
		cout<<endl;
		int g=0;
		for(int j=0; j<size; j++)
		{
			if (user_password[j]==confirm_password[j])
				g++;
		}
		cout<<endl<<endl;
		trial++;
		if ((user_id==user_name) && (f==size) && (g==size))
		{
			do
			{
				trial=0;
				system("cls");
				cout<<endl;
				cout<<"\t\t\t\t\t\t"<<"BANK MANAGEMENT SYSTEM"<<endl<<endl;
				cout<<"\t\t\t\t------------------------- MENU -------------------------"<<endl<<endl;
				cout<<"\t\t\t\t1. CREATE ACCOUNT \n\t\t\t\t2. DISPLAY ALL ACCOUNTS \n\t\t\t\t3. DISPLAY SPECIFIC ACCOUNT \n\t\t\t\t4. WITHDRAW \n\t\t\t\t5. DEPOSIT "<<endl;
				cout<<"\t\t\t\t6. ACCOUNT WITH BALANCE GREATER THAN 2,00,000 \n\t\t\t\t7. DISPLAY DORMANT ACCOUNT \n\t\t\t\t0. EXIT"<<endl<<endl;
				cout<<"\t\t\t\tEnter your choice: ";
				cin>>n;
				system("cls");
				switch(n)
				{
					case 1:{
						write();
						break;
					}
					
					case 2:{
						read();
						break;
					}
					
					case 3:{
						specific_acc();
						break;
					}
					
					case 4:{
						bank_withdraw();
						break;
					}
					
					case 5:{
						bank_deposit();
						break;
					}
					
					case 6:{
						greater_than_2_lakh();
						break;
					}
					
					case 7:{
						minimum_balance();
						break;
					}
				}
				cin.ignore();
				cin.get();
			}
			while(n!=0);
		}
		
		else
		{
			cout<<"\t\t\t\tInvalid user_id or password"<<endl;
			cin.ignore();
			cin.get();
			
		}
		for (int k = 0; k<size; k++)
		{
			user_password[k] = "";
			confirm_password[k] = "";
		}
    	k=0;
		i=0;
	}
	if (trial==3)	
	{
		system("cls");
		cout<<endl<<endl;
		cout<<"\t\t\t\tUser authentication failed"<<endl;
		cin.ignore();
		cin.get();
	}
}
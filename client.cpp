//headers for omplementation of class client
#include "book.cpp"
#include<vector>

//headers for password abstraction

#include <cstdlib>
#include <iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>


using namespace std;

//demo initialisation for making it a friend
class libaray;

class client{
	//friend
	friend class library;

	//private data members

	string name;
	string password;
	vector<book> books_with_client;

	//private methords

	//private accessors
	void get_data();
	string get_name();

	//private mutators
	void set_name(string&);
	void set_password(string&);
	void change_password();

	//overloaded operators
	bool operator==(client&);
	friend ostream& operator<<(ostream&,client&);


	int inner_menu();
	void add_books(book);
	void return_books();
	void view_books();
	
	

public:
	//public methords

	//constructors
	client();
	client(int);

	//menu for clients
	int  menu();

};

ostream& operator<<(ostream& out,client& c){

	cout<<"^^^^^^^^^^^CLIENT^^^^^^^^^^\n";
	cout<<"NAME:: "<<c.name<<endl;
	cout<<"books with me "<<endl;
	for(int i=0;i<c.books_with_client.size();i++){
		cout<<c.books_with_client[i]<<endl;
	}

	return out;
}

void client::set_password(string& password){

	this->password=password;

	return ;
}



void client::set_name(string& name){

	this->name=name;

	return ;
}


client::client(int i){
	//version of constructor that allows garbage
}

string client::get_name(){

	//accesor for name

	return this->name;

}

bool client::operator==(client& c){

	//fxn to compare equality of two clients base don username

	return (name==c.get_name());
}

void client::view_books(){

	//private methord to vew client

	cout<<"#########################\n\n";
	cout<<"      "<<name<<endl<<endl;
	cout<<"books with you are\n\n";


	for(int i=0;i<books_with_client.size();i++){

		cout<<books_with_client[i]<<endl;

	}

	return ;

}

void client::change_password(){


	//private methord to change password to be called only by menu fxn

	password=getpass("enter your password");

}

void client::return_books(){

	//private methord to return books to library

	for(int i=0;i<books_with_client.size();i++){

		cout<<"######## "<<i<<" ###########\n"<<books_with_client[i]<<endl;
	}

	int index;

	cin>>index;

	if(index<0||index>=books_with_client.size()){

		cout<<"wrong input\n";

		return_books();

	}

	else{

		int qty;
		cout<<"enter the no of copies to return\n";
		cin>>qty;

		if(qty<0||qty>books_with_client[index].get_copies()){

			cout<<"wrong input \n";

			return_books();

		}

		else if(qty==books_with_client[index].get_copies()){

			books_with_client.erase(books_with_client.begin()+index);

			return ;
		}

		else {

			books_with_client[index].set_copies(books_with_client[index].get_copies()-qty);

			return ;
		}
	}


	return ;
}

void client::add_books(book b){

	//private methord to add books to the client collection

	for(int i=0;i<books_with_client.size();i++){

		if(books_with_client[i]==b){

			books_with_client[i].set_copies(books_with_client[i].copies+b.get_copies());

			return ;
		}
	}

	books_with_client.push_back(b);

	return ;

}


void client::get_data(){

	//private methord only to be called by constructor to get imp data

	cout<<"enter the name of the client (username must be unique) \n";
	getline(cin,name);

	cout<<"enter the password for the client\n";
	password=getpass("enter your password");



}


int client::inner_menu(){

	//fxn to return choice for the main menu to be called only by the menu

	int choice;

	cout<<"1:: issue books\n";
	if(this->books_with_client.size())cout<<"2:: return book\n";
	cout<<"3:: view books with you\n";
	cout<<"4:: change your password\n";
	cout<<"0:: return\n";

	cin>>choice;

	return choice;
}

int client::menu(){

	//menu for the client

	while(1){

		switch(inner_menu()){

			case 1:
			{
				cout<<"here we go\n";
				return 1;
			}
			break;

			case 2:
			this->return_books();
			break;

			case 3:
			this->view_books();
			break;

			case 4:
			this->change_password();
			break;

			case 0:
			return 0;
			break;

			default:
			cout<<"wrong choice\n";
			break;
		}


	}

	return 0;
}

client::client(){

	//priavte methord called by constructor to get data
	this->get_data();
}

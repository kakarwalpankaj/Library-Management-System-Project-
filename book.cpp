//header files necessary for implementation
#include<iostream>
#include<string>


using namespace std;

//intialisation of other classes for making them friend

class client;
class library;

class book {

	//friends

	friend class client;
	friend class library;

	//private data members

	string name;
	string publication;
	int copies;

	//private methords

	//private accessors

	void get_data();
	string get_name();
	string get_publication();
	int get_copies();

	//priavte mutators
	void set_copies(int);
	void set_name(string&);
	void set_publication(string&);

	//overloaded equality operator for compariisons
	bool operator==(book&);

	//overloaded extraction operator
	friend ostream& operator<<(ostream&,book&);
	
	
public:

	//public metords

	//constructors
	book();
	book(int);

};

string book::get_publication(){


	return this->publication;
}

string book::get_name(){

	return this->name;
}

void book::set_publication(string& publication){

	//priavte mutator

	this->publication=publication;

	return ;
}


void book::set_name(string& name){

	this->name=name;

	return ;
}

book::book(int k){

}




int book::get_copies(){
	//priavte methord to return no of copies

	return this->copies;

}

bool book::operator==(book& b){

	//private methord to compre equality of books

	return (b.name==name)&(b.publication==publication);
}


void book::set_copies(int n){
	//private methord to set copies
	//only to be used by libaray and client

	copies=n;
	return ;

}

ostream& operator<<(ostream& out,book& b){

	//private methord to print the book

	out<<"========BOOK========\n";
	out<<"NAME  ::         "<<b.name<<endl;
	out<<"PUBLICATION  ::  "<<b.publication<<endl;
	out<<"COPIES  ::       "<<b.copies<<endl;

	return out;

}

void book::get_data(){

//private methord called by the constructor for getting the data

	cout<<"enter the name of the book\n";
	cin>>name;

	cout<<"enter the publication\n";
	cin>>publication;

	cout<<"enter the no of copies\n";
	cin>>copies;


}

book::book(){

	//private methord for constuructor just to gaet the essential data;
	
	this->get_data();
}

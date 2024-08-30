#include"client.cpp"
#include<fstream>

using namespace std;


class library{

//driver class of this project which resembles a library
	//private data members
	string name;
	string password;
	int no_of_books;

	//vector of book and clients
	vector<book> lib_books;
	vector<client> lib_client;

	//private methords

	void get_data();
	int inner_menu();

	bool log_admin();
	void log_client();
	void sign_up();

	void admin_menu();

	void view();

	void set_name(string&);
	void set_password(string&);

	void add_book_admin();
	void add_book_admin(book&);
	void remove_book_admin();
	void remove_client_admin();
	void remove_book_admin_by_name();

	book issue_book();


public:

	//public methords
	library();
	void menu();
	void last_rites();
	friend ostream& operator<<(ostream&,library&);


};


void library::last_rites(){

	cout<<"this is call to last rites of library (we are saving the data)\n";

	fstream fout;

	fout.open("library_save.txt",ios::out);

	fout<<name<<" "<<password<<endl;
	fout<<no_of_books<<endl;

	for(int i=0;i<no_of_books;i++){

		fout<<lib_books[i].get_name()<<" "<<lib_books[i].get_publication()<<" "<<lib_books[i].get_copies()<<endl;
	}

	fout<<lib_client.size()<<endl;

	for(int i=0;i<lib_client.size();i++){

		fout<<lib_client[i].get_name()<<" "<<lib_client[i].password<<" "<<lib_client[i].books_with_client.size()<<endl;

		for(int j=0;j<lib_client[i].books_with_client.size();j++){

			fout<<lib_client[i].books_with_client[j].get_name()<<" "<<lib_client[i].books_with_client[j].get_publication()<<" "<<lib_client[i].books_with_client[j].get_copies()<<endl;

		}
	}

	cout<<"done with last rites\n";
	return ;
}


void library::sign_up(){

	client c(1);

	cout<<"enter unique username\n";
	cin>>c.name;

	for(int i=0;i<lib_client.size();i++){

		if(lib_client[i].get_name()==c.get_name()){

			cout<<"user already exist\n";
			sign_up();
			return ;
		}
	

	}

	bool k=1;
	
	string pass1,pass2;

	while(k){
		pass1=getpass("enter the password");
		pass2=getpass("enter the same password");

		if(pass1==pass2){
			c.password=pass1;
			k=0;
		}

		cout<<"re-enter the password\n";

	}
	
	cout<<"\n\n!!!!!!!!registered successful!!!!!!!!\n\n";

	lib_client.push_back(c);

	menu();


	return ;
}

book library::issue_book(){

	book b(1);


	for(int i=0;i<no_of_books;i++){

		cout<<"@@@@@@@@@@ "<<i<<" @@@@@@@@@@\n";
		cout<<lib_books[i]<<endl;

	}

	int index;
	while(1){

		cout<<"enter the index of the book";
		cin>>index;
		if(index<0||index>lib_books.size()){
			cout<<"wrong choice\n";
		}
		else{

			b.set_name(lib_books[index].name);
			b.set_publication(lib_books[index].publication);

			cout<<"library has "<<lib_books[index].get_copies()<<" copies how many do you wish to issue\n";
			int n;
			while(1){
				cin>>n;
				if(n>0&&n<lib_books[index].get_copies()){
					b.set_copies(n);
					lib_books[index].set_copies(lib_books[index].get_copies()-n);

					return b;
				}
				else if(n==lib_books[index].get_copies()){
					b.set_copies(n);
					no_of_books--;
					lib_books.erase(lib_books.begin()+index);

					return b;
				}
				else{
					cout<<"wrong choice\n";
				}
			}



		}
	}

	return b;


}

void library::add_book_admin(book& b){

	for(int i=0;i<no_of_books;i++){

		if(lib_books[i]==b){

			lib_books[i].set_copies(lib_books[i].get_copies()+b.get_copies());
			
			return ;
		}
	}

	lib_books.push_back(b);

	no_of_books++;
	return ;

}

void library::remove_client_admin(){

	if(!lib_client.size()){

		cout<<"~~~~~~~ WE ARE LACKING CLIENTS ~~~~~~~~~~~\n";

		return ;
	}

	for(int i=0;i<lib_client.size();i++){

		cout<<i<<" "<<lib_client[i].get_name()<<endl;
	}
	cout<<"these were the clients which of these you wish to remove\n";
	
	int n;
	cin>>n;
	if(n>=0&&n<lib_client.size()){

		for(int j=0;j<lib_client[n].books_with_client.size();j++){
			add_book_admin(lib_client[n].books_with_client[j]);
		}

		lib_client.erase(lib_client.begin()+n);

		cout<<"done\n";
		return ;
	}	

	cout<<"wrong choice\n";

	return ;
}

void library::remove_book_admin(){

	if(!no_of_books){


		cout<<"no more books in ;lib to remove\n";
		return ;
	}


	for(int i=0;i<lib_books.size();i++){

		cout<<"######### "<<i<<" #########\n";
		cout<<lib_books[i]<<endl;
	}

	cout<<"enter index of the book you want to remove\n";
	int index ;

	while(1){

		cin>>index;

		if(index>=0&&index<no_of_books){

			cout<<"library has "<<lib_books[index].get_copies()<<" copies how many do you wish to remove\n";
			int n;
			while(1){
				cin>>n;

				if(n>0&&n<lib_books[index].get_copies()){

					lib_books[index].set_copies(lib_books[index].get_copies()-n);
					break;
				}

				else if(n==lib_books[index].get_copies()){
					no_of_books--;
					lib_books.erase(lib_books.begin()+index);
					break;
				}

				else{
					cout<<"wrong choice\n";
				}

			}
			return ;
			
		}

		else{
			cout<<"wrong choice\n";
		}
	}

	return ;
}

void library::remove_book_admin_by_name(){


	book b(1);
	cout<<"enter the name of book\n";
	cin>>b.name;

	cout<<"enter the publisher\n";
	cin>>b.publication;

	for(int i=0;i<no_of_books;i++){

		if(lib_books[i]==b){

			cout<<"book found on shelf \n";
			cout<<"library has "<<lib_books[i].get_copies()<<" copies how many do you wish to remove\n";
			int n;
			while(1){
				cin>>n;
				if(n>0&&n<lib_books[i].get_copies()){
					lib_books[i].set_copies(lib_books[i].get_copies()-n);
					no_of_books--;
					break;
				}
				else if(n==lib_books[i].get_copies()){
					no_of_books--;
					lib_books.erase(lib_books.begin()+i);
					break;
				}
				else{
					cout<<"wrong choice\n";
				}
			}
		}
	}

	return ;
}

void library::add_book_admin(){

	book b;
	

	for(int i=0;i<no_of_books;i++){

		if(lib_books[i]==b){

			lib_books[i].set_copies(lib_books[i].get_copies()+b.get_copies());
			cout<<"book already existed so we updated the quantity\n";
			return ;
		}
	}

	lib_books.push_back(b);
	cout<<"book added to the shelf\n";
	no_of_books++;

	return ;
}

void library::set_name(string& name){

	this->name=name;

	return ;
}


void library::set_password(string& password){

	this->password=password;

	return ;
}

void library::view(){
	cout<<"####### TOUR ########\n";
	cout<<"NAME:: "<<name<<endl;
	cout<<"NO of books:: "<<no_of_books<<endl;
	for(int i=0;i<no_of_books;i++){
		cout<<lib_books[i]<<endl;
	}

	cout<<"NO of clients:: "<<lib_client.size()<<endl;

	for(int i=0;i<lib_client.size();i++){

		cout<<lib_client[i]<<endl;
	}
}

void library::log_client(){

	string name,pass;
	int index = -1;
	cout<<"enter the user_name\n";
	cin>>name;

	for(int i=0;i<lib_client.size();i++){
		if(lib_client[i].get_name()==name){
			index=i;
		}
	}
	if(index==-1){

		cout<<"user not find\n";
		return ;
	}

	pass=getpass("enter the password");

	if(pass!=lib_client[index].password){
		cout<<":::::: access denied ::::::::\n";
		return ;
	}

	cout<<"::::::: ACESS GRANTED :::::::\n";

	int x=1;

	while(x){

		x=lib_client[index].menu();
		if(x==1){
			if(!no_of_books){
				cout<<"library is empty\n";
			}
			else{

				lib_client[index].add_books(issue_book());
			}
		}
	}
	

}

void library::admin_menu(){

	cout<<"=========WELCOME ADMIN=========\n";

	int choice;

	while(1){

		cout<<"1:: change libarary_name\n";
		cout<<"2:: change admin password\n";
		cout<<"3:: take a tour\n";
		cout<<"4:: add_book\n";
		cout<<"5:: remove_book\n";
		cout<<"6:: remove book by name\n";
		cout<<"7:: remove client\n";
		cout<<"0:: return\n";

		cin>>choice;

		switch(choice){

			case 1:
			{
				string name;
				cout<<"enter new name of the llibrary\n\n";
				cin>>name;
				this->set_name(name);
				cout<<"\n!!!!!!!! LIB NAME CHANGED !!!!!!!!!\n\n";

			}
			break;

			case 2:{
				string password;
				password=getpass("enter the newpassword\n\n");
				this->set_password(password);

				cout<<"\n!!!!!!!! ADMIN PASSWORD CHANGED !!!!!!!!!\n\n";

			}
			break;

			case 3:
			{
				cout<<"~~~~~~~~WELCOME ADMIN~~~~~~~~~~\n\n";
				this->view();
			}
			break;

			case 4:
			{
				add_book_admin();

				cout<<"|||||| DONE ||||||\n\n";
			}
			break;
			
			case 5:
			{
				remove_book_admin();
			}
			break;

			case 6:
			{
				remove_book_admin_by_name();
			}
			break;

			case 7:
			{
				remove_client_admin();
			}
			break;

			case 0:
			{
				return ;
			}
			break;
		}

	}


}

bool library::log_admin(){


	string password;

	password=getpass("enter the admin pass");

	return password==this->password;

}

ostream& operator<<(ostream& out,library& l){

	cout<<"`````````````````````````````````\n";

	out<<"WELCOME TO "<<l.name<<" LIBRARY \n";

	out<<"we currently have "<<l.no_of_books<<" books\n";

	cout<<"WE CURRENTLY HAVE "<<l.lib_client.size()<<" CLIENTS\n\n";

	cout<<"`````````````````````````````````\n";

	return out;
}

void library::get_data(){

	fstream fin;

	fin.open("library_save.txt",ios::in);

	fin>>name;

	fin>>password;

	fin>>no_of_books;

	string temp;
	int copies,no_of_clients,m;

	book b(1);

	for(int i=0;i<no_of_books;i++){

		fin>>temp;
		b.set_name(temp);

		fin>>temp;
		b.set_publication(temp);

		fin>>copies;
		b.set_copies(copies);

		lib_books.push_back(b);
	}

	fin>>no_of_clients;
	client c(1);

	for(int i=0;i<no_of_clients;i++){

		fin>>temp;
		c.set_name(temp);

		fin>>temp;
		c.set_password(temp);

		fin>>m;

		for(int i=0;i<m;i++){

			fin>>temp;
			b.set_name(temp);

			fin>>temp;
			b.set_publication(temp);

			fin>>copies;
			b.set_copies(copies);

			c.books_with_client.push_back(b);


		}

		lib_client.push_back(c);

		c.books_with_client.clear();


	}

	return ;

}


library::library(){
	//public constructor for lib
	//fxn to read previous data

	this->get_data();

}

int library::inner_menu(){

	int choice;

	cout<<"1:: login as admin\n";
	cout<<"2:: login as client\n";
	cout<<"3:: signup as client\n";
	cout<<"0:: return\n";
	cin>>choice;

	return choice;

}


void library::menu(){


	while(1){

		switch(inner_menu()){

			case 1:
			if(log_admin()){
				cout<<"\n:::::::: ACCESS GRANTED ::::::::::\n\n";
				admin_menu();
			}
			break;

			case 2:
			log_client();
			break;

			case 3:
			sign_up();
			break;

			case 0:
			return ;
			break;

			default:
			cout<<"wrong choice\n";
			break;

		}

	}

	return ;
}


int main(){

	library lib;

	cout<<lib<<endl;

	lib.menu();

	lib.last_rites();

	return 0;

}
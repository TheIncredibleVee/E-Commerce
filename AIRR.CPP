#include<fstream.h>
#include<dos.h>
#include<iomanip.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<process.h>
#include<string.h>
#include<graphics.h>

int id=-1;
class user{
	private:
		long phone;
		int u_id;
		char conpass[20];
		char emailid[50];
		char name[20];
		char pass[20];
		char address[50];
		struct date d;
		char gender;
		void password();
	public:
		void get();
		void display();
		long retphone();
		char* retname();
		char* retemail();
		char* retpass();
		char* retad();
		int retid();
		void chpass(char*);
};


class product{
	private:
		int pno;
		char pname[20];
		char category[20];
		float cost;
		char color[20];
		float ratings;
	public:
		void get();
		void put();
		char* retcat();
		char* retname();
		int retpno();
		float retprice();
};
product p; user check;
product arr[50];
int user_id=-1;

class order{
	private:
		char date[50];
		//time_t tim;
		int product_id;
		int u_id;
		char product_name[50];
		char address[100];
		float price;
		int qty;
	public:
		order(product p, int user_id, int qty, char* a){
			add_date();
			add_productname(p.retname());
			add_productid(p.retpno());
			add_uid(user_id);
			add_address(a);
			add_qty(qty);
			add_price(p.retprice());
		}
		void add_date();
		void add_productid(int);
		void add_uid(int);
		void add_productname(char*);
		void add_address(char*);
		void diaplydet();
		int retid();
		void add_qty(int);
		void add_price(float);
};
class cart{
	private:
		int pno;
		char pname[20];
		char category[20];
		float cost;
		int phone;
		char name[20];
		char address[50];
		float price;
		int qty;
	public:
		void val(int);
		void display();
		float retprice();
		int retpno();
};
cart c;
char add[50];
int op,ph=-1,checkk=0,pno, phno;
char* cate[5]={"ELECTRONICS", "FURNITURE", "CLOTHING", "BOOKS", "SPORTS AND FITNESS"};
int no=0;
ifstream fin;
fstream mem,shopcart;
ofstream temp;
char pass[20],username[20],un[20],ad[20];
int flag=1;
int checkemail(char*);
void load();
void firstpg();
void signuppg();
void loginpg();
void mainpg();
void admin();
int num;
char m[30],l[30];      //m for loginid  l for password

int userpos=0;
void firstpg(){
	clrscr();
	char  choice;
	gotoxy(25,7);
	cout<<" ==================="<<endl;
	gotoxy(25,9);
	cout<<"     1. SIGN UP"<<endl;
	gotoxy(25,10);
	cout<<"     2. SIGN IN"<<endl;
	gotoxy(25,11);
	cout<<"     3. EXIT"<<endl;
	gotoxy(25,13);
	cout<<" ==================="<<endl;
	gotoxy(25,16);
	cout<<"  \n    *.Admin Login "<<endl;
	gotoxy(25,18);
	cout<<" ==================="<<endl;
	up:
	gotoxy(25,23);
	cout<<"    Enter choice :-"<<'\t';
	choice=getche();
	cout<< endl;
	switch(choice){
		case '1':
			signuppg();
			break;
		case '2':
			loginpg();
			break;
		case '3':
			exit(0);
		case '*':
			admin();
			break;
		default :
			gotoxy(25,25);
			cout<<"Invalid choice try again"<<endl;
			goto up;
			
	}
}	//END of First Page........
void signuppg(){
	clrscr();
	user rec;
	rec.get();
	cout<<"\n\n    1.Submit  ";
	cout<<"  \n    2.Cancel  ";
	cout<<"  \n    3.Refresh ";
	start:
	cout<<"\n\n   Enter choice :  ";
	char choice;
	choice=getche();
	switch(choice){
	case '1':
	ofstream fout("user.dat",ios::binary|ios::app);
	fout.write((char*)&rec,sizeof(rec));
	fout.close();
		cout<<"Account Successfully created\n Press any key to continue to loogin page\n";
		getch();
		loginpg();
		break;
	case '2':
		firstpg();
		break;
	case '3':
		signuppg();
		break;
	case '*':
		admin();
		break;
	default:
		cout<<"    invalid choice !!! ";
		getch();
		signuppg();
	}
}	// END of signup page.....

void loginpg(){
	clrscr();
	int i=0;
	char ch= ' ';
	gotoxy(30,8);
	cout<<" SIGN IN "<<endl<<endl;
	gotoxy(23,10);
	cout<<" Enter Login ID  ";
	cin>>m;
	gotoxy(23,12);
	cout<<" Enter Password  ";
	while(ch!=13){
		ch=getch();
		l[i++]=ch;
		if(ch!=13)
			cout<<"*";
	}
	l[--i]='\0';
	ifstream fin("user.dat",ios::binary|ios::in);
	fin.seekg(0);
	if(!fin){
		gotoxy(20,15);cout<<"FILE DOES NOT EXISTS !!! "; getch(); fin.close();
	firstpg();
	}
	int flag=0;
	while(fin.read((char*)&check,sizeof(check))){
   //   check.show();
		if(strcmp(check.retemail(),m)==0){
			if(strcmp(check.retpass(),l)==0){
				flag=1;
				userpos=fin.tellg()-sizeof(user);
				user_id=check.retid();
				strcpy(add,check.retad());
				fin.close();
				load();
				mainpg();
			}
			else{
				gotoxy(20,15);  cout<<" credentials donot match !!! ";
			getch();
			fin.close();
			loginpg();
			}
		}
	}
	fin.close();
	if (flag==0){
		gotoxy(21,15); cout<<" User Doesnot Exists !!!";
		getch();
		firstpg();
	}
}	// END of Login page....

void mainpg(){
	clrscr();
	gotoxy(20,4);   cout<<" ============================";
	gotoxy(20,5);   cout<<setw(18)<<m;
	gotoxy(20,6);   cout<<" ============================";
	gotoxy(20,8);   cout<<"      1.SHOP        ";
	gotoxy(20,9);   cout<<"      2.CART          ";
	gotoxy(20,10);  cout<<"      3.PREVIOUS SHOOPED ITEMS           ";
	gotoxy(20,11);  cout<<"      4.ACCOUNT SETTINGS ";
	gotoxy(20,12);  cout<<"      5.LOGOUT         ";
	gotoxy(20,14);  cout<<" ============================";
	gotoxy(20,16);  cout<<"     Input Choice - ";
	char input;
	input= getche() ;
	int n=0,f;
	fin.close();
	switch(input){

		case'1':
			clrscr();
			fin.open("product.dat",ios::binary);
			for(int pos=0;!fin.eof();pos++,++n){
				fin.read((char*)&arr[pos],sizeof(product));
				if(fin.eof())
					break;
				arr[pos].put();
				cout<<endl;
			}
			fin.close();
			cout<<endl<<endl;
			cout<<"1. Filter by category"<<endl;
			cout<<"";
			buy:
			cout<<"\n*. Buy"<<endl;
			cout<<"9. Go to Menu"<<endl;
			cout<<"Enter your choice\n ";

			char choice=getche();
			switch(choice){ 
				case '1':
					clrscr();
					cout<<"CHOOSE CATEGORY\n";
					for(int i=0;i<5;i++){
						cout<<i+1<<". "<<cate[i]<<endl;
					}
					char ch=getche();
					for(int h=0;h<n;++h){
						if(!strcmpi(arr[h].retcat(), cate[ch-'1'])){
							arr[h].put();
						}
					}
					goto buy;
					break;
				case '*':
					clrscr();
					cout<<"Enter Product No.:";
					cin>>pno;
					for(f=0;f<n;f++){
						if(arr[f].retpno()==pno){
							flag=0;
							arr[f].put();
							break;
						}
					}
					if(flag==1){ 
						cout<<"NO such product"; 
						getch();
						clrscr();
						mainpg();
						break;
					}
					cout<<endl;
					int qty;
					cout<<"Enter Quantity:";
					cin>>qty;
					cout<<"Total Amount:"<<qty*arr[f].retprice();
					cout<<endl;
					cout<<"1.Buy Now"<<endl;
					cout<<"2.Add to Cart"<<endl;
					cout<<"3.Go to Menu"<<endl;
					int choice2;
					cin>>choice2;
					switch(choice2){
						case 1:
							cout<<"Order Placed!\nThe rest of the details will be messaged to you on the mobile number provided\nThanks for shopping :)\n Press any key to continue\n"<<endl;
							fstream log("log.dat", ios::app|ios::binary|ios::out|ios::in);
							order d(arr[f], user_id, qty, add);
							/*d.add_date();
							d.add_productname(arr[f].retname());
							d.add_productid(arr[f].retpno());
							d.add_uid(user_id);
							d.add_address(check.retad());
							d.add_qty(qty);
							d.add_price(arr[f].retprice());*/
							log.write((char*)&d, sizeof(order));
							log.close();
							getch();
							clrscr();
							d.diaplydet();
						//	date s;
						//	getdate(&s);
						//	cout<<s.da_day<<endl<<s.da_mon<<endl<<s.da_year<<endl;
							getch();
							mainpg();
							break;
						case 2:
							clrscr();
							checkk=1;
							shopcart.open("Cart.dat",ios::binary|ios::in|ios::out|ios::app);
							c.val(f);
							shopcart.write((char*)&c,sizeof(cart));
							shopcart.close();
							cout<<"Sucessfully added to cart, keep shopping\nPress any key to continue\n";
							getch();
							clrscr();
							mainpg();
							break;
						case 3:
							clrscr();
							break;
						default:
							cout<<"Invalid Choice"; 
							
							break;
					}
					break;
				case '2':
					cout<<"BEST SELLERS \n";
				case '9':
					clrscr();
					mainpg();
					break;
				default:
					cout<<"Invalid Choice";
					getch();
					clrscr();
					mainpg();
					break;
			}
			break;

		case '2':
			clrscr();
			fstream shop;
			shop.open("Cart.dat",ios::binary|ios::in|ios::out);
			if(shop.eof()){
				cout<<"No product in the cart";
				getch();
				clrscr();
				mainpg();
				break;
			}
			product s[50];
			int i=0;
			while(!shop.eof()){
				shop.read((char*)&s[i++],sizeof(cart));
				if (shop.eof()){
					if (i==1){
							cout<<"No product in the cart";
							getch();
							clrscr();
							mainpg();
					}
					break;
				}
				c.display();
				cout<<endl;
			}
			shop.close();
			//cout<<"Enter Quantity:";
	    	//int qty;
	    	//cin>>qty;
			//cout<<"Total Amount:"<<qty*c.retprice()<<endl;
			cout<<"1.CHECKOUT"<<endl;
			cout<<"2.DELETE ALL"<<endl;
			int choice3;
			cin>>choice3;
			switch(choice3){
				case 1:
					clrscr();
					cout<<"Order Placed!\nThanks for shopping :)\n Press any key to continue";
					fstream log("log.dat", ios::app|ios::binary|ios::out|ios::in);
					for(int j=0;j<i;++j){
						order d(s[j], user_id, 1, add);
						log.write((char*)&d, sizeof(order));
					}
					log.close();
					remove("Cart.dat");
					getch();
					clrscr();
					//d.diaplydet();
					checkk=0;
					getch();
					break;
		 		case 2:
					clrscr();
					/*shop.open("Cart.dat",ios::binary|ios::in|ios::out);
					temp.open("Temp.dat",ios::binary);
					while(!shopcart.eof()){
						shop.read((char*)&c,sizeof(cart));
						if(c.retpno()!=pno){
							temp.write((char*)&c,sizeof(cart));
			   			}
					}
					shop.close();temp.close();*/
			 		remove("Cart.dat");
			 		//rename("Temp.dat","Cart.dat");
			 		clrscr();
			 		mainpg();
					break;
				default:
					cout<<"Invalid choice";
					clrscr();
					break;
		}
			clrscr();
			mainpg();
			break;

		case '3':
			clrscr();
			gotoxy(25, 10);
			cout<<"PREVIOUSLY SHOPPED ITEMS"<<endl;
			fstream logg;
			logg.open("log.dat", ios::binary|ios::in|ios::out);
			if(!logg){
				cout<<"No Record found!!!";
				clrscr();
				mainpg();
			}
			logg.seekg(0);
			order q(p, 10,10,"jhash");
			while(!logg.eof()){
				logg.read((char*)&q, sizeof(order));
				if(logg.eof())
					break;
				if(q.retid()==user_id){
					q.diaplydet();
					cout<<endl;
				}
			}
			logg.close();
			getch();
			mainpg();
			break;
		case '4':
	 		clrscr();
			user change;
			
  			gotoxy(25,7);  cout<<" ========================";
			gotoxy(25,8);  cout<<"     ACCOUNT SETTINGS ";
			gotoxy(25,9);  cout<<" ========================";
			gotoxy(25,11); cout<<"   1.CHANGE PASSWORD";
			gotoxy(25,12); cout<<"   2.DELETE ACCOUNT\n";
			gotoxy(25,13); cout<<"   3.EXIT\n";
			gotoxy(25,15); cout<<"   Enter choice :  ";
			cin>>n;
			switch(n){
				case 1:
				char passnow[30],passn[30],conpassn[30],ch;
				int i;
				reset: clrscr();
				gotoxy(17,6); cout<<" enter existing password :";
				cin>>passnow;
			if(strcmp(passnow,l)==0){
				gotoxy(17,8); cout<<" Enter new password :- ";
				i=0;
				ch=' ';
					while(ch!=13){
						ch=getch();
						passn[i++]=ch;
						cout<<"*";
					}
					passn[--i]='\0';
					gotoxy(17,10); cout<<" Confirm your password :- ";
					i=0;
					ch=' ';
					while(ch!=13){
						ch=getch();
						conpassn[i++]=ch;
						cout<<"*";
					}
					gotoxy(14,12); cout<<"---------------------------------";
					conpassn[--i]='\0';
					if(strcmp(conpassn,passn)!=0){
						gotoxy(17,15);cout<<"password donot match !!!";
					getch();
					goto reset;
					}
					else{
					fstream fio("user.dat",ios::in|ios::out|ios::binary);
					fio.seekg(userpos);
					fio.read((char*)&change,sizeof(change));
					change.chpass(passn);
					fio.seekg(userpos);
					fio.write((char*)&change,sizeof(change));
					fio.close();
    					gotoxy(17,15); cout<<" Password successfully changed!";
    					getch();
    					loginpg();
    				}
  				}
   				else {
					gotoxy(17,15); cout<<" Incorrect Password ";
					getch();
	  				goto reset;
				}
				break;
			case 2:
	   			ifstream fin("user.dat",ios::in|ios::binary);
	   			ofstream fout("temprecord.dat",ios::out|ios::binary);
	   			user pickup;
	   			while(fin.read((char*)&pickup,sizeof(pickup))){
					int add=userpos+sizeof(pickup);
	    			if(fin.tellg()==add)
						continue;
	    			else
					fout.write((char*)&pickup,sizeof(pickup));
	    		}

				fin.close();
				fout.close();

	   			remove("user.dat");
	   			rename("temprecord.dat","user.dat");
	   			clrscr();
	  			gotoxy(31,11); cout<<"o-------------------o";
	  			gotoxy(31,12); cout<<"|  Account Deleted  |";
	  			gotoxy(31,13); cout<<"o-------------------o";
	    		getch();
			firstpg();
				break;
			case 3:
				mainpg();
				break;
			}
		case '5':
			exit(0);
			break;
		default:
			cout<<"INAVLID CJOICE";
			getch();
			clrscr();
			mainpg();
			break;
	}
}		//END Of Main Page.......

void admin(){
	char p[10]; int op2,n;ofstream fout;product q;
    cout<<"Enter Password:";
    gets(p);
    if(strcmp(p,"VINAY IS GREAT")==0){ 
		clrscr();
		cout<<"AMDIN PAGE"<<endl;
		cout<<"1. Enter Products"<<endl;
		cout<<"2. Delete Products"<<endl;
		cout<<"3. Go to Menu"<<endl;
		cout<<"Enter option:";
		cin>>op2;
		switch(op2){
			case 1:
				clrscr();
		    	fout.open("product.dat",ios::binary|ios::app);
		    	cout<<"Enter no. of products to be entered:";
		    	cin>>n;
		    	cout<<"Enter products"<<endl;
		    	for(int i=0;i<n;++i){ 
					q.get();
					fout.write((char*)&q,sizeof(product));
					cout<<endl;
				}
			cout<<"Added"; fout.close();
			getch();
				clrscr();
				firstpg();
				break;
			case 2: clrscr();
				temp.open("Temp2.dat",ios::binary);
		    	fin.open("product.dat",ios::binary);
		    	int prono;
		    	cout<<"Enter product number to be deleted:";
			cin>>prono;
		    	while(!fin.eof()){
					fin.read((char*)&q,sizeof(product));
					if(prono!=q.retpno()){
						temp.write((char*)&q,sizeof(product));
					}
			}
		    	temp.close();fin.close();
		    	remove("product.dat");
		    	rename("Temp2.dat","product.dat");
		    	cout<<"Deleted";
		    	getch();
				clrscr();
				firstpg();
				break;
			case 3:
				clrscr();
				firstpg();
				break;
			default:
				cout<<"Invalid choice";
				getch();
				clrscr();
				firstpg();
				break;
		}
	}
	else{
		cout<<"INCORRECT PASSWORD\n ";
		getch();
		firstpg();
	}
}
/*
void get()
{ cout<<"Product No.:";
	cin>>pno;
    cout<<"Product name:";
    gets(pname);
    cout<<"Cost:";
    cin>>cost;
    cout<<"Category:";
    gets(category);
    cout<<"Color";
    gets(color);
  }
  void put()
  { cout<<"Product No.:"<<pno<<" "<<endl;
    cout<<"Product Name:"<<pname<<"  "<<endl;
    cout<<"Rs."<<cost<<"\t";
    cout<<"Color "<<color<<"\t";
  }

*/

/*
void val()
 { pno=p.retpno();
   strcpy(pname,p.retname());
   strcpy(category,p.retcat());
   phone=member.retphno();
   strcpy(name,member.retname());
   strcpy(address,member.retad());
   cost=p.retprice();
 }

*/
/*

*/


void load(){
	int x=170,i,gdriver=DETECT,gmode;
	initgraph(&gdriver,&gmode,"C:\BGI");
	settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
	outtextxy(170,180,"LOADING,PLEASE WAIT");
	for(i=0;i<300;++i){
		delay(3);
		line(x,200,x,220);
		x++;
	}
	outtextxy(170,250,"Press any key to continue......");	
	getch();
	closegraph();
}
void main(){
	clrscr();
	int op,ph=-1,check=0,pno;
	ifstream fin;
	fstream mem,shopcart;
	ofstream temp;
	char pass[20],user[20],un[20],ad[20];
	int flag=1;
	load();
	firstpg();
	mainpg();

  getch();
}

void user::get(){
	cout<<" Enter your name :-"<<'\t';
	gets(name);
	cout<<endl;
	email:
	cout<<" Enter Email ID:-"<<'\t';
	gets(emailid);
	if(checkemail(emailid)){
		cout<<endl<<"Invaild email\n";
		goto email;
	}
	cout<<endl;
	password();
	cout<<endl<<endl;
	cout<<" Enter birth date(dd) :-"<<'\t';
	cin>>d.da_day;
	cout<<endl;
	cout<<" Enter birth month :-"<<'\t';
	cin.ignore();
	cin>>d.da_mon;
	cout<<endl;
	cout<<" Enter birth year(yyyy) :-"<<'\t';
	cin.ignore();
	cin>>d.da_year;
	cout<<endl;
	cout<<" Enter gender(m/f) :-"<<'\t';
	gender=getche();
	cout<<endl;
	cin.ignore();
	cout<<" Enter mobile number(10 digit) :-"<<'\t';
	int digit;
	phone=0;
	for(int i=9;i>=0;--i){
		digit=getche()-48;
		phone+=	digit*pow(10,i);
	}
	cout<<endl;
  	cout<<" Enter Address :-"<<'\t';
	gets(address);
	cout<<endl;
 }
 
int checkemail(char* s){
 	int flag=1;
 	for(int i=0;i<strlen(s)-3;++i){
 		if (s[i]=='.'&& s[i+1]=='c'&& s[i+2]=='o'&& s[i+3]=='m')
 			flag=0;
	 }
	 for(i=0;i<strlen(s)-6;++i){
		if (s[i]=='@'){
 			flag=0;
 			break;
 		}
 			
		else
			flag=1;
	 }
	 return flag;
 }

void user::password(){
	cout<<" Enter password :-"<<'\t';
	int i=0;
	char ch;
	while(ch!=13){
		ch=getch();
		pass[i++]=ch;
		cout<<"*";
	}
	pass[--i]='\0';
	cout<<endl<<endl;
	cout<<" Confirm your password :-"<<'\t';
	i=0;
	ch=' ';
	while(ch!=13){
		ch=getch();
		conpass[i++]=ch;
		cout<<"*";
	}
	conpass[--i]='\0';
	if(strcmp(conpass,pass)!=0){
		cout<<"\n\n password donot match !!! \n\n Re";
		password();   
	}
 }

/* void user::display(){
	cout<<"Product No.:"<<pno<<endl;
	cout<<"Product Name:"<<pname<<endl;
	cout<<"Price:"<<cost<<endl;
	cout<<"Customer Name:"<<name<<endl;
	cout<<"Address:"<<address<<endl;
} */
long user::retphone(){
	return  phone;
}
char* user::retad(){
	return address;
}
char* user::retpass(){
	return pass;
}
int user::retid(){
	return u_id;
}
char* user::retname(){
	return name;
}
char* user::retemail(){
	return emailid;
}
void product::get(){
	cout<<"Product No.:";cin>>pno;
    cout<<"Product name:";
    gets(pname);
    cout<<"Cost:";
    cin>>cost;
    cout<<"Category:";
    for(int i=0;i<5;++i){
    	cout<<i+1.<<" "<<cate[i]<<endl;
	}
	cat:
	char x;
	x=getche();
	if(x>='1'&& x<='5')
		strcpy(category, cate[x-'1'])
	else{
		cout<<"INAVLAD CATEGORY"<<endl;
		goto cat;
	}
	cout<<"Ratings(1-5)";
	cin>>ratings;
	if(ratings>5)
		ratings=5;
	else if (ratings<1)
		ratings =1;
    //strcpy(cate[no++],category);
}
void product::put(){
	cout<<"Product No.:"<<pno<<" ";
    cout<<"Product Name:"<<pname<<"  ";
    cout<<"Rs."<<cost<<"\t";
}
int product::retpno(){
	return pno;
}
char * product::retcat(){
	return category;
}
char *  product::retname(){	return pname;
}
float product::retprice(){
	return cost;
}
void cart::val(int f){
	pno=arr[f].retpno();
	strcpy(pname,arr[f].retname());
	strcpy(category,arr[f].retcat());
	phno=check.retphone();
	strcpy(name,check.retname());
	strcpy(address,check.retad());
	cost=arr[f].retprice();
}
void cart::display(){
	cout<<"Product No.:"<<pno<<endl;
	cout<<"Product Name:"<<pname<<endl;
	cout<<"Price:"<<cost<<endl;
	cout<<"Customer Name:"<<name<<endl;
	cout<<"Address:"<<address<<endl;
}
float cart::retprice(){
	return cost;
}
int cart::retpno(){
	return pno;
}
void user::chpass(char* str){ 
	strcpy(pass,str); 
}
void order::add_address(char* s){
	strcpy(address, s);
}
void order::add_date(){
	strcpy(date, __DATE__);
}
void order::add_productid(int x){
	product_id=x;
}
void order::add_productname(char* s){
	strcpy(product_name, s);
}

void order::add_uid(int x){
	u_id=x;
}
void order::diaplydet(){
	cout<<endl;
	cout<<"Detials of the order are as follows"<<endl;
	cout<<"PRODUCT NAME:\t"<<product_name<<endl;
	cout<<"ADDRESS\t"<<address<<endl;
	cout<<"DATE\t"<<date<<endl;
	cout<<"PRICE\t"<<qty*price<<endl;
}
int order::retid(){
	return u_id;
}
void order::add_qty(int x){
	qty=x;
}
void order::add_price(float f){
	price=f;
}



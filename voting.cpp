#include<fstream.h>
#include<conio.h>
#include<ctype.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<dos.h>

int temp,ch,color=CYAN;
void print_border()
{  int j;
   for(j=2;j<=79;j+=2)
   { gotoxy(j,1);

      cprintf(" ");
   }
   for(j=2;j<=24;j++)
   { gotoxy(1,j);
     cout<<(char)17;

   }
   for(j=2;j<=24;j++)
   { gotoxy(80,j);
     cout<<(char)16;

   }
   for(j=2;j<=79;j+=2)
   { gotoxy(j,25);
      cout<<"¬";
   }

}
class candidate
{
	 char name[30];
	 int votes;
      public:
       candidate()
       {  strcpy(name,"");
	   votes=0;
       }
       void set_name(char *s)
       { strcpy(name,s);
	 votes=0;
       }
       int getvotes()
       {  return votes;
       }
       char* getname()
       {   return name;
       }
       void add_one_vote()
       { votes++;
       }
};

class post
{
	candidate list[10];
	char name[30];
	int total_candidates;
	int maxvotes;
     public:
     void get_post_data();
     void show_post_data();
     char* get_post_name()
     {  return name;
     }
     void modify_name()
     { char nm[30];
       gotoxy(5,22);
       cout<<"Enter new name of the post(. to retain older value) ::: ";
       gets(nm);
       if(strcmp(nm,".")!=0)
       {  strcpy(name,nm);
       }
     }
     int modify_candidate_name();
     int add_candidates();
     int delete_candidates();
     void vote();
     void show_winners(int);
};
int post::modify_candidate_name()
{  //DISPLAY CANDIDATE LIST OF THE SELECTED POST
	char nm[30];
	clrscr();
	print_border();
	int x=10,y=2;
	for(int i=0;i<total_candidates;i++)
	{  gotoxy(x,y);
	   y+=2;
	   if(y==20)
	   { x=30;
	     y=2;
	   }

	   cout<<i+1<<"."<<list[i].getname()<<endl;

	}
	gotoxy(16,22);
	cout<<"ENTER SERIAL NUMBER OF THE NAME TO BE MODIFIED ::: ";
	cin>>temp;
	if(total_candidates<temp || temp<=0)
	{ textcolor(RED+BLINK);
	  gotoxy(26,24);
	  cprintf("INVALID SERIAL NUMBER");
	  return 0;
	}
	else
	{   gotoxy(16,22);
	    cout<<"                                                     ";
	    gotoxy(16,22);
	    cout<<"ENTER NEW NAME FOR CANDIDATE("<<list[temp-1].getname()<<"):::";
	    gets(nm);
	    list[temp-1].set_name(nm);
	    return 1;
	}
}
void post::vote()
{   int y=5;
    for(int i=0;i<total_candidates;i++)
    {  gotoxy(13,y);
       y+=2;
       cout<<i+1<<"."<<list[i].getname();
    }
    gotoxy(17,23);
    cout<<"ENTER SERIAL NUMBER OF THE CANDIDATE TO VOTE ::: ";
    cin>>temp;
    if(temp>0 && temp<=total_candidates)
    { list[temp-1].add_one_vote();
    }
}
void post::get_post_data()
{     clrscr();
      print_border();
      gotoxy(15,3);
       cout<<"Enter post name ::: ";
	gets(name);
	int tot_cd=0;
	char nm[30]="";
	gotoxy(10,5);
	cout<<"Enter names of the candidates(. to stop,max 10)";
	gotoxy(14,7);
	int k=8;
	do
	{   cout<<"Enter name of the candidate ::: ";
	    gets(nm);
	    gotoxy(14,k++);

	  if(strcmp(nm,".")!=0)
	  {  list[tot_cd].set_name(nm);
	     tot_cd++;
	  }
	}while(strcmp(nm,".")!=0 && tot_cd<10);
	if(tot_cd==10)
	{ gotoxy(12,k);
	  textcolor(RED+BLINK);
	  cprintf("Cannot add more than 10 candidates to a post");
	  getch();
	}

	total_candidates=tot_cd;

}
void post::show_post_data()
{  int i;
   maxvotes=0;
   cout<<name;//FORMAT OUTPUT ACCORDINGLY
   for(i=0;i<total_candidates;i++)
   {  cout<<"\n\t"<<i+1<<"."<<list[i].getname()<<" - "<<list[i].getvotes();
     if(list[i].getvotes()>maxvotes)
     {  maxvotes=list[i].getvotes();

     }
   }

}
int post::add_candidates()
{   int counter=0;
    char nm[30];
    if(total_candidates==10)
    { gotoxy(15,20);
      cout<<"                                                            ";
      gotoxy(25,20);
      textcolor(RED+BLINK);
      cprintf("CANNOT ADD MORE CANDIDATES");
      gotoxy(23,22);
      cprintf("LIST ALREADY HAS 10 CANDIDATES");
      return 0;
    }
    else
    {  clrscr();
       print_border();
       gotoxy(16,5);
       cout<<"Enter names of the candidates(. to stop,max 10)";
       gotoxy(14,7);
       int k=8;
       do
       {   cout<<"Enter name of the candidate ::: ";
	   gets(nm);
	   gotoxy(14,k++);
	   if(strcmp(nm,".")!=0)
	   {  list[total_candidates+counter].set_name(nm);
	      counter++;

	   }
       }while(strcmp(nm,".")!=0 && total_candidates+counter<10);
       if(total_candidates+counter==10)
       {  gotoxy(12,k);
	  textcolor(RED+BLINK);
	  cprintf("Cannot add more than 10 candidates to a post");
       }
       total_candidates+=(counter);
       return 1;
    }
}
int post::delete_candidates()
{
     if(total_candidates==0)
     { gotoxy(15,22);
       cout<<"Post Doesn't Have Any Candidates to Delete";
       return 0;
     }
     else
     {  //DISPLAY CANDIDATE LIST OF THE SELECTED POST
	clrscr();
	print_border();
	char nm[30];
	int x=14,y=3;
	for(int i=0;i<total_candidates;i++)
	{ gotoxy(x,y);
	  y+=2;
	  cout<<i+1<<"."<<list[i].getname()<<endl;


	}
	gotoxy(17,y);
	cout<<"ENTER SERIAL NUMBER OF THE NAME TO BE DELETED ::: ";
	cin>>temp;
	if(total_candidates<temp || temp<=0)
	{ gotoxy(17,y);
	  cout<<"                                                         ";
	  gotoxy(25,y);
	  textcolor(RED+BLINK);
	  cprintf("INVALID SERIAL NUMBER !!!");
	  return 0;
	}
	else
	{  if(temp==total_candidates)
	   {  total_candidates--;

	   }
	   else
	   { for(i=temp-1;i<total_candidates-1;i++)
	     {  list[i]=list[i+1];
	     }
	     total_candidates--;
	   }
	   return 1;
	}
      }

}
void post::show_winners(int sno)
{  int i;
   if(maxvotes>0)
   {  cout<<"\n"<<sno<<"."<<name;
      cout<<"\n    -----------------------";
      cout<<"\n\t:::WINNER(s):::";
      for(i=0;i<total_candidates;i++)
      {    if(list[i].getvotes()==maxvotes)
	   {   cout<<"\n\t"<<"-->"<<list[i].getname();
	   }
      }
      cout<<"\n    -----------------------";
    }
}
class administrator
{
	char username[30];
	char password[30];
	int total_post;
    public:
    administrator()
    {  strcpy(username,"voter");
       strcpy(password,"");
    }
    char* get_username()
    {  return username;
    }

    int match(char *u,char *p)
    {   if(strcmp(u,username)==0 && strcmp(p,password)==0)
	{  return 1;
	}
	else
	{ return 0;
	}
    }
    int match(char *u)
    {   if(strcmp(u,username)==0)
	{  return 1;
	}
	else
	{ return 0;
	}
    }
    void get_data()
    { gotoxy(25,11);
      cout<<"ENTER USERNAME ::: ";
      gets(username);
      gotoxy(25,13);
      cout<<"ENTER PASSWORD ::: ";
      gets(password);
    }
    int modify_pass()
    {  char p[30];
	gotoxy(28,10);
       cout<<"ENTER OLD PASSWORD ::: ";
       gets(p);
       if(strcmp(p,password)==0)

       { gotoxy(18,12);
	 cout<<"ENTER NEW PASSWORD(. to retain older one) ::: ";
	 gets(p);
	 if(strcmp(p,".")!=0)
	 {  strcpy(password,p);
	 }
	 return 1;
       }
       else
       {    textcolor(RED);
	    clrscr();
	    print_border();
	    gotoxy(30,13);
	    cout<<"PASSWORD INCORRECT !!! ";
	    gotoxy(25,15);
	    cout<<"ABORTING PASSWORD CHANGE OPERATION";
	      return 0;
       }
    }

    void new_candidate_list();
    void show_results();
    void edit_candidate_list();
    int show_post_list();
    void set_total_posts();
    void vote();
};
void administrator::new_candidate_list()
{ int number_of_post;
  clrscr();
  print_border();

  gotoxy(28,12);
  cout<<"Enter number of posts ::: ";
  cin>>number_of_post;
  post X;
  ofstream fout("PostCandidates.DAT",ios::binary|ios::app);
  for(int i=0;i<number_of_post;i++)
  {   X.get_post_data();
    //Write X to the file
       fout.write((char*)&X,sizeof(X));
  }
  total_post+=number_of_post;
  fout.close();
  clrscr();
  print_border();
  gotoxy(28,12);
  cout<<"POST(s) ADDED SUCCESSFULLY!!!!";
  getch();

}
void administrator::set_total_posts()
{
  int counter=0;
  post X;
   ifstream fin("PostCandidates.DAT",ios::binary);
   while(fin.read((char*)&X,sizeof(X)))
   {  counter++;
   }
   total_post=counter;
   fin.close();
}
void administrator::show_results()
{ clrscr();
  cout<<"\nDisplaying results shortly";
  for(int i=0;i<5;i++)
  {  cout<<". ";
    delay(300);
  }
  cout<<"\n";
   post X;
   i=1;
   ifstream fin("PostCandidates.DAT",ios::binary);
   ofstream fout("PC.DAT",ios::binary);
   while(fin.read((char*)&X,sizeof(X)))
   {   cout<<"\n"<<i++<<".";
       X.show_post_data();
       fout.write((char*)&X,sizeof(X));

       cout<<endl;

   }
   fin.close();
   fout.close();
   remove("PostCandidates.DAT");
   rename("PC.DAT","PostCandidates.DAT");
   if(i>1)
   {  fin.open("PostCandidates.DAT",ios::binary);
      fin.seekg(0);
      i=1;
      while(fin.read((char*)&X,sizeof(X)))
      { X.show_winners(i++);
      }
      fin.close();
    }
    if(i==1)
    {   cout<<"\nNOTHING TO DISPLAY";
    }


   getch();
}
int administrator::show_post_list()
{  post X;
   int i=1,count=0;
   ifstream fin("PostCandidates.DAT",ios::binary);
   clrscr();
   print_border();
   int x=10,y=2;

   while(fin.read((char*)&X,sizeof(X)))
   {
      count++;
      gotoxy(x,y);
      if(y==18)
      {  y=2;
	 x=18;
      }

      y+=2;
       cout<<i++<<"."<<X.get_post_name();
       cout<<endl;
   }
   fin.close();
   return count;
}
void administrator::edit_candidate_list()
{  post X;
   char str[30];
   int i=0,pos;
   fstream finout;

   do
   { finout.open("PostCandidates.DAT",ios::binary|ios::in|ios::out);
     finout.seekg(0);
     finout.seekp(0);
   textcolor(WHITE);
   clrscr();
   print_border();
   gotoxy(28,6);
   cout<<"1.Edit Post Name";
    gotoxy(28,8);
   cout<<"2.Edit Candidate Name";
    gotoxy(28,10);
   cout<<"3.Add Candidates to a Post";
    gotoxy(28,12);
   cout<<"4.Remove Post";
    gotoxy(28,14);
   cout<<"5.Remove Candidates";
    gotoxy(28,16);
   cout<<"6.Go Back";
    gotoxy(23,18);
   cout<<"ENTER YOUR CHOICE ::: ";
   cin>>ch;
   switch(ch)
   {  case  1 :  clrscr();
		 print_border();
	      if(show_post_list()!=0)
	      { gotoxy(16,20);
		cout<<"ENTER POST NUMBER WHOSE NAME IS TO BE CHANGED ::: ";
		cin>>temp;
		if(temp>total_post || temp<=0)
		{ gotoxy(28,22);
		  textcolor(RED+BLINK);
		  cprintf("INVALID POST NUMBER");
		}
		else
		{ while(i<temp)
		  { pos=finout.tellg();
		    finout.read((char*)&X,sizeof(X));
		    i++;
		  }

		  X.modify_name();
		  finout.seekp(pos);
		  finout.write((char*)&X,sizeof(X));
		  gotoxy(25,24);
		  cout<<"POST NAME SUCCESSFULLY MODIFIED !!!";

		}
	      }
	      else
	      { gotoxy(23,12);
		cout<<"NO POSTS WERE FOUND IN THE FILE !!!";
	      }

	      break;
      case 2: clrscr();
	      print_border();
	      if(show_post_list()!=0)
	      {  gotoxy(16,20);
		 cout<<"ENTER POST NUMBER WHERE NAME IS TO BE CHANGED ::: ";
		 cin>>temp;
		 if(temp>total_post || temp<=0)
		 { gotoxy(28,22);
		   textcolor(RED+BLINK);
		   cprintf("INVALID POST NUMBER");
		 }
		 else
		 {
		      while(i<temp)
		      { pos=finout.tellg();
			finout.read((char*)&X,sizeof(X));
			i++;
		      }
		      temp=X.modify_candidate_name();
		      if(temp==1)
		      {  finout.seekp(pos);
			 finout.write((char*)&X,sizeof(X));
			 gotoxy(24,24);
			 cout<<"MODIFIED SUCCESSFULLY !!";
		      }

		 }
	       }
	       else
	       {  gotoxy(23,12);
		cout<<"NO POSTS WERE FOUND IN THE FILE !!!";
	       }
	      break;
      case 3 : clrscr();
	       print_border();
	       if(show_post_list()!=0)
	       {  gotoxy(16,20);
		 cout<<"ENTER POST NUMBER TO ADD NAMES TO IT ::: ";
		 cin>>temp;
	      if(temp>total_post || temp<=0)
	      {    gotoxy(28,22);
		   textcolor(RED+BLINK);
		   cprintf("INVALID POST NUMBER");
	      }
	      else
	      {

		while(i<temp)
		{ pos=finout.tellg();
		  finout.read((char*)&X,sizeof(X));
		  i++;
		}
		temp=X.add_candidates();
		if(temp==1)
		{ finout.seekp(pos);
		  finout.write((char*)&X,sizeof(X));
		  gotoxy(24,24);
		  cout<<"CANDIDATES ADDED SUCCESSFULLY !!!";
		}
	       }
	       }
	       else

	       {
		      gotoxy(23,12);
		      cout<<"NO POSTS WERE FOUND IN THE FILE";
	       }
	       break;
      case 4:  clrscr();
	       print_border();
	      if(show_post_list()!=0)
	      { ofstream fout("TEMP_FILE.DAT",ios::binary);
		gotoxy(16,20);
		cout<<"ENTER POST NUMBER WHICH IS TO BE DELETED ::: ";
		cin>>temp;
		if(temp>total_post || temp<=0)
		{  gotoxy(28,22);
		   textcolor(RED+BLINK);
		   cprintf("INVALID POST NUMBER");
		}
		else
		{

		  while(i<temp-1)
		  { finout.read((char*)&X,sizeof(X));
		    fout.write((char*)&X,sizeof(X));
		    i++;
		  }
		  finout.read((char*)&X,sizeof(X));
		  while(finout.read((char*)&X,sizeof(X)))
		  {  fout.write((char*)&X,sizeof(X));

		  }
		  finout.close();
		  fout.close();
		  remove("PostCandidates.DAT");
		  rename("TEMP_FILE.DAT","PostCandidates.DAT");
		  set_total_posts();
		  gotoxy(17,23);
		  cout<<"                                                    ";
		  gotoxy(23,23);
		  cout<<"DELETED SUCCESSFULLY!!";
		}
	      }
	      else
	      {  gotoxy(23,12);
		cout<<"NO POSTS WERE FOUND IN THE FILE!!!";

	      }
	     break;
      case 5:  clrscr();
	       print_border();
	      if(show_post_list()!=0)
	      { gotoxy(16,20);
		cout<<"ENTER POST NUMBER WHICH IS TO BE DELETED ::: ";
		cin>>temp;
		if(temp>total_post || temp<=0)
		{  gotoxy(28,22);
		   textcolor(RED+BLINK);
		   cprintf("INVALID POST NUMBER");
		}
		else
		{
			while(i<temp)
			{ pos=finout.tellg();
			  finout.read((char*)&X,sizeof(X));
			  i++;
			}
			temp=X.delete_candidates();
			if(temp==1)
			{ finout.seekp(pos);
			  finout.write((char*)&X,sizeof(X));
			  gotoxy(15,23);
			  cout<<"                                                    ";
			  gotoxy(20,23);
			  cout<<"CANDIDATE(S) REMOVED SUCCESSFULLY!!!";
			}
		 }
	      }
	      else
	      { gotoxy(23,12);
		cout<<"NO POSTS WERE FOUND IN THE FILE !!!";
	      }
	     break;
      case 6: return;
	      break;
       default : cout<<"\nWrong Choice !!!";

   }
   finout.close();
   getch();
  }while(1);

}
void administrator::vote()
{  clrscr();

   temp=show_post_list();
   gotoxy(2,1);
   for(int i=1;i<79;i++)
   {  cout<<" ";
   }
   gotoxy(2,25);
   for(i=1;i<79;i++)
   {  cout<<" ";
   }

   gotoxy(17,1);
   cout<<"YOU WILL HAVE TO VOTE FOR FOLLOWING POSTS";
   post X;
   int pos;
  if(temp>0)
  { gotoxy(22,2*(temp+1));
    cout<<"Press Any Key To Continue. . . . .";
    getch();
    clrscr();
    print_border();
    ifstream finout("PostCandidates.DAT",ios::binary|ios::in|ios::out);
    ofstream fout("PC.DAT",ios::binary);
    while(finout.read((char*)&X,sizeof(X)))
    { gotoxy(18,4);
      cout<<"VOTE FOR THE POST "<<X.get_post_name();
      X.vote();
      fout.write((char*)&X,sizeof(X));
      clrscr();
      print_border();
    }
    fout.close();
    finout.close();
    remove("PostCandidates.DAT");
    rename("PC.DAT","PostCandidates.DAT");
    gotoxy(17,12);
    cout<<"YOU HAVE SUCCESSFULLY VOTED FOR ALL THE POSTS !!!";
  }
  else
  {  gotoxy(23,12);
     cout<<"SORRY!! No Posts Exist to Vote for";
  }
  gotoxy(25,14);
  cout<<"Press Any Key To Continue. . . . .";
   getch();

}

void update_file(administrator A)
{
   administrator X;
 //ALSO MODIFY PASSWORD IN ADMINLIST.DAT
    fstream finout("ADMINLIST.DAT",ios::binary|ios::in|ios::out|ios::nocreate);
    while(finout.read((char*)&X,sizeof(X)))
    { if(X.match(A.get_username())==1)
      { finout.seekp(-1*(int)sizeof(X),ios::cur);
	finout.write((char*)&A,sizeof(A));
      }
    }


}
int login(administrator & A)
{  char unm[30],pass[30];
   administrator x;
   char chrs;
   int k=0;
   textcolor(LIGHTGREEN);
   clrscr();
   print_border();
   gotoxy(30,8);
   cout<<"ENTER USERNAME ::: ";
   gets(unm);
   gotoxy(30,10);
   cout<<"ENTER PASSWORD ::: ";
   chrs=getch();
   while(chrs!='\r')
   {
     if(isalnum(chrs) || chrs=='_' || chrs=='@')
     {  cout<<"*";
	pass[k++]=chrs;
     }
     chrs=getch();
   }
   pass[k]='\0';

   temp=0;
   ifstream fin("ADMINLIST.DAT",ios::binary);
   fin.seekg(0);
   while(fin.read((char*)&x,sizeof(x)))
   {   if(x.match(unm,pass)==1)
       {  A=x;
	  temp=1;
       }

   }
   fin.close();
   A.set_total_posts();
   if(temp==1)
   {   return 1;
   }
   else
   { return 0;
   }
}
int add_admin(administrator X)
{ ofstream fout("ADMINLIST.DAT",ios::binary|ios::app);
   if(!fout)

  {  gotoxy(17,16);
     cout<<"ERROR OPENING FILE!!!";
     fout.close();
     return -1;
  }
  else
  {    fout.write((char*)&X,sizeof(X));
       fout.close();
	return 1;
  }


}

void admin_proceed(administrator A)
{  clrscr();
   char choice;
   administrator X;
   do
   { textcolor(WHITE);
    clrscr();
   print_border();
   gotoxy(28,4);
   cout<<"1.ADD ADMINISTRATOR";
   gotoxy(28,6);
   cout<<"2.CHANGE PASSWORD";
   gotoxy(28,8);
   cout<<"3.NEW CANDIDATE LIST";
   gotoxy(28,10);
   cout<<"4.EDIT CANDIDATE LIST";
   gotoxy(28,12);
   cout<<"5.SHOW RESULTS";
   gotoxy(28,14);
   cout<<"6.RESET CANDIDATE LIST";
   gotoxy(28,16);
   cout<<"7.LOGOUT";
   gotoxy(28,18);
   cout<<"8.EXIT";
   gotoxy(24,20);
   cout<<"ENTER YOUR CHOICE ::: ";
   cin>>ch;
   switch(ch)
   {  case 1:   clrscr();
		print_border();
		X.get_data();
	      temp=add_admin(X);
	      if(temp!=1)
	      {   textcolor(RED);
		  clrscr();
		  print_border();
		  gotoxy(20,12);
		  cout<<"COULDN'T ADD ADMINISTRATOR ::: ";
	      }
	      else
	      {   gotoxy(25,16);
		  cout<<"ADMINISTRATOR SUCCESSFULLY ADDED";
	      }
	      getch();
	      break;

      case 2 :  clrscr();
		print_border();
	     temp=A.modify_pass();
	       if(temp==1)
	       { gotoxy(25,18);
		 update_file(A);
		 cout<<"PASSWORD SUCCESSFULLY CHANGED";
	       }
	       getch();
	      break;
      case 3 : A.new_candidate_list();
	       break;
      case 4 : A.edit_candidate_list();
	       break;
      case 5 : A.show_results();
	       break;

      case 6 : gotoxy(14,22);
	      cout<<"Are you sure you want to RESET LIST OF CANDIDATES(Y/N)?";
	       cin>>choice;
	       if(choice=='y' || choice=='Y')
	       { remove("PostCandidates.DAT");
		 ofstream fin("PostCandidates.DAT",ios::binary);
		 fin.close();
		 cout<<" RESET SUCCESSFUL";
	       }
	       break;
      case 7 :  gotoxy(17,22);
	       cout<<"ARE YOU SURE YOU WANT TO LOGOUT(Y/N) ? ::: ";
	       cin>>choice;
	       if(choice=='y' || choice=='Y')
	       {
			return;

	       }
	       break;
      case 8 : gotoxy(17,22);
	       cout<<"ARE YOU SURE YOU WANT TO EXIT(Y/N) ? ::: ";
	       cin>>choice;
	       if(choice=='y' || choice=='Y')
	       {
			exit(0);
	       }
	       break;
      default :  gotoxy(17,22);
	       textcolor(RED+BLINK);
	      cprintf("OOOPS!!THAT WAS A WRONG CHOICE!!!!");
	     getch();

   }

  }while(1);
}

void main()
{ char c;
  do{
   textcolor(WHITE);
   clrscr();
   print_border();
   gotoxy(30,8);
   cout<<"SELECT USER CATEGORY";
   gotoxy(25,10);
   cout<<"1.ADMINISTRATOR";
   gotoxy(25,12);
   cout<<"2.VOTER";
   gotoxy(25,14);
   cout<<"3.QUIT";
   gotoxy(25,16);
   cout<<"ENTER YOUR CHOICE ::: ";

   cin>>ch;
   switch(ch)
   {  case 1:   clrscr();
		administrator A;
		temp=login(A);
		if(temp==0)
		{  textcolor(RED);
		   clrscr();
		   print_border();
		   gotoxy(35,12);
		   cout<<"LOGIN FAILED !!!";
		   getch();
		}
		else
		{  admin_proceed(A);
		}
	       break;
      case 2: // A voter can vote through ADMINISTRATOR ONLY
	      administrator().vote();
	      break;

      case 3: gotoxy(20,18);
	      cout<<"Are you sure you want to quit(Y/N) ? ::: ";
	      cin>>c;
	      if(c=='y' || c=='Y')
	      {  exit(0);
	      }
	       break;
      default :gotoxy(20,18);
	       textcolor(RED+BLINK);
       cprintf("OOPS!!THAT WAS A WRONG CHOICE !!!");
	     getch();
   }

  }while(1);

}


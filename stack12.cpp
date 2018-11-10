//Ryan Jaipersaud
//DSA1
// The following will read in commands from a txt file that
// will create, push, pop values from stacks or queues
// the values that can be pushed or popped are ints, strings, doubles
// this code uses a doubly linked list
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <list>

using namespace std;

//input and output file objects
ifstream infile;
ofstream outfile;

//This is my base class
//This class contains doubly linked list functionality
template <class T>
class SimpleList 
{
	
protected: 
	struct node{
	T data;   
	node *next; // node pointer this is able to point to another node
	node *prev; // node pointer for the previous node
	};


	node *n;
	node *t; // temporary node
	node *h; // node for the head or first node
    string sname; // this will hold the name of the list


	public:

		T input;
		
		
			SimpleList()
			{
				n = new node; // n will point to a new node
				n->prev = NULL; // the previous node of the first node is set to NULL
				t = n; 
				h = n;
				n->next=NULL; // the "next" field will point to NULL
			}
			
			virtual void push(T x) // this should push something anywhere
			{
				
				n = new node; // n will point to a new node
				n -> data = x; // The x value will go into the data section of the new node
				n->prev = t; // the prev pointer of n will point back to t
				t -> next = n; // the next pointer of t (the previous node) will point to n
				t = n; // this will move t forward to n
				n->next=NULL;

				
			}
			virtual void pop()// this should pop something from anywhere 
			{ // a dervied class will over write this later
				outfile<<"HELP HELP";
			}

			string name() // function to return the name of the list stored in sname
			{
				return sname;
			}	

};

//Stack will inherit from SimpleList
template <class T> class Stack: public SimpleList<T> 
{
	
public:
	
		Stack(string x){ // constructor

			this->sname = x;
		}

		void pop(){
			if(this->t->prev == NULL)
			{
				outfile<<"ERROR: This list is empty!"<<endl;
				}

			else{
			
			outfile<<"Value popped: "<< this-> t->data<<endl;
				this-> t= this->t->prev; // t will now be set back to what the prev pointer of the current t equals
			}
		}
};

//Quene will inherit from SimpleList
template <class T>
class Quene: public SimpleList<T>
{
public:
		Quene(string x){
			this->sname = x;
		}
		void pop(){
			if(this->h->next == NULL)
			{
				outfile<<"ERROR: This list is empty!"<<endl;
			}
			else{
				this->h= this->h->next;
			outfile<<"Value popped: "<< this->h->data<<endl;
				
			}
		}
};

//global variables 
list<SimpleList<int> *> listSLi; // linked list of pointer to simple lists of ints 
SimpleList<int> *pSLi;          

list<SimpleList<string> *> listSLs; // linked list of pointers to strings
SimpleList<string> *pSLs;

list<SimpleList<double> *> listSLd; // linked list of pointers to doubles
SimpleList<double> *pSLd;



//protypes for functions
void create(char, string, string);
void MAINPUSH(char,string, string);
void MAINPOP(string);

//The main function will ask for input/output files
//It will also read in the commands of the input file word by word
int main()
{
	
	string word1, word2, word3;
	char c;
	string  input, output;
	
	cout<<"Enter the input file: "<<endl;
	cin>>input;
	cout<<"Enter the output file: "<<endl;
	cin>>output;

	infile.open(input.c_str()); // open file you want to read from
	outfile.open(output.c_str()); // open file you want to write to

	while(!infile.eof())
	{
	infile >> word1; // word1 is the command 
		if(word1 == "create")
			{
			infile >> word2 >> word3; //word2 is the name of list, word3 will be whether is it a stack or q
			outfile<<"PROCESSING COMMAND: "<<word1<<" "<<word2<<" "<<word3<<endl;
			create(word2[0],word2, word3);
			}
		if(word1 == "push")
			{
			infile >> word2>> word3; // word3 will be the value being pushed
			outfile<<"PROCESSING COMMAND: "<<word1<<" "<<word2<<" "<<word3<<endl;
			MAINPUSH(word2[0],word2, word3);
			}
		if(word1 == "pop")
			{
			infile >> word2 ;
			outfile<<"PROCESSING COMMAND: "<<word1<<" "<<word2<<endl;
			MAINPOP(word2);
			word3 = "";
			}

	}
  // close the files
  infile.close();
  outfile.close();
  return 0;
}


// This function will create as many stacks and queues as needed
// It will check if the list already exist and if it does not it will 
// create that specific type
void create(char type, string listname, string LIST)
{   
    int on = 1; // this will act like a switch if on =1 the switch is on, if on = 0 the switch is off

		if (type == 'i')
			{

			//This for loop will loop through the list of pointers to ints to check for the name of a stack/queue
			for ( list<SimpleList<int>*>::iterator il = listSLi.begin(); il!= listSLi.end(); il++) // for loop to cycle though everypoint in the SimpleList of int
				{
				if ((*il)-> name() == listname)
					{
					outfile<<"ERROR: This name already exists!"<<endl;
					on = 0;//the switch is off when on is set to 0
					}
				}
			if (on == 1)
				{
					if (LIST =="stack")
						{
						pSLi = new Stack<int>(listname); // set the pointer to a stack located in the heap
						listSLi.push_front(pSLi);
						}

					if (LIST =="queue")
						{
						pSLi = new Quene<int>(listname);
						listSLi.push_front(pSLi);
						}
				}
			}

		if (type == 's')
			{
			for ( list<SimpleList<string>*>::iterator il = listSLs.begin(); il!= listSLs.end(); il++)
				{
				if ((*il)-> name() == listname)
					{
					outfile<<"ERROR: This name already exists!"<<endl;
					on = 0;
					}
				}

			if(on == 1)
				{
					if (LIST =="stack")
						{
						pSLs = new Stack<string>(listname); 
						listSLs.push_front(pSLs);
						}

					if (LIST =="queue")
						{
						pSLs = new Quene<string>(listname); 
						listSLs.push_front(pSLs);
						}
				}
			}

		if (type == 'd')
			{
			for ( list<SimpleList<double>*>::iterator il = listSLd.begin(); il!= listSLd.end(); il++)
				{
				if ((*il)-> name() == listname)
					{
					outfile<<"ERROR: This name already exists!"<<endl;
					on = 0;
					}
				}

			if(on == 1)
				{
					if (LIST =="stack")
						{
						pSLd = new Stack<double>(listname); 
						listSLd.push_front(pSLd);
					}
					if (LIST =="queue")
						{
						pSLd = new Quene<double>(listname); 
						listSLd.push_front(pSLd);
					}
				}
			}
}

//This will push the value to the respective stack/queue
//store is the first character of the second word in a line
//EX: "push i55 50", store ="i", putoutme = "i55", HERE ="50"
void MAINPUSH(char store, string putoutme, string HERE){

	int i;
	string s;
	double d;
	int on = 1;
	if(store == 'i')
		{
		i = atoi(HERE.c_str()); // this converts the string passed into HERE into an int
		for ( list<SimpleList<int>*>::iterator il = listSLi.begin(); il!= listSLi.end(); il++)
			{
			if ((*il)-> name() == putoutme)
				{
				(*il) -> push(i);
				on = 0;
				}
			}
		}
	if(store == 's')
		{
		s = HERE;
		for ( list<SimpleList<string>*>::iterator il = listSLs.begin(); il!= listSLs.end(); il++)
			{
			if ((*il)-> name() == putoutme)
				{
				(*il) -> push(s);
				on = 0;
				}
			}
		}
	if(store == 'd')
		{
		d = atof(HERE.c_str());
		for ( list<SimpleList<double>*>::iterator il = listSLd.begin(); il!= listSLd.end(); il++)
			{
			if ((*il)-> name() == putoutme)
				{
					(*il) -> push(d);
					on = 0;
				}
			}
		}
	if(on==1){
			outfile<<"ERROR: This name does not exist!"<<endl;
		}
}

// this function will return the last valued entered if the list is a stack
// or the first value entered if the list is a q
void MAINPOP(string putoutme)
{
	int on = 1;
	for ( list<SimpleList<int> *>::iterator il = listSLi.begin(); il!= listSLi.end(); il++)
		{
		if ((*il)-> name() == putoutme)
			{
			(*il) -> pop();
			on = 0;
			}
		}
	for ( list<SimpleList<string> *>::iterator il = listSLs.begin(); il!= listSLs.end(); il++)
		{
		if ((*il)-> name() == putoutme)
			{
			(*il) -> pop();
			on = 0;
			}
		}
	for ( list<SimpleList<double> *>::iterator il = listSLd.begin(); il!= listSLd.end(); il++)
		{
		if ((*il)-> name() == putoutme)
			{
			(*il) -> pop();
			on = 0;
			}
		
		}
	if(on==1)
		{
		outfile<<"ERROR: This name does not exist!"<<endl;
		}
}
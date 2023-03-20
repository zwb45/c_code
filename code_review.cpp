#include<iostream>
#include<string.h>
#include<fstream>
#include<math.h>
#include<iomanip>

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


#define N 100000

#define HASHSIZE 35 
#define  Size    15

using namespace std;

int hash1[60],hash2[60];
double pos[2];


typedef unsigned int uint;
typedef struct Node{
	const char* key;
	const int *value;
	Node *next;
}Node;

class HashTable{
private:
    Node* node[HASHSIZE];
public:
	HashTable();
	~HashTable();
	int hash(const char* key);
	Node* lookup(const char* key);
	bool install(const char* key,const int* value);
	const char* get(const char* key);
	void display();
};

HashTable *ht = new HashTable();


HashTable::HashTable(){
	for (int i = 0; i < HASHSIZE; ++i)
	{
		node[i] = NULL;
	}
}
HashTable::~HashTable(){
	cout<<"bye";
}
int HashTable::hash(const char* key){

	return (int)((*key)-97);
}

Node* HashTable::lookup(const char* ch){
	Node *np;
	uint index;
	index = hash(ch);
	//np=node[index];
	for(np=node[index];np;np=np->next){
		if(!strcmp(ch,np->key))
			return np;
}
	
	return NULL;
}

bool HashTable::install(const char* key,const int* value){
	uint index;
	Node *np;
	if(!(np=lookup(key))){
		index = hash(key);
		np = (Node*)malloc(sizeof(Node));
		if(!np) return false;
		np->key=key;
		np->next = node[index];
		node[index] = np;
	}
	np->value=value;
	return true;
}

void HashTable::display(){
	Node* temp;
	for (int i = 0; i < HASHSIZE; ++i)
	{
		if(!node[i]){
			printf("%d\n",i);
		}
		else 
		{
			printf("");
			for (temp=node[i]; temp; temp=temp->next)
			{
				cout<<i<<setw(50)<<temp->key<<endl; 
			}
		
		}
	}
}
	
static void judege_c(int hash[],const char* ch) {
      Node  *np;
      int x;
      x=ht->hash(ch);
      	if(x>=0&&x<=25)
	{
      np=ht->lookup(ch);

      if(np!=NULL)
	  if(!strcmp(ch,np->key))
	     {hash[*(np->value)]++;
		 
		 } 
    }
}
	
static int deal_data1(char data[]) {
    char ch;
    char filename[50];
    cout<<"the first file:"<<endl;
    cin>>filename;
    ifstream infile(filename,ios::in);
    ofstream outfile("dealt_data1.txt",ios::out);
    if(!infile) {
        cout<<"Open first file error!"<<endl;
        exit(0);
	}
    if(!outfile) {
        cout<<"Open dealt_data1 error!"<<endl;
        exit(0);
	}
    
    while(infile.get(ch)) {
        if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'||ch==','||ch=='<'||ch=='>'||ch==';')
            ch=' ';
        outfile.put(ch);
    }
    infile.close();
    outfile.close();
    ifstream infile1("dealt_data1.txt",ios::in);
    if(!infile1) {
        cout<<"open dealt_data1 error!"<<endl;
    }
    int cnt=0;
    while(infile1.get(ch)) {
        data[cnt++]=ch;
    }
    infile1.close();
    return cnt;
}

static int deal_data2(char data[]) {
    char ch;
    char filename[50];
    cout<<"the second file:"<<endl;
    cin>>filename;
    ifstream infile(filename,ios::in);
    ofstream outfile("dealt_data2.txt",ios::out);
    if(!infile) {
        cout<<"Open second file error!"<<endl;
        exit(0);
	}
    if(!outfile) {
        cout<<"Open dealt_data2 error!"<<endl;
        exit(0);
	}
    while(infile.get(ch)) {
        if(ch=='('||ch==')'||ch=='{'||ch=='}'||ch=='['||ch==']'||ch==','||ch=='<'||ch=='>'||ch==';')
            ch=' ';
        outfile.put(ch);
    }
    infile.close();
    outfile.close();
    ifstream infile2("dealt_data2.txt",ios::in);
    if(!infile2) {
        cout<<"open dealt_data2 error!"<<endl;
    }
    int cnt=0;
    while(infile2.get(ch)) {
        data[cnt++]=ch;
    }
    infile2.close();
    return cnt;
}

static void calcunum_c(const char data[],const int n,const int num) {
    char ch[100];
    int i,j,x;
    for(i=0; i<n; i++) {
        if(data[i]!=' '&&data[i]!='\n'&&data[i]!='\t') {
            j=0;
            while(data[i]!=' '&&data[i]!='\n'&&data[i]!='\t') {
                ch[j]=data[i];
                i++;
                j++;
            }
            ch[j]='\0';
            if(num==1)
            {
				judege_c(hash1,ch);
			}
            else
            {             
			    judege_c(hash2,ch);
			}
        }
    }
}

void possibality(int hash1[],int hash2[])
{
    int i;
    double sum=0,sum1=0,sum2=0,sum3=0,pos1,pos2;
    for(i=0;i<Size;i++)
    {
        sum=sum+hash1[i]*hash2[i];
        sum1=sum1+hash1[i]*hash1[i];
        sum2=sum2+hash2[i]*hash2[i];
        sum3=sum3+(hash1[i]-hash2[i])*(hash1[i]-hash2[i]);
    }
    pos1=sqrt(sum1);
    pos2=sqrt(sum2);
    pos[0]=sum/(pos1*pos2);
    pos[1]=sqrt(sum3);
}


int main(void)
{

	const char* key[]={"void","int","for","char","if","else","while","return",
	                    "double","float","static","const","do","sizeof","struct"
	                  };
	const int value[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	cout<<"the list of hash:    "<<endl<<endl<<endl;
	for (int i = 0; i < Size; ++i)
	{
		ht->install(key[i],&value[i]);
	}
	ht->display();
	
	char data1[N];
    char data2[N];
    const int cnt1 = deal_data1(data1);
    const int cnt2 = deal_data2(data2);
   
    calcunum_c(data1,cnt1,1);
    calcunum_c(data2,cnt2,2);


	cout<<"the number of key of first file:"<<endl;
    for(int i=0; i<Size; i++){
        cout<<setw(10)<<key[i]<<":"<<hash1[i+1];
        if((i+1)%5==0)
            cout<<endl;
    }
    cout<<endl;
    cout<<"the number of key of second file:"<<endl;
    for(int i=0; i<Size; i++){
        cout<<setw(10)<<key[i]<<":"<<hash2[i+1];
        if((i+1)%5==0)
            cout<<endl;
    }
	cout<<endl;cout<<endl;cout<<endl;
	possibality(hash1,hash2);
	cout<<"the Cosine: "<<pos[0]<<endl<<"the Distance: "<<pos[1]<<endl;
	delete ht;
	return 0;
}

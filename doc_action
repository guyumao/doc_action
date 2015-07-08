#include<iostream>
#include<fstream>
#include<pthread.h>
#include<unistd.h>
#include<map>
#include<iomanip>
#include<string>
using namespace std;
#define NUM 8
fstream in;
typedef multimap<string,string> MAP;
MAP record;
MAP::iterator it;
pthread_mutex_t reading_mutex,record_mutex;
int analysis(string filename)
{	
	fstream file;
	char buf[256];
	string::size_type position,first,last,check;
	file.open(filename.c_str(),ios::in);
	if(file.good())
	{
		while(!file.eof())
		{	
			file.getline(buf,256,'\n');
			string s(buf);
			position=s.find("#include");
			if(position!=s.npos)
			{	
				if((check=s.find("\""))!=s.npos)
				{
					first=s.find("\"");
					last=s.rfind("\"");
					s=s.substr(first+1,last-first-1);
				}
				else
				{
					first=s.find("<");
					last=s.find(">");
					s=s.substr(first+1,last-first-1);
				}
				pthread_mutex_lock(&record_mutex);
				record.insert(make_pair(s,filename));
				pthread_mutex_unlock(&record_mutex);
			}
		}
	}
	else
		cout<<"open failed"<<endl;
	file.close();
}	
void* read(void* args)
{
	char buffer[256];
	pthread_mutex_lock(&reading_mutex);
	in.getline(buffer,256,'\n');
	string FILENAME(buffer);
	//cout<<FILENAME<<endl;
	analysis(FILENAME);
	//cout<<"reading"<<buffer<<endl;
	pthread_mutex_unlock(&reading_mutex);
}
int main()
{	
	int i=0;
	in.open("in.txt",ios::in);
	pthread_t tids[NUM];
	pthread_mutex_init(&reading_mutex,NULL);
	pthread_mutex_init(&record_mutex,NULL); 
	while(!in.eof())
	{
		for(int i=0;i<NUM;i++)
		{
			int ret=pthread_create(&tids[i],NULL,read,NULL);
			if(ret!=0)
				cout<<"pthread_create error: error_code="<<ret<<endl;
		}
		for(int i=0;i<NUM;i++)
    		{  
                	int ret=pthread_join(tids[i],NULL);  
        		if (ret!=0)   
            			cout<<"pthread_join error: error_code="<<ret<<endl;
		}
	}
	in.close();	
    	pthread_mutex_destroy(&record_mutex);
    	pthread_mutex_destroy(&reading_mutex);
	for(it=record.begin();it!=record.end();it++)
	{
		cout<<it->first<<"\t"<<it->second<<endl;
	}
}


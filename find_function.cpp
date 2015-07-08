#include<iostream>
#include<fstream>
#include<map>
#include<string>
using namespace std;
typedef multimap<string,string> MAP;
MAP func;
MAP::iterator it;
fstream in;
string filename="/usr/include/unistd.h";
string::size_type pos,first,last;
int main()
{	
	in.open(filename.c_str(),ios::in);
	while(!in.eof())
	{
		char buffer[256];
		string buf;
		int flag;
		while(flag && !in.eof())
		{
			in.getline(buffer,256,'\n');
			string s(buffer);
			if((pos=s.find(";"))!=s.npos)
				flag=0;
			else if(((pos=s.find("*/"))!=s.npos)||(pos=s.find("/*")!=s.npos))
				buf="";
			else
				buf+=s;
		}
		flag=1;
		if(buf!="")
		{
			if((pos=buf.find("(",0))!=buf.npos)
			{
				last=buf.rfind(' ',pos);
				first=buf.rfind(' ',last);
				buf=buf.substr(first+1,last-first-1);
			}
			else
				buf="";
		}
		if(buf!="")
			cout<<buf<<endl;
	}
	return 0;
}	

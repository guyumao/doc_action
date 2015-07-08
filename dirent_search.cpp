#include<iostream>
#include<string>
#include<dirent.h>
#include<fstream>
using namespace std;
int function(string dirname)
{
	ofstream in;
	in.open("in.txt",ios::app);
	DIR *dp;
	struct dirent *dirp;
	if((dp=opendir(dirname.c_str()))==NULL)
		cout<<"Can't open"<<dirname<<endl;
	while((dirp=readdir(dp))!=NULL)
	{
		if(dirp->d_type==8)
			in<<dirname+'/'+dirp->d_name<<endl;
	}
	in.close();
	return 0;
}
int main()
{
	function("/home/rtai/ros_catkin_ws/src/ros_comm/roscpp/include/ros");
	function("/home/rtai/ros_catkin_ws/src/ros_comm/roscpp/include/ros/transport");
	return 0;
}

	

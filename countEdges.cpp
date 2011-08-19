#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main(int argc,char**argv){
	map<string,vector<string> > links;
	string c1;
	char s1;
	string c2;
	char s2;
	int gap;

	string file=argv[1];

	ifstream f(file.c_str());
	while(!f.eof()){
		gap=-1;
		f>>c1>>s1>>c2>>s2>>gap;
		if(gap==-1)
			continue;
		links[c1].push_back(c2);
		links[c2].push_back(c1);
	}

	f.close();
	
	map<int,int> distribution;

	for(map<string,vector<string> >::iterator i=links.begin();i!=links.end();i++)
		distribution[i->second.size()]++;

	cout<<"Edges	Count"<<endl;
	for(map<int,int>::iterator i=distribution.begin();i!=distribution.end();i++)
		cout<<i->first<<"	"<<i->second<<endl;


	return 0;
}

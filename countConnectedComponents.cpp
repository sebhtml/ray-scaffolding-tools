#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

bool assignColor(string*element,int color,map<string,vector<string> >*links,map<string,int>*colors){
	if(colors->count(*element)>0)
		return false;

	(*colors)[*element]=color;
	for(vector<string>::iterator i=(*links)[*element].begin();i!=(*links)[*element].end();i++){
		string child=*i;
		assignColor(&child,color,links,colors);
	}
	return true;
}

// contig-3        R       contig-80       R       156
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
	
	map<string,int> colors;

	int currentColor=0;

	for(map<string,vector<string> >::iterator i=links.begin();i!=links.end();i++){
		string element=i->first;
		if(assignColor(&element,currentColor,&links,&colors))
			currentColor++;
	}

	cout<<"Colors assigned: "<<currentColor<<endl;

	return 0;
}

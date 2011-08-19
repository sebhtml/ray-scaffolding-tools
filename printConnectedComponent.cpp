#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int assignColor(string*element,int color,map<string,vector<string> >*links,map<string,int>*colors){
	if(colors->count(*element)>0)
		return 0;

	int colored=1;
	(*colors)[*element]=color;
	for(vector<string>::iterator i=(*links)[*element].begin();i!=(*links)[*element].end();i++){
		string child=*i;
		colored+=assignColor(&child,color,links,colors);
	}
	return colored;
}

// contig-3        R       contig-80       R       156
int main(int argc,char**argv){
	map<string,vector<string> > links;
	string c1;
	char s1;
	string c2;
	char s2;
	int gap;

	// arguments: ScaffoldLinks   contigName

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
		int colored=assignColor(&element,currentColor,&links,&colors);
		if(colored>0){
			cout<<"colored "<<colored<<" with color "<<currentColor<<endl;
			currentColor++;
		}
	}

	string selected=argv[2];

	cout<<"Assigned colors: "<<currentColor<<endl;

	if(colors.count(selected)==0)
		cout<<"Error, not found"<<endl;

	cout<<"Element: "<<selected<<" assigned color: "<<colors[selected]<<endl;

	int selectedColor=colors[selected];

	{
	ifstream f(file.c_str());
	while(!f.eof()){
		gap=-1;
		f>>c1>>s1>>c2>>s2>>gap;
		if(gap==-1)
			continue;
		if(colors[c1]==selectedColor|| colors[c2]==selectedColor)
			cout<<c1<<" -- "<<c2<<endl;
	}

	f.close();
	}

	return 0;
}

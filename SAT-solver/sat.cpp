#include <iostream>
#include <string>
#include <regex>
#include <set>
#include <map>
#include <cmath>
#include <bitset>
using namespace std;
int main (int argc, char** argv)
{
    string s = argv[1];
	smatch m;
	regex letter ("([a-zA-Z])");
	regex all_decision ("(\\|\\w{2})|(\\&\\w{2})|(\\!\\w)");
	regex all_match (".*(\\|\\w{2}).*|.*(\\&\\w{2}).*|.*(\\!\\w).*");
	string::const_iterator start = s.begin();
	string::const_iterator end = s.end();
	string tmp;
	set<char>setAlphabet;
	map<char,int>mapAlphabet;
	map<char, int>::iterator iter;
	mapAlphabet.insert(pair<char, int>('1', 1));
	mapAlphabet.insert(pair<char, int>('0', 0));
	while(regex_search (start, end, m, letter)){//use regular expression iterator search to get all |xy
		tmp = m[0];
		//cout<<tmp<<endl;
		setAlphabet.insert(tmp[0]);//get all occurred letters  
        start = m[0].second;
	}
	

	const int n = setAlphabet.size();//number of occurred letters
	
	set<char>::iterator it;           
	for(int c = 0; c<pow(2, n);++c){
		std::bitset<52> bitset(c);//generate bit values assigning to variables
		int i =0; 
		for(it=setAlphabet.begin();it!=setAlphabet.end();it++)  //assign values to each letter
		{	
			mapAlphabet[*it] = bitset[i];//to cover formal value
			i = i+1;
		}

		//in every round search and replace "|xy" with {0,1}, loop until s == "1" or "0"
		s = argv[1];//reset s 
		while(s!="0"&&s!="1"){
			start = s.begin();
			if (regex_match(s, all_match)){
				while(regex_search(start, end, m, all_decision)){
					tmp = m[0];
					if (tmp[0]=='|'){
						if(mapAlphabet[tmp[1]]||mapAlphabet[tmp[2]]){
							s.replace(m[0].second-3,m[0].second,"1");
						}
						else
						{
							s.replace(m[0].second-3,m[0].second,"0");
						}
						start = m[0].second-3;
					}
					else if (tmp[0]=='&'){
						if (mapAlphabet[tmp[1]]&&mapAlphabet[tmp[2]]){
							s.replace(m[0].second-3,m[0].second,"1");
						}
						else {
							s.replace(m[0].second-3,m[0].second,"0");
						}
						start = m[0].second-3;
					}
					else if (tmp[0]=='!'){
						if (mapAlphabet[tmp[1]]){
							s.replace(m[0].second-2,m[0].second,"0");	
						}
						else{
							s.replace(m[0].second-2,m[0].second,"1");
						}
						start = m[0].second-2;
					}
			
				}
				if (regex_match(s, all_match)||s== "0"||s=="1"){//invalid query handling
					continue;
				}
				else {
					cout<<"Invalid query!"<<endl;
					return 0;
				}

			}
			else {
				cout<<"Invalid query!"<<endl;
				return 0;
			}
		}
		if (s == "1"){//output satisfied result
			cout<<"The input SAT model is satisfiable!"<<endl<<"A satisfying model is:"<<endl;
			for (iter = std::next(mapAlphabet.begin(), 2); iter != mapAlphabet.end();iter++){
				//cout<<*iter;
				cout<<iter->first<<"="<<iter->second<<endl;
			}
			break;
		}
	}
	if (s=="0"){//output unsatisfied result
		cout<<"The input SAT model is unsatisfiable!"<<endl;
	}
	return 0;
}
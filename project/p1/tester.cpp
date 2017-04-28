#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string.h>
#include <windows.h>
#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

//#define DEVELOP

string& trim(string &str)   
{  
    if (str.empty())   
    {  
        return str;  
    }  
    str.erase(0, str.find_first_not_of(" "));  
    str.erase(str.find_last_not_of(" ") + 1);  
    return str;  
}

int main()
{
	cout<<"VE280 Tester 0.0.1 alpha"<<endl;
	string filename;
	ifstream input;
	do
	{
		cout<<"Please enter the project name: ";
		getline(cin, filename);
	}
	while(_access((".//"+filename+".test").c_str(),0)==-1);
	string testmenu=".//"+filename+".test//";
	system(("dir "+filename+".test /B >filelist.test").c_str());
	ifstream filelist("filelist.test");
	vector<string> testname;
	while(!filelist.eof())
	{
		string readStr;
		getline(filelist, readStr);
		size_t last=readStr.find_last_of('.');
		if(last==string::npos)
		{
			continue;
		}
		if(readStr.substr(last)!=".case")
		{
			continue;
		}
		testname.push_back(readStr.substr(0,last));
		//cout<<readStr.substr(0,last)<<endl;
	}
	filelist.close();
	system("del filelist.test");
	cout<<endl;
	ofstream log("test.log");
	int all=0,success=0;
	for(vector<string>::iterator it=testname.begin();it<testname.end();it++)
	{
		all++;
		string inputpath=testmenu+*it+".case";
		string outputpath=testmenu+*it+".result";
		string answerpath=testmenu+*it+".answer";
		#ifdef DEVELOP
		DWORD t1=GetTickCount();
		system((filename+" >"+answerpath+" <"+inputpath).c_str());
		DWORD t2=GetTickCount();
		cout<<"case"<<setw(6)<<*it<<" "<<setw(5)<<t2-t1<<" ms   ";
		log<<"case"<<setw(6)<<*it<<" "<<setw(5)<<t2-t1<<" ms   "<<endl;
		ifstream input(inputpath.c_str());
		log<<"input: "<<endl;
		if(!input.is_open()) 
		{
			cout<<"error";
			log<<"error: input not found! (Contact the test provider)"<<endl;
		}
		else
		{
			while(!input.eof())
			{
				string inputStr;
				getline(input, inputStr);
				if(!inputStr.empty()) log<<inputStr<<endl;
			}
			input.close();
			ifstream answer(answerpath.c_str());
			log<<"answer: "<<endl;
			if(!answer.is_open()) 
			{
				cout<<"error";
				log<<"error: answer not found!"<<endl<<endl; 
				continue;
			}
			else
			{
				while(!answer.eof())
				{
					string answerStr;
					getline(answer, answerStr);
					if(!answerStr.empty()) log<<answerStr<<endl;
				}
				answer.close();
				cout<<"success";
				log<<"success"<<endl;
				success++;
			}
		}
		cout<<endl;
		log<<endl;
		#else
		DWORD t1=GetTickCount();
		system((filename+" >"+outputpath+" <"+inputpath).c_str());
		DWORD t2=GetTickCount();
		cout<<"case"<<setw(6)<<*it<<" "<<setw(5)<<t2-t1<<" ms   ";
		log<<"case"<<setw(6)<<*it<<" "<<setw(5)<<t2-t1<<" ms   "<<endl;
		ifstream output(outputpath.c_str());
		if(!output.is_open()) 
		{
			cout<<"error"<<endl;
			log<<"error: output not found! (Examine your program)"<<endl<<endl; 
			continue;
		}
		ifstream answer(answerpath.c_str());
		if(!answer.is_open())
		{
			cout<<"error"<<endl;
			log<<"error: answer not found! (Contact the test provider)"<<endl<<endl;
			output.close();
			system(("del "+filename+".test\\"+*it+".result").c_str());
			continue;
		} 
		int line=1;
		bool error=false;
		while(!(output.eof()&&answer.eof()))
		{
			string outputStr, answerStr;
			while(!output.eof())
			{
				getline(output, outputStr);
				if(!trim(outputStr).empty()) break;
			}
			while(!answer.eof())
			{
				getline(answer, answerStr);
				if(!trim(answerStr).empty()) break;
			}
			if(outputStr!=answerStr)
			{
				if(!error)
				{
					error=true;
					ifstream input(inputpath.c_str());
					log<<"input: "<<endl;
					if(!input.is_open()) 
					{
						log<<"input not found! (Contact the test provider)"<<endl; 
					}
					else
					{
						while(!input.eof())
						{
							string inputStr;
							getline(input, inputStr);
							if(!inputStr.empty()) log<<inputStr<<endl;
						}
						input.close();
					}
				}
				log<<"line "<<line<<endl;
				log<<"output: "<<outputStr<<endl;
				log<<"answer: "<<answerStr<<endl;
			}
			line++;
		}
		if(t2-t1>=2000)
		{
			cout<<"time limit";
			log<<"time limit";
		} 
		else if(!error)
		{
			cout<<"success";
			log<<"success";
			success++;
		}
		else
		{
			cout<<"wrong answer";
			log<<"wrong answer";
		}
		cout<<endl;
		log<<endl<<endl;
		answer.close();
		output.close();
		system(("del "+filename+".test\\"+*it+".result").c_str());
		#endif
	}
	cout<<endl<<"Total: "<<success<<" / "<<all<<" "<<endl;
	log<<endl<<"Total: "<<success<<" / "<<all<<" "<<endl;
	if(success==all)
	{
		cout<<"Congratulations! You passed all the cases!"<<endl;
		log<<"Congratulations! You passed all the cases!"<<endl;
	}
	else
	{
		cout<<all-success<<" error(s) found. Check the file test.log!"<<endl;
	}
	log.close();
	system("pause"); 
	return 0;
}

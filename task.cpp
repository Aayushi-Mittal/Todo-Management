#include <bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

multimap<string, pair<string, bool>> tasks;

vector<vector<string>> split(string str)
{
    vector<vector<string>> res;
    vector<string> temp;
    string s="";
    for(int i=0; i<str.size(); i++)
    {
        if(str[i]=='\n')
        {
            temp.push_back(s);
            res.push_back(temp);
            s="";
            temp={};
        }
        else if(str[i]==';')
        {
            temp.push_back(s);
            s="";
        }
        else
            s+=str[i];
    }
    temp.push_back(s);
    res.push_back(temp);
    return res;
}

void printHelp()
{
    cout<<"Usage :-"<<endl;
    cout<<"$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list"<<endl;
    cout<<"$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order"<<endl;
    cout<<"$ ./task del INDEX            # Delete the incomplete item with the given index"<<endl;
    cout<<"$ ./task done INDEX           # Mark the incomplete item with the given index as complete"<<endl;
    cout<<"$ ./task help                 # Show usage"<<endl;
    cout<<"$ ./task report               # Statistics"<<endl;
}

void updateTask()
{
	ofstream task_file;
    task_file.open("task.txt");
    if(task_file) {
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
            task_file<<itr->first<<";"<<(itr->second).first<<";"<<(itr->second).second<<endl;
    }
    task_file.close();
}

void addTask(int argc, char* argv[])
{
    if(argc<4)
        cout<<"Error: Missing tasks string. Nothing added!";
    else
    {
        tasks.insert({argv[2], pair<string,bool>{argv[3], false}});
        updateTask();
    }
}

void lsTask()
{
    int i=0;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        cout<<i<<". "<<itr->first<<" ["<<(itr->second).first<<"]"<<endl;
        i++;
    }
}

void delTask(int argc, char* argv[])
{
    if(argc<3)
        cout<<"Error: Missing tasks string. Nothing added!";
    else
    {
        int i=1;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
        {
            if(to_string(i)==argv[2])
            {
                tasks.erase(itr);
                break;
            }
            i++;
        }
        updateTask();
    }
}

void doneTask(int argc, char* argv[])
{
    if(argc<3)
        cout<<"Error: Missing tasks string. Nothing added!";
    else
    {
        int i=1;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
        {
            if(to_string(i)==argv[2])
            {
                (itr->second).second="true";
                break;
            }
            i++;
        }
        updateTask();
    }
}

void report()
{
    cout<<"Pending :"<<endl;
    int i=0;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==true)
        {
            cout<<i<<". "<<itr->first<<" ["<<(itr->second).first<<"]"<<endl;
            i++;
        }
    }
    cout<<"Completed :"<<endl;
    i=0;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==false)
        {
            cout<<i<<". "<<itr->first<<" ["<<(itr->second).first<<"]"<<endl;
            i++;
        }
    }
}


int main(int argc, char* argv[])
{
    cout<<argc<<endl;
    for(int i=0; i<argc; i++)
        cout<<argv[i]<<"; ";

    string todo, priority, task;
    bool isDone;
    vector<vector<string>> todov;
	ifstream task_file("task.txt");
	// ofstream ofs;
 
    if(task_file) {
        ostringstream ss;
        ss << task_file.rdbuf(); // reading data
        todo = ss.str();
        cout<<"\n"<<todo<<"\n"<<endl;
        todov = split(todo);
        for(int i=0; i<todov.size(); i++)
        {
            priority=todov[i][0];
            task=todov[i][1];
            isDone=((todov[i][2]=="true") ? true : false);
            // cout<<"["<<priority<<"] "<<task<<" "<<isDone<<endl;
            tasks.insert({priority, pair<string,bool>{task, isDone}});
            cout<<endl;
        }
    }

    // for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    //     cout<<"["<<itr->first<<"] "<<(itr->second).first<<" "<<(itr->second).second<<endl;



    if(argv[1]=="help")
    {
        printHelp();
    }
    else if(argv[1]=="add")
    {
        addTask(argc, argv);
    }
    else if(argv[1]=="ls")
    {
        lsTask();
    }
    else if(argv[1]=="del")
    {
        delTask(argc, argv);
    }
    else if(argv[1]=="done")
    {
        doneTask(argc, argv);
    }
    else if(argv[1]=="report")
    {
        report();
    }
    else
    {
        cout<<"INVALID";
    }

    return 0;
}


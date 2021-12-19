#include <bits/stdc++.h>
#include<fstream>
#include<sstream>
using namespace std;

// Container of all the tasks with priority and status(isDone?).
multimap<int, pair<string, bool>> tasks;

// Function for splitting the contents of file into tasks multimap
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

void initializeTasks()
{
    string todo, task;
    int priority;
    bool isDone;
    vector<vector<string>> todov;
	ifstream task_file;
    task_file.open("task.txt");
    if(task_file) {
        ostringstream ss;
        ss << task_file.rdbuf();
        todo = ss.str();
        todov = split(todo);
        for(int i=0; i<todov.size(); i++)
        {
            priority=stoi(todov[i][0]);
            task=todov[i][1];
            isDone=((todov[i][2]=="1") ? true : false);
            tasks.insert({priority, pair<string,bool>{task, isDone}});
        }
    }
    task_file.close();
}

// -------------------------------- Functions for each case starts from here --------------------------------

void printHelp()
{
    string help="Usage :-\n$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list\n$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order\n$ ./task del INDEX            # Delete the incomplete item with the given index\n$ ./task done INDEX           # Mark the incomplete item with the given index as complete\n$ ./task help                 # Show usage\n$ ./task report               # Statistics";
    cout<<help<<endl;
}

void updateTask()
{
	ofstream task_file;
    task_file.open("task.txt");
    if(task_file) {
        int i=0, count=0;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
            count++;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
        {
            task_file<<itr->first<<";"<<(itr->second).first<<";"<<(itr->second).second;
            i++;
            if(i<count) task_file<<"\n";
        }
    }
    task_file.close();
}

void addTask(int argc, char* argv[])
{
    if(argc<4)
        cout<<"Error: Missing tasks string. Nothing added!";
    else
    {
        string todo="";
        for(int i=3; i<argc; i++)
            todo+=argv[i];
        tasks.insert({stoi(argv[2]), pair<string,bool>{todo, false}});
        updateTask();
        cout<<"Added task: \""<<todo<<"\" with priority "<<argv[2]<<endl;
    }
}

void lsTask()
{
    int i=1;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==false)
        {
            cout<<i<<". "<<(itr->second).first<<" ["<<itr->first<<"]"<<endl;
            i++;
        }
    }
    if(i==1) cout<<"There are no pending tasks!"<<endl;
}

void delTask(int argc, char* argv[])
{
    if(argc<3)
        cout<<"Error: Missing NUMBER for deleting tasks.";
    else
    {
        int i=1, notfound=1;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
        {
            if((itr->second).second==false)
            {
                if(to_string(i)==argv[2])
                {
                    tasks.erase(itr);
                    notfound=0;
                    break;
                }
                i++;
            }
        }
        if(notfound || i<1) cout<<"Error: task with index #"<<argv[2]<<" does not exist. Nothing deleted."<<endl;
        else {
            updateTask();
            cout<<"Deleted task #"<<i<<endl;
        }
    }
}

void doneTask(int argc, char* argv[])
{
    if(argc<3)
        cout<<"Error: Missing NUMBER for marking tasks as done.";
    else
    {
        int i=1, notfound=1;
        for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
        {
            if((itr->second).second==false)
            {
                if(to_string(i)==argv[2])
                {
                    (itr->second).second=true;
                    notfound=0;
                    break;
                }
                i++;
            }
        }
        if(notfound || i<1) cout<<"Error: no incomplete item with index #"<<argv[2]<<" exists."<<endl;
        else {
            updateTask();
            cout<<"Marked item as done."<<endl;
        }
    }
}

void report()
{
    int p=0, c=0;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==false) p++;
        else c++;
    }

    cout<<"Pending : "<<p<<endl;
    int i=1;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==false)
        {
            cout<<i<<". "<<(itr->second).first<<" ["<<itr->first<<"]"<<endl;
            i++;
        }
    }
    cout<<"\nCompleted : "<<c<<endl;
    i=1;
    for(auto itr=tasks.begin(); itr!=tasks.end(); itr++)
    {
        if((itr->second).second==true)
        {
            cout<<i<<". "<<(itr->second).first<<endl;
            i++;
        }
    }
}

// -------------------------------- Main Code starts from here --------------------------------

int main(int argc, char* argv[])
{
    //since strings and character array are not same.
    string cmd="";
    if(argc>1)
    {
        for(int k=0; argv[1][k]!='\0'; k++)
            cmd+=argv[1][k];
    }
    else
        cmd="help";

    initializeTasks();

    if(cmd=="help" || argc==1)
        printHelp();
    else if(cmd=="add")
        addTask(argc, argv);
    else if(cmd=="ls")
        lsTask();
    else if(cmd=="del")
        delTask(argc, argv);
    else if(cmd=="done")
        doneTask(argc, argv);
    else if(cmd=="report")
        report();
    else
        printHelp();

    return 0;
}

#include<iostream>
#include<vector>
using namespace std;
void nextFit(vector<int> task,vector<int> memory)
{
    int lastIndex = 0;
    vector<pair<int,int>> result;
    for(int i=0;i<task.size();i++)
    {
        bool allocated = false;
        for(int j=0;j<memory.size();j++)
        {
            int index = (lastIndex + j)%memory.size();


            if (task[i] <= memory[index])
            {
                result.push_back({i, index});
                memory[index] -= task[i];  // Allocate the task to the memory block


                task[i] = -1;  // Mark the task as allocated
                lastIndex = index;  // Update the last allocated index
                allocated = true;
                break;
            }
        }
        
    }


    for(auto i : result)
    {
        cout<<"T"<<i.first+1<<" : "<<"M"<<i.second+1<<endl;
    }
    cout<<"Task For which memory is not allocated : ";
    for(int i=0;i<task.size();i++)
    {
        if(task[i]!=-1) cout<<"T"<<i+1<<"    ";
    }
    cout<<endl;
}
void bestFit(vector<int> task,vector<int> memory)
{
    vector<pair<int,int>> result;
    for(int i=0;i<task.size();i++)
    {
        int best = -1;
        for(int j=0;j<memory.size();j++)
        {
            if(task[i]<=memory[j])
            {
                if(best==-1 || memory[best]>memory[j])
                {
                    best = j;
                }
            }
        }
        if(best!=-1)
        {
            result.push_back({i,best});
            memory[best]-=task[i];
            task[i]=-1;
        }
    }
    for(auto i : result)
    {
        cout<<"T"<<i.first+1<<" : "<<"M"<<i.second+1<<endl;
    }
    cout<<"Task For which memory is not allocated : ";
    for(int i=0;i<task.size();i++)
    {
        if(task[i]!=-1) cout<<"T"<<i+1<<"    ";
    }
    cout<<endl;


}
void firstFit(vector<int> task,vector<int> memory)
{
    // pair<task,memory>
    vector<pair<int,int>> result;
    for(int i=0;i<task.size();i++)
    {
        for(int j=0;j<memory.size();j++)
        {
            if(task[i]<=memory[j])
            {
                result.push_back({i,j});
                memory[j] -=task[i];


                task[i]=-1;
                break;
            }
        }
    }
    for(auto i : result)
    {
        cout<<"T"<<i.first+1<<" : "<<"M"<<i.second+1<<endl;
    }
    cout<<"Task For which memory is not allocated : ";
    for(int i=0;i<task.size();i++)
    {
        if(task[i]!=-1) cout<<"T"<<i+1<<"    ";
    }
    cout<<endl;
}
void worstFit(vector<int> task,vector<int> memory)
{
    vector<pair<int,int>> result;
    for(int i=0;i<task.size();i++)
    {
        int worst = -1;
        for(int j=0;j<memory.size();j++)
        {
            if(task[i]<=memory[j])
            {
                if(worst==-1 || memory[worst]<memory[j])
                {
                    worst = j;
                }
            }
        }
        if(worst!=-1)
        {
            result.push_back({i,worst});
            memory[worst]-=task[i];
            task[i]=-1;
        }
    }
    for(auto i : result)
    {
        cout<<"T"<<i.first+1<<" : "<<"M"<<i.second+1<<endl;
    }
    cout<<"Task For which memory is not allocated : ";
    for(int i=0;i<task.size();i++)
    {
        if(task[i]!=-1) cout<<"T"<<i+1<<"    ";
    }
    cout<<endl;
}
int main()
{
    vector<int> task;
    vector<int> memory;
    int t,m;
    cout<<"Enter no of Tasks : ";
    cin>>t;
    cout<<"Enter no of Memory : ";
    cin>>m;
    for(int i=0;i<t;i++)
    {
        int x;
        cout<<"Enter Task "<<i+1<<" Size : ";
        cin>>x;
        task.push_back(x);
    }
    for(int i=0;i<m;i++)
    {
        int x;
        cout<<"Enter Memory "<<i+1<<" Size : ";
        cin>>x;
        memory.push_back(x);
    }
    cout<<"------------------------------------------------\n";
    firstFit(task,memory);
    cout<<"------------------------------------------------\n";
    bestFit(task,memory);
    cout<<"------------------------------------------------\n";
    worstFit(task,memory);
    cout<<"------------------------------------------------\n";
    nextFit(task,memory);
    cout<<"------------------------------------------------\n";
}


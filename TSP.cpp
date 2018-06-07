#include<iostream>
using namespace std;

int sum=1;
int n,m,length;
int topo[10000],degree[10000];
int MAX(int a,int b)
{
    if(a<b)return b;
    else return a;
}

struct node
{
    int num;
    node *next;
    node()
    {
        next=NULL;
    }
    node(int x,node *n) :num(x),next(n){}
};

struct village
{
    int dp;
    node *next_village;
    village(){next_village=NULL;dp=1;}
    void insert(int next_village);
}a[10000];
void village::insert(int next_village)
{
    degree[next_village]++;
    if(this->next_village==NULL)
        this->next_village=new node(next_village,NULL);
    else
    {
        node *nodes=new node(next_village,this->next_village);
        this->next_village=nodes;
    }
    return;
}
void Topology()
{
    for(int i=1;i<=n;i++)
    {
        if(!degree[i])
            topo[++length]=i;
    }
    for(int i=1;topo[i];i++)
    {
        int rec=topo[i];
        for(node *tmp=a[rec].next_village;tmp!=NULL;tmp=tmp->next)
        {
            a[tmp->num].dp=MAX(a[rec].dp+1,a[tmp->num].dp);
            sum=MAX(sum,a[tmp->num].dp);
            int x=tmp->num;
            degree[x]--;
            if(!degree[x])
                topo[++length]=x;
        }
    }
}
int  main()
{
    cin>>n>>m;
    for(int i=0;i<m;i++)
    {
        int x,y;
        cin>>x>>y;
        a[x].insert(y);
    }
    Topology();
    cout<<sum;
}


#include<forward_list>
//#include<iostream>

template<class T>
T read_and_pop(forward_list<T> &t)
{
    T num;
    if(t.empty()){cout<<"the term is wrong"<<endl;exit(1);}
    num=t.front();
    t.pop_front();
    return num;
}

int main()
{
    forward_list<int> poland;
    char str;
    while(cin>>str)
    {
        if(str=='=') break;
        switch(str)
        {
            case '+':poland.push_front(read_and_pop(poland)+read_and_pop(poland));break;
            case '-':poland.push_front(read_and_pop(poland)-read_and_pop(poland));break;
            case '*':poland.push_front(read_and_pop(poland)*read_and_pop(poland));break;
            case '/':poland.push_front(read_and_pop(poland)/read_and_pop(poland));break;
            default :poland.push_front(int(str-48));
        }
    }
    cout<<poland.front()<<endl;
    return 0;
}

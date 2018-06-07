#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

//定义poly结构体，其中包含指数和系数；
typedef struct {
	int coef;
	int exp;
}poly;

//判断指数大小；
bool cmp(poly a, poly b)
{
	return a.exp>b.exp;
}

//输出多项式；
void output(vector<poly> p)
{
	vector<poly>::iterator i = p.begin();
	//cout<<i->coef << "x^" << i->exp;
	if (i->coef > 0)
		{
			if (i->exp == 1)
			{
				cout << i->coef << "x";
			}
			if (i->exp == 0)
			{
				cout << i->coef;
			}
			if (i->coef == 1)
			{
				cout << "x^" << i->exp;
			}
			else
			{
				cout << i->coef << "x^" << i->exp;
			}
		}
		//系数小于零输出；
		if (i->coef < 0)
		{
			if (i->exp == 1)
			{
				cout << i->coef << "x";
			}
			if (i->exp == 0)
			{
				cout << i->coef;
			}
			if (i->coef == -1)
			{
				cout << "-x^" << i->exp;
			}
			else
			{
				cout << i->coef << "x^" << i->exp;
			}
		}
    if (p.size()==1){cout<<endl;return;}
	for ( i = p.begin()+1; i != p.end()-1; i++ )
	{
		//系数大于零时输出；
		if (i->coef > 0)
		{
			if (i->exp == 1)
			{
				cout << "+" << i->coef << "x";
				continue;
			}
			if (i->exp == 0)
			{
				cout << "+" << i->coef;
				continue;
			}
			if (i->coef == 1)
			{
				cout << "+x^" << i->exp;
				continue;
			}
			else
			{
				cout << "+" << i->coef << "x^" << i->exp;
				continue;
			}
		}
		//系数小于零时输出；
		if (i->coef < 0)
		{
			if (i->exp == 1)
			{
				cout << i->coef << "x";
				continue;
			}
			if (i->exp == 0)
			{
				cout << i->coef;
				continue;
			}
			if (i->coef == -1)
			{
				cout << "-x^" << i->exp;
				continue;
			}
			else
			{
				cout << i->coef << "x^" << i->exp;
				continue;
			}
		}
	}
	vector<poly>::iterator j = p.end()-1;
	if (j->coef > 0)
		{
            if ((j->exp==1)&&(j->coef==1))
            {
                cout << "+x";
            }
			else if (j->exp == 1)
			{
				cout << "+" << j->coef << "x";
			}
			else if (i->exp == 0)
			{
				cout << "+" << j->coef;
			}
			else if (i->coef == 1)
			{
				cout << "+x^" << j->exp;
			}
			else
			{
				cout << "+" << j->coef << "x^" << j->exp;
			}
		}
		if (j->coef < 0)
		{
		    if ((j->exp==1)&&(j->coef==-1))
            {
                cout << "-x";
            }
			else if (j->exp == 1)
			{
				cout << j->coef << "x";
			}
			else if (j->exp == 0)
			{
				cout << j->coef;
			}
			else if (j->coef == -1)
			{
				cout << "-x^" << j->exp;
			}
			else
			{
				cout << j->coef << "x^" << j->exp;
			}
		}
	cout << endl;
}

//按指数排大小，并合并同类项；
void arrange(vector<poly> p)
{
	//printf("%d", p.size());
	//降幂排序;
	sort(p.begin(), p.end(), cmp);

	//合并同类项;
	int tmp;
	if (p.size()>1)
	{
		for (int n = 0; n < 5; n++)
		{
			for (vector<poly>::iterator i = p.begin() + 1; i != p.end(); i++)
			{
				if (i->exp == (i - 1)->exp)
				{
					(i - 1)->coef += i->coef;
					i->coef = 0;
				}
			}
		}
	}
	output(p);

}

int main()
{
    cout<<"================================一元多项式加减乘运算========================="<<endl;
	cout<<"||请按照程序提示输入,例如：                                                ||"<<endl;
	cout<<"||请输入第一个多项式所含的单项式个数：                                     ||"<<endl;
	cout<<"||请输入第一个多项式各单项式系数和指数，第一个数为系数，第二个数为指数     ||"<<endl;
	cout<<"||输出一行，为第一次所输入的一元多项式                                     ||"<<endl;
	cout<<"||请输入需要进行的运算，+、-、*                                            ||"<<endl;
	cout<<"||请输入第二个多项式所含的单项式个数：                                     ||"<<endl;
	cout<<"||请输入第二个多项式各单项式系数和指数，第一个数为系数，第二个数为指数     ||"<<endl;
	cout<<"||输出一行，为第二次所输入的一元多项式                                     ||"<<endl;
	cout<<"||输出一行，为一元多项式的运算结果                                         ||"<<endl;
	cout<<"||                                                                         ||"<<endl;
	cout<<"||                                                制作人：徐希迎、徐旭     ||"<<endl;
	cout<<"============================================================================="<<endl;
	vector<poly> a, b, c;
	int n;
	char way;

	cout << "请输入第一个多项式所含的单项式个数：";
	cin >> n;
	cout << "请输入第一个多项式各单项式系数和指数：" << endl;
	while (n--)
	{
		poly tmp;
		cin >> tmp.coef >> tmp.exp;
		a.push_back(tmp);
	}
	cout << "第一个多项式为：";
	arrange(a);
    cout << "============================================================================="<<endl;
	cout << "请输入你要进行的运算方法：";
	cin >> way;
    cout << "============================================================================="<<endl;
	cout << "请输入第二个多项式包含的单项式个数：";
	cin >> n;
	cout << "请输入第二个多项式各单项式系数和指数：" << endl;
	while (n--)
	{
		poly tmp2;
		cin >> tmp2.coef >> tmp2.exp;
		b.push_back(tmp2);
	}
	cout << "第二个多项式为：";
	arrange(b);


	//定义加法运算
	if (way == '+')
	{
		for (int i = 0; i < a.size(); i++)
			c.push_back(a[i]);
		for (int i = 0; i < b.size(); i++)
			c.push_back(b[i]);
	}


	//定义减法运算
	if (way == '-')
	{
		poly tmp3;
		for (int i = 0; i < a.size(); i++)
		{
			tmp3.coef = a[i].coef;
			tmp3.exp = a[i].exp;
			c.push_back(tmp3);
		}
		for (int i = 0; i < b.size(); i++)
		{
			tmp3.coef = -b[i].coef;
			tmp3.exp = b[i].exp;
			c.push_back(tmp3);
		}
	}


	//定义乘法运算
	if (way == '*')
	{
		for (int i = 0; i < a.size(); i++)
		{
			for (int j = 0; j < b.size(); j++)
			{
				poly tmp3;
				tmp3.coef = a[i].coef*b[j].coef;
				tmp3.exp = a[i].exp + b[j].exp;
				c.push_back(tmp3);
			}
		}
	}

	if (way != '+' && way != '-' && way != '*')
	{
		cout << "无法计算" << endl;
		system("pause");
	}
    cout << "============================================================================="<<endl;
	cout << "计算结果为：";
	arrange(c);
    cout << "============================================================================="<<endl;
}

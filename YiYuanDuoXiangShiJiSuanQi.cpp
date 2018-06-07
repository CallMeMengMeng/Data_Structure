#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

//����poly�ṹ�壬���а���ָ����ϵ����
typedef struct {
	int coef;
	int exp;
}poly;

//�ж�ָ����С��
bool cmp(poly a, poly b)
{
	return a.exp>b.exp;
}

//�������ʽ��
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
		//ϵ��С���������
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
		//ϵ��������ʱ�����
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
		//ϵ��С����ʱ�����
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

//��ָ���Ŵ�С�����ϲ�ͬ���
void arrange(vector<poly> p)
{
	//printf("%d", p.size());
	//��������;
	sort(p.begin(), p.end(), cmp);

	//�ϲ�ͬ����;
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
    cout<<"================================һԪ����ʽ�Ӽ�������========================="<<endl;
	cout<<"||�밴�ճ�����ʾ����,���磺                                                ||"<<endl;
	cout<<"||�������һ������ʽ�����ĵ���ʽ������                                     ||"<<endl;
	cout<<"||�������һ������ʽ������ʽϵ����ָ������һ����Ϊϵ�����ڶ�����Ϊָ��     ||"<<endl;
	cout<<"||���һ�У�Ϊ��һ���������һԪ����ʽ                                     ||"<<endl;
	cout<<"||��������Ҫ���е����㣬+��-��*                                            ||"<<endl;
	cout<<"||������ڶ�������ʽ�����ĵ���ʽ������                                     ||"<<endl;
	cout<<"||������ڶ�������ʽ������ʽϵ����ָ������һ����Ϊϵ�����ڶ�����Ϊָ��     ||"<<endl;
	cout<<"||���һ�У�Ϊ�ڶ����������һԪ����ʽ                                     ||"<<endl;
	cout<<"||���һ�У�ΪһԪ����ʽ��������                                         ||"<<endl;
	cout<<"||                                                                         ||"<<endl;
	cout<<"||                                                �����ˣ���ϣӭ������     ||"<<endl;
	cout<<"============================================================================="<<endl;
	vector<poly> a, b, c;
	int n;
	char way;

	cout << "�������һ������ʽ�����ĵ���ʽ������";
	cin >> n;
	cout << "�������һ������ʽ������ʽϵ����ָ����" << endl;
	while (n--)
	{
		poly tmp;
		cin >> tmp.coef >> tmp.exp;
		a.push_back(tmp);
	}
	cout << "��һ������ʽΪ��";
	arrange(a);
    cout << "============================================================================="<<endl;
	cout << "��������Ҫ���е����㷽����";
	cin >> way;
    cout << "============================================================================="<<endl;
	cout << "������ڶ�������ʽ�����ĵ���ʽ������";
	cin >> n;
	cout << "������ڶ�������ʽ������ʽϵ����ָ����" << endl;
	while (n--)
	{
		poly tmp2;
		cin >> tmp2.coef >> tmp2.exp;
		b.push_back(tmp2);
	}
	cout << "�ڶ�������ʽΪ��";
	arrange(b);


	//����ӷ�����
	if (way == '+')
	{
		for (int i = 0; i < a.size(); i++)
			c.push_back(a[i]);
		for (int i = 0; i < b.size(); i++)
			c.push_back(b[i]);
	}


	//�����������
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


	//����˷�����
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
		cout << "�޷�����" << endl;
		system("pause");
	}
    cout << "============================================================================="<<endl;
	cout << "������Ϊ��";
	arrange(c);
    cout << "============================================================================="<<endl;
}

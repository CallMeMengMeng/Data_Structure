
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"
#include<queue>
#include<stack>
#include<stdio.h>

/* given */
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

/* given */
twoDtree::~twoDtree(){
	clear();
}

/* given */
twoDtree::twoDtree(const twoDtree & other) {
	       root = NULL;
	       copy(other);
}

/* given */
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn)
{
    /* your code here */
    stats s(imIn);
    pair<int ,int> ul(0,0);
    pair<int,int> lr(imIn.width()-1,imIn.height()-1);
    height = imIn.height();
    width =imIn.width();
    root = buildTree(s,ul,lr);
    //cout<<root->upLeft.first<<endl;
}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr) {
	/* your code here */
	Node *tmproot;                          //定义一个临时节点指针
	Node *result;                           //记录头节点指针的位置
	queue<Node*> t;
	Node* newroot = new Node(ul,lr,s.getAvg(ul,lr));    //新建根节点
	tmproot = newroot;
	result = tmproot;
	//cout<<tmproot->upLeft.first<<endl;
    t.push(tmproot);
    int count=0;              //设置一个计数器，若为偶数则水平切割，若为奇数则竖直切割
    int layer =0;
    int count1 = 0;
    while(!t.empty())                       //利用队列进行层次建树
        {
            tmproot = t.front();
            t.pop();
            pair<int,int>tul(tmproot->upLeft);
            pair<int,int>tlr(tmproot->lowRight);
            pair<int,int>r_ul(0,0);                                  //定义切割后右子树的左上角
            pair<int,int>r_lr(0,0);
          /*  int tttt = 1;
            for(int i=0;i<layer;i++)
                tttt*=2;
            if(count>=tttt)
            {
                layer++;count = 0;
            }
          count++;
          if((tlr.first-tul.first<3&&layer%2==1)||(tlr.second-tul.second<3&&layer%2==0))    //若矩阵规模小于3*3则不再分割
          {

               tmproot->left=NULL;
               tmproot->right=NULL;
             cout<<"ul "<<tmproot->upLeft.first<<" "<<tmproot->upLeft.second<<endl;
              cout<<"lr "<<tmproot->lowRight.first<<" "<<tmproot->lowRight.second<<endl;
              printf("ave r= %d\n",tmproot->avg.r);
              printf("ave g= %d\n",tmproot->avg.g);
              printf("ave b= %d\n",tmproot->avg.b);
               continue;
          }
          else
          {
              long long score=-1;
                                              //定义切割后左子树的右下角
              if(layer%2==0)                                            //水平切割
              {
                  for(int i=tul.second+1;i<tlr.second;i++)
                  {
                      pair<int,int>temp1(lr.first,i);
                      pair<int,int>temp2(ul.first,i);
                      long long temp = s.getScore(tul,temp1)+s.getScore(temp2,tlr);
                      if(score<temp)
                      {
                         r_ul.first = tul.first; r_ul.second = i;
                         r_lr.first = tlr.first; r_lr.second = i;
                         score = temp;
                      }
                  }
              }
              else                                                                  //竖直切割，思路同水平切割
              {

                 for(int i=tul.first+1;i<tlr.first;i++)
                  {
                      pair<int,int>temp1(i,lr.second);
                      pair<int,int>temp2(i,ul.second);
                      long long temp = s.getScore(tul,temp1)+s.getScore(temp2,tlr);
                      if(score<temp)
                      {
                         r_ul.first = i; r_ul.second = tul.second;
                         r_lr.first = i; r_lr.second = tlr.second;
                         score = temp;
                      }
                  }
              }*/
              //下一次切割换另一个维度
              if(tlr.first-tul.first<3&&tlr.second-tul.second<3)
              {
                  tmproot->left=NULL;
                  tmproot->right=NULL;
                  continue;
              }
              long long score=-1;
              if(tlr.second-tul.second>=3){
                for(int i=tul.second+1;i<tlr.second;i++)
                  {
                      pair<int,int>temp1(lr.first,i);
                      pair<int,int>temp2(ul.first,i);
                      long long temp = s.getScore(tul,temp1)+s.getScore(temp2,tlr);
                      if(score<temp)
                      {
                         r_ul.first = tul.first; r_ul.second = i;
                         r_lr.first = tlr.first; r_lr.second = i;
                         score = temp;
                      }
                  }
              }
              if(tlr.first-tul.first>=3){
                  for(int i=tul.first+1;i<tlr.first;i++)
                  {
                      pair<int,int>temp1(i,lr.second);
                      pair<int,int>temp2(i,ul.second);
                      long long temp = s.getScore(tul,temp1)+s.getScore(temp2,tlr);
                      if(score<temp)
                      {
                         r_ul.first = i; r_ul.second = tul.second;
                         r_lr.first = i; r_lr.second = tlr.second;
                         score = temp;
                      }
                  }
              }
              //count1++;
              Node *l_chirdnode=new Node(tmproot->upLeft,r_lr,s.getAvg(tmproot->upLeft,r_lr));
              Node *r_chirdnode=new Node(r_ul,tmproot->lowRight,s.getAvg(r_ul,tmproot->lowRight));
              tmproot->right = r_chirdnode;
              tmproot->left  = l_chirdnode;
              t.push(tmproot->left);
              t.push(tmproot->right);
              count1++;
              /*cout<<"original ul "<<tul.first<<" "<<tul.second<<endl;
              cout<<"original lr "<<tlr.first<<" "<<tlr.second<<endl;
              cout<<"new l_child ul "<<tmproot->left->upLeft.first<<" "<<tmproot->left->upLeft.second<<endl;
              cout<<"new l_child lr "<<tmproot->left->lowRight.first<<" "<<tmproot->left->lowRight.second<<endl;
              cout<<"new r_child ul "<<tmproot->right->upLeft.first<<" "<<tmproot->right->upLeft.second<<endl;
              cout<<"new r_child lr "<<tmproot->right->lowRight.first<<" "<<tmproot->right->lowRight.second<<endl;
              printf("ave r= %d\n",tmproot->avg.r);
              printf("ave g= %d\n",tmproot->avg.g);
              printf("ave b= %d\n",tmproot->avg.b);
              //cout<<"lawer = "<<lawer<<endl;
              //cout<<"count = "<<count<<endl;
              cout<<"*************************************"<<endl;*/
          }
        cout<<"切割次数 "<<count1<<endl;
        return result;


}

PNG twoDtree::render(){
	/* your code here */
    PNG Newpng(width,height);
    Node *x = root;
    stack<Node*> t;
    t.push(root);
    while(!t.empty())
    {
        x=t.top();t.pop();
        if(x->right)
        {
            t.push(x->right);
        }
        if(x->left)
        {
            t.push(x->left);
        }
        if(x->right==NULL&&x->left==NULL)
        {
            RGBAPixel *tm;
           /* cout<<"x坐标是"<<x->upLeft.first<<","<<x->upLeft.second<<endl;
            cout<<"y坐标是"<<x->lowRight.first<<","<<x->lowRight.second<<endl;
            printf("r = %d\n",x->avg.r);
            printf("g = %d\n",x->avg.g);
            printf("b = %d\n",x->avg.b);
            cout<<"**********************************************"<<endl;*/
            for(int i = x->upLeft.first;i<=x->lowRight.first;i++)
            {
                for(int j = x->upLeft.second;j<=x->lowRight.second;j++)
                {

                    tm = Newpng.getPixel(i,j);
                    *tm = x->avg;
                }
            }
        }
    }
    cout<<"render complete"<<endl;
    return Newpng;


}

void twoDtree::prune(double pct, int tol){
	/* your code here */
	/*stack<Node*> t;
	Node *tp_l = root->left;
	Node *tp_r = root->right;
	t.push(root);
	Node *tp1_father= root;
	while(!t.empty())
    {
        tp1_father = t.top();t.pop();
        tp_l = tp1_father->left;
        tp_r = tp1_father->right;
        if(tp1_father->right)
        {
            t.push(tp1->right);
        }
        if(tp1_father->left)
        {
            t.push(tp1->left);
        }
        stack <Node*> s;
        int w_count=0;
        int r_count=0;
        Node *t =
        s.push(tp1);
        Node *tp2 = tp1;
        int ave = (tp1->avg.a)*(tp1->avg.a)+(tp1->avg.b)*(tp1->avg.b)+(tp1->avg.g)*(tp1->avg.g);
        //cout<<"ave "<<ave<<endl;
        while(!s.empty())
        {
            tp2 = s.top();s.pop();
            if(tp2->right)
            {
                s.push(tp2->right);
            }
            if(tp2->left)
            {
                s.push(tp2->left);
            }
            if(tp2->left==NULL&&tp2->right==NULL)
            {
                unsigned char r = tp2->avg.r;
                unsigned char g = tp2->avg.g;
                unsigned char b = tp2->avg.b;
                int s = r*r+g*g+b*b;
                if(s>=ave-tol&&s<=ave+tol)
                    r_count++;
                else
                    w_count++;
            }
        }
        if((r_count/(r_count+w_count))>=pct)
        {
            //cout<<tp1->upLeft.first<<","<<tp1->upLeft.second<<endl;
            //cout<<tp1->lowRight.first<<","<<tp1->lowRight.second<<endl;
            tp1->left=NULL;
            tp1->right=NULL;


        }


    }*/
    stack<Node*> t;
    Node *x= root;
    if(x) t.push(x);
    while(!t.empty())
    {
        x = t.top();t.pop();
        if(x->right)
        {
            t.push(x->right);
        }
        if(x->left)
        {
            t.push(x->left);
        }
        int ave = (x->avg.a)*(x->avg.a)+(x->avg.b)*(x->avg.b)+(x->avg.g)*(x->avg.g);
        stack <Node*> s;
        int w_count=0;
        int r_count=0;
        Node *t = x->left;
        if(t)s.push(t);
        else
        {
            continue;
        }
        while(!s.empty())
        {
             t = s.top();s.pop();
            if(t->right)
            {
                s.push(t->right);
            }
            if(t->left)
            {
                s.push(t->left);
            }
            if(t->left==NULL&&t->right==NULL)
            {
                unsigned char r = t->avg.r;
                unsigned char g = t->avg.g;
                unsigned char b = t->avg.b;
                int temp = r*r+g*g+b*b;
                if(temp>=ave-tol&&temp<=ave+tol)
                    r_count++;
                else
                    w_count++;
            }

        }

         if((r_count/(r_count+w_count))>=pct)
        {
           if(t->left!=NULL)
                t->left=NULL;
            if(t->right!=NULL)
                t->right=NULL;

            continue;
        }
        w_count=0;
        r_count=0;
        t = x->right;

        if(t)s.push(t);
        else
            continue;
        while(!s.empty())
        {
             t = s.top();s.pop();
            if(t->right)
            {
                s.push(t->right);
            }
            if(t->left)
            {
                s.push(t->left);
            }
            if(t->left==NULL&&t->right==NULL)
            {
                unsigned char r = t->avg.r;
                unsigned char g = t->avg.g;
                unsigned char b = t->avg.b;
                int temp= r*r+g*g+b*b;
                if(temp>=ave-tol&&temp<=ave+tol)
                    r_count++;
                else
                    w_count++;
            }

        }
         if((r_count/(r_count+w_count))>=pct)
        {
          if(t->left!=NULL)
                t->left=NULL;
          if(t->right!=NULL)
                t->right=NULL;


            continue;
        }

    }
}

void twoDtree::clear() {
	/* your code here */
        /*cout<<"2 "<<root->upLeft.first<<endl;
        stack<Node*> tt;
        tt.push(root);
        Node *tmp;
        tmp = tt.top();
      /*  while(!tt.empty())
        {   root = tt.top();tt.pop();
            cout<<root->upLeft.first<<" "<<root->upLeft.second<<endl;
            if(root->right){ tt.push(root->right);}
            if(root->left) tt.push(root->left);
        }*/
        if(!root)
            return ;
        else
        {
            stack<Node*> t;
            t.push(root);
            while(!t.empty())
            {
                root = t.top();t.pop();
                if(root->right) t.push(root->right);
                if(root->left) t.push(root->left);
                delete root;

            }

        }
       // cout<<"clear completed"<<endl;
}


void twoDtree::copy(const twoDtree & orig){
	/* your code here */
    Node *tp2 = orig.root;
    Node* newroot = new Node(tp2->upLeft,tp2->lowRight,tp2->avg);
    root = newroot;
    Node *tp1 = root;
    if(tp2->left==NULL&&tp2->right==NULL)
    {
            Node* newnode = new Node(tp2->upLeft,tp2->lowRight,tp2->avg);
            tp1 = newnode;
    }
    else
    {
            stack<Node*> s1;
            stack<Node*> s2;
            s1.push(tp1);s2.push(tp2);
            while(!s2.empty())
            {
                 tp1 = s1.top();s1.pop();
                 tp2 = s2.top();s2.pop();
                 if(tp2->right)
                 {
                     Node* r_node = new Node(tp2->right->upLeft,tp2->right->lowRight,tp2->right->avg);
                     tp1->right= r_node;
                     s1.push(tp1->right);s2.push(tp2->right);
                 }
                 else
                 {
                     tp1->right = NULL;
                 }
                 if(tp2->left)
                 {
                     Node* l_node = new Node(tp2->left->upLeft,tp2->left->lowRight,tp2->left->avg);
                     tp1->left= l_node;
                     s1.push(tp1->left);s2.push(tp2->left);
                 }
                 else
                 {
                     tp1->left = NULL;
                 }

            }
    }

    //*************************************用于测试是否复制成功********************
    /*Node *p1=root;
    Node *p2= orig.root;
    stack<Node*>t1,t2;
    t1.push(root);t2.push(orig.root);
    while(!t1.empty())
    {   p1 = t1.top();t1.pop();
        p2 = t2.top();t2.pop();
        if(p1->upLeft!=p2->upLeft){cout<<"error"<<endl;return ;}
        if(p2->left)
        {
            t1.push(p1->left);t2.push(p2->left);
        }
        else
        {
            if(p1->left !=NULL) {cout<<"error"<<endl;return ;}
        }
        if(p2->right)
        {
            t1.push(p1->right);t2.push(p2->right);
        }
        else
        {
            if(p1->right!=NULL) {cout<<"error"<<endl;return ;}
        }
    }
    cout<<"copy complete"<<endl;*/

}




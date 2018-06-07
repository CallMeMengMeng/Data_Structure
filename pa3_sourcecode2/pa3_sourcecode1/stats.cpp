#include "stats.h"
#include<vector>
#include<stdio.h>
using namespace cs221util;
long long stats::getSum(char channel, pair<int,int> ul, pair<int,int> lr)
{
       long long tmp = 0;
        switch(channel)
        {
            case 'r':
                tmp = sumRed[lr.first][lr.second] + sumRed[ul.first][ul.second]
                    - sumRed[lr.first][ul.second] - sumRed[ul.first][lr.second];
                    break;
            case 'g':
                tmp = sumGreen[lr.first][lr.second] + sumGreen[ul.first][ul.second]
                    - sumGreen[lr.first][ul.second] - sumGreen[ul.first][lr.second];
                    break;
            case 'b':
                tmp = sumBlue[lr.first][lr.second] + sumBlue[ul.first][ul.second]
                    - sumBlue[lr.first][ul.second] - sumBlue[ul.first][lr.second];
                    break;
        }

        return tmp;
}
long long stats::getSumSq(char channel, pair<int,int> ul, pair<int,int> lr)
{
      long long int tmp = 0;
        switch(channel)
        {
            case 'r':
                tmp = sumsqRed[lr.first][lr.second] + sumsqRed[ul.first][ul.second]
                    - sumsqRed[lr.first][ul.second] - sumsqRed[ul.first][lr.second];
                    break;
            case 'g':
                tmp = sumsqGreen[lr.first][lr.second] + sumsqGreen[ul.first][ul.second]
                    - sumsqGreen[lr.first][ul.second] - sumsqGreen[ul.first][lr.second];
                    break;
            case 'b':
                tmp = sumsqBlue[lr.first][lr.second] + sumsqBlue[ul.first][ul.second]
                    - sumsqBlue[lr.first][ul.second] - sumsqBlue[ul.first][lr.second];
                    break;
        }
        return tmp;
}
stats::stats(PNG & im)
{
    for(int i=0;i<im.width();i++)
  {
      sumRed.push_back(vector<long long> (im.height(),0));
      sumGreen.push_back(vector<long long> (im.height(),0));
      sumBlue.push_back(vector<long long> (im.height(),0));
      sumsqRed.push_back(vector<long long> (im.height(),0));
      sumsqGreen.push_back(vector<long long> (im.height(),0));
      sumsqBlue.push_back(vector<long long> (im.height(),0));

  }
                sumRed[0][0] = im.getPixel(0,0)->r;
                sumGreen[0][0] = im.getPixel(0,0)->g;
                sumBlue[0][0] = im.getPixel(0,0)->b;
                for(int i= 1;i<im.width();i++)
                {
                    sumRed[i][0]=sumRed[i-1][0]+im.getPixel(i,0)->r;
                    sumGreen[i][0]=sumGreen[i-1][0]+im.getPixel(i,0)->g;
                    sumBlue[i][0] = sumBlue[i-1][0]+im.getPixel(i,0)->b;
                }
                for(int i=1;i<im.height();i++)
                {
                    sumRed[0][i]=sumRed[0][i-1]+im.getPixel(0,i)->r;
                    sumGreen[0][i]=sumGreen[0][i-1]+im.getPixel(0,i)->g;
                    sumBlue[0][i] = sumBlue[0][i-1]+im.getPixel(0,i)->b;
                }
                for(int i = 1;i<im.width();i++)
                    for(int j=1;j<im.height();j++)
                {
                    sumRed[i][j] = im.getPixel(i,j)->r+sumRed[i-1][j]+sumRed[i][j-1]-sumRed[i-1][j-1];
                    sumGreen[i][j] = im.getPixel(i,j)->g+sumGreen[i-1][j]+sumGreen[i][j-1]-sumGreen[i-1][j-1];
                    sumBlue[i][j] = im.getPixel(i,j)->b+sumBlue[i-1][j]+sumBlue[i][j-1]-sumBlue[i-1][j-1];
                }
                 sumsqRed[0][0] = (im.getPixel(0,0)->r)*(im.getPixel(0,0)->r);
                sumsqGreen[0][0] = (im.getPixel(0,0)->g)*(im.getPixel(0,0)->g);
                sumsqBlue[0][0] = (im.getPixel(0,0)->b)*(im.getPixel(0,0)->b);
                for(int i= 1;i<im.width();i++)
                {
                    sumsqRed[i][0]=sumsqRed[i-1][0]+(im.getPixel(i,0)->r)*(im.getPixel(i,0)->r);
                    sumsqGreen[i][0]=sumsqGreen[i-1][0]+(im.getPixel(i,0)->g)*(im.getPixel(i,0)->g);
                    sumsqBlue[i][0] = sumsqBlue[i-1][0]+(im.getPixel(i,0)->b)*(im.getPixel(i,0)->b);
                }
                for(int i=1;i<im.height();i++)
                {
                    sumsqRed[0][i]=sumsqRed[0][i-1]+(im.getPixel(0,i)->r)*(im.getPixel(0,i)->r);
                    sumsqGreen[0][i]=sumsqGreen[0][i-1]+(im.getPixel(0,i)->g)*(im.getPixel(0,i)->g);
                    sumsqBlue[0][i] = sumsqBlue[0][i-1]+(im.getPixel(0,i)->b)*(im.getPixel(0,i)->b);
                }
                for(int i = 1;i<im.width();i++)
                    for(int j=1;j<im.height();j++)
                {
                    sumsqRed[i][j] = (im.getPixel(i,j)->r)*(im.getPixel(i,j)->r)+sumsqRed[i-1][j]+sumsqRed[i][j-1]-sumsqRed[i-1][j-1];
                    sumsqGreen[i][j] = (im.getPixel(i,j)->g)*(im.getPixel(i,j)->g)+sumsqGreen[i-1][j]+sumsqGreen[i][j-1]-sumsqGreen[i-1][j-1];
                    sumsqBlue[i][j] = (im.getPixel(i,j)->b)*(im.getPixel(i,j)->b)+sumsqBlue[i-1][j]+sumsqBlue[i][j-1]-sumsqBlue[i-1][j-1];
                }
}
long long stats::getScore(pair<int,int> ul, pair<int,int> lr)
{
        long long score = 0;
        // 计算面积时边长+1
        long long area = (ul.first-lr.first)*(lr.second-ul.second);
        //cout<<"area "<<area<<endl;
        score += getSumSq('r',ul,lr) - getSum('r',ul,lr)*getSum('r',ul,lr)/area;
        score += getSumSq('g',ul,lr) - getSum('g',ul,lr)*getSum('g',ul,lr)/area;
        score += getSumSq('b',ul,lr) - getSum('b',ul,lr)*getSum('b',ul,lr)/area;
        //cout<<"score "<<score<<endl;

        return score;
}
RGBAPixel stats::getAvg(pair<int,int> ul, pair<int,int> lr)
{
        long long area = (lr.first-ul.first+1)*(lr.second-ul.second+1);
        unsigned char r;
        unsigned char g;
        unsigned char b;
        r = getSum('r',ul,lr)/area;
        g = getSum('g',ul,lr)/area;
        b = getSum('b',ul,lr)/area;
        RGBAPixel tmp(r,g,b);
        return tmp;
}
long long stats::rectArea(pair<int,int> ul, pair<int,int> lr)
{
        long long area = (ul.first-lr.first+1)*(lr.second-ul.second+1);
        return area;
}



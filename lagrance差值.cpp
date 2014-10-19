***********************Sample1-lagrange************************* 
#include<iostream> 
#include<cmath> 
using namespace std; 

int lagrange(double *px,double *py,double *pcoeff,int iNum) 
{ //px 存储已知点横坐标值，py 存储已知点纵坐标值,pcoeff 带回 
  //多项式的系数，iNum 为已知点个数 
  //以下变量名皆对应公式所用字母 
double *pk,*ptemp_coeff; 
int i,j,k,kk; pk=new double [iNum]; 
ptemp_coeff=new double [iNum]; 
//初始化系数数组 
for(i=0;i<iNum;i++) { 
pcoeff[i]=0.0; 
ptemp_coeff[i]=0.0; 
} 
//以下为公式（1） 
for(i=0;i<iNum;i++) { 
pk[i]=1.0; 
for(j=0;j<iNum;j++) { 
if(i!=j) { 
pk[i]*=px[i]-px[j]; 
} 
} 
} 
//i 循环为公式（3） 循环为公式（2） ，j 
for(i=0;i<iNum;i++) { 
ptemp_coeff[0]=1.0; //乘积因子 1.0 
  for(j=0,k=0;j<iNum;j++) //乘以第 j 个因子 
  { 
  if(j!=i) { 
    for(k++,kk=k;kk>0;kk--) 
{ 
  ptemp_coeff[kk]-=ptemp_coeff[kk-1]*px[j]; 
} 
  } 
  } 
  for(j=0;j<iNum;j++)//公式（3） ，求和 
  { 
  pcoeff[j]+=py[i]*ptemp_coeff[j]/pk[i]; 
  ptemp_coeff[j]=0.0; 
  } 
} 
   delete pk,ptemp_coeff; 
return 0; 
} 
double lagcaculate(double *pcoeff,double dxx,int iNum) { 
//dxx 表示需要估计函数值处的横坐标 
//由拉格朗日插值公式计算函数值 
//返回计算所得函数值 
double dsum; 
int i; 
dsum=0.0; 
for(i=0;i<iNum;i++) { 
dsum=dsum*dxx+pcoeff[i]; 
} 
return dsum; 
} 
int main() { 
int iNum,i,iisrandom; 
double *px,*py,*pcoeff; 
cout<<"本程序求解拉格朗日插值求解函数近似值" <<endl<<"请输入已知点个数:"<<endl; cin>>iNum; cout<<"是否进行自动测试（测试函数为正弦函数）,是输入 1，否输入 0："; 
cin>>iisrandom; 
px=new double [iNum]; 
py=new double [iNum]; 
pcoeff=new double [iNum]; 
if(iisrandom==0) { 
cout<<"请输入 iNum 个已知点的横坐标:"<<endl; 
for(i=0;i<iNum;i++) { 
cin>>px[i]; 
} 
cout<<"请输入 iNum 个已知点的纵坐标:"<<endl; 
for(i=0;i<iNum;i++) { 
cin>>py[i]; 
} 
} else { 
for(i=0;i<iNum;i++) { px[i]=i; py[i]=sin(i); 
} 
} 
lagrange(px,py,pcoeff, iNum); 
int testnum; 
cout<<"输入测试值数量"; cin>>testnum; 
double *pxvalue; 
pxvalue=new double [testnum]; 
double *pyvalue; 
pyvalue=new double [testnum]; 
cout<<"输入"<<testnum<<"个需要测试的值"<<endl; 
for(i=0;i<testnum;i++) //输入 testnum 个需要求近似值的自变量值 
{ cin>>pxvalue[i]; } 
for(i=0;i<testnum;i++) //有拉格朗日插值公式计算近似值 
{ pyvalue[i]=lagcaculate(pcoeff,pxvalue[i],iNum); 
py[i]=sin(pxvalue[i]); 
} 
cout<<"拉格朗日公式求得的值"<<"    "<<"标准函数值为"<<endl; 

for(i=0;i<testnum;i++) { 
cout<<pyvalue[i]<<"     "<<py[i]<<endl; 
} 
delete px,py,pcoeff,pxvalue,pyvalue; 
return 0; 
} 


***********************Sample2-lagrange&Newton*********************** 


#include<stdio.h> 
#include<stdlib.h> 
#include<iostream.h> 
typedef struct data 
{ 
float x; 
float y; 
}Data;//变量x和函数值y的结构 
Data d[20];//最多二十组数据 
float f(int s,int t)//牛顿插值法，用以返回插商 
{ 
if(t==s+1) 
  return (d[t].y-d[s].y)/(d[t].x-d[s].x); 
else 
        return (f(s+1,t)-f(s,t-1))/(d[t].x-d[s].x);  
} 
//float Newton(float x,int count) 
//{ 
// int n; 
//while(1) 
//{ 
//     cout<<"请输入n值(即n次插值):";//获得插值次数 
//  cin>>n; 
//  if(n<=count-1)// 插值次数不得大于count－1次 
//  break; 
// else 
//   system("cls"); 
// } 
//初始化t，y，yt。 
// float t=1.0; 
//float y=d[0].y; 
// float yt=0.0; 
//计算y值 
//for(int j=1;j<=n;j++) 
//{ 
// t=(x-d[j-1].x)*t; 
// yt=f(0,j)*t; 
  //cout<<f(0,j)<<endl; 
//  y=y+yt; 
//} 
// return y; 
//} 
float lagrange(float x,int count) 
{ 
float y=0.0; 
for(int k=0;k<count;k++)//这儿默认为count－1次插值 
{ 
  float p=1.0;//初始化p 
  for(int j=0;j<count;j++) 
  {//计算p的值 
   if(k==j)continue;//判断是否为同一个数 
   p=p*(x-d[j].x)/(d[k].x-d[j].x); 
  } 
  y=y+p*d[k].y;//求和 
} 
return y;//返回y的值 
} 
void main() 
{ 
float x,y; 
int count; 
while(1) 
{ 
  cout<<"请输入x[i],y[i]的组数，不得超过20组:";//要求用户输入数据组数 
  cin>>count; 
  if(count<=20) 
   break;//检查输入的是否合法 
  system("cls"); 
} 
//获得各组数据 
for(int i=0;i<count;i++) 
{ 
      cout<<"请输入第"<<i+1<<"组x的值:"; 
      cin>>d[i].x; 
      cout<<"请输入第"<<i+1<<"组y的值:"; 
      cin>>d[i].y; 
   system("cls"); 
} 
cout<<"请输入x的值:";//获得变量x的值 
cin>>x; 
while(1) 
{ 
  int choice=3; 
// cout<<"请您选择使用哪种插值法计算："<<endl; 
  //cout<<"              (0):退出"<<endl; 
  //cout<<"              (1):Lagrange"<<endl; 
// cout<<"              (2):Newton"<<endl; 
// cout<<"输入你的选择："; 
// cin>>choice;//取得用户的选择项 
choice=1; 
  //if(choice==2) 
// { 
//  cout<<"你选择了牛顿插值计算方法，其结果y为："; 
//  y=Newton(x,count);break;//调用相应的处理函数 
// } 
  //      if(choice==1) 
// { 
   cout<<"拉格朗日插值计算方法，其结果为："; 
   y=lagrange(x,count); 
   break;//调用相应的处理函数 
// } 
  if(choice==0) 
   break; 
  system("cls"); 
  cout<<"输入错误!!!!"<<endl; 
} 
cout<<y<<endl;//输出最终结果 
    
} 


//another source
实验一 Lagrange插值算法(附源程序)  

2007-10-12 14:00:28|  分类： 数值计算方法 |举报|字号 订阅
 

实验一   插值多项式

 

一、实验目的

学会Lagrange插值算法,并应用算法于实际问题。

二、实验要求

1、以0.32,0.34,0.36为节点,分别用线性插值和抛物插值求正弦函数在0.3367处的近似值;

2、取正弦函数

3、如果有错，修改直至运行成功，查看运行结果；

三、实验内容

Lagrange插值多项式： ，其中 

           

四、实验环境

计算中心机房

五、实验步骤和方法

1、程序设计

2、计算实例： 1）取正弦函数 ;

3、撰写实验报告

 

六、实验预习要求

预习Lagrange插值多项式

七、实验报告要求

实验目的明确，步骤清晰，有主要算法，实验数据，实验结果。

[源程序]

#include<iostream.h>
#include<math.h>
typedef struct data
{
 float x;
 float y;
}Data;
Data d[20];

float lagrange(float x,int count)
{
 float y=0.0;
 for(int k=0;k<count;k++)
 {
  float p=1.0;
  for(int j=0;j<count;j++)
  {
   if(k==j)continue;
   p=p*(x-d[j].x)/(d[k].x-d[j].x);
  }
  y=y+p*d[k].y;
 }
 return y;
}
void main()
{
  float x,y;
     int count,choice,i;
  cout<<"请选择1.线形插值2.抛物插值："<<endl;
  cin>>choice;
  if(choice==1)
  {
   cout<<"你选择了线形插值："<<endl;
   for(i=0;i<2;i++)
   {
      cout<<"请输入第"<<i+1<<"组x的值:";
      cin>>d[i].x;
      d[i].y=float(sin(d[i].x));
            cout<<"第"<<i+1<<"组y的值为:"<<d[i].y<<endl;
   }
         cout<<"请输入x的值：";
            cin>>x;
            y=lagrange(x,2);
         cout<<y<<endl;
  }
  else if(choice==2)
  {                                                                                                                                    
   cout<<"你选择了抛物插值："<<endl;
    while(1)
    {
  cout<<"请输入x[i],y[i]的组数，不超过20组：";
  cin>>count;
  if(count<=20)
   break;
    }
    for(int i=0;i<count;i++)
    {
  cout<<"请输入第"<<i+1<<"组x的值:";
  cin>>d[i].x;
  d[i].y=float(sin(d[i].x));
        cout<<"第"<<i+1<<"组y的值为:"<<d[i].y<<endl;
    }
    cout<<"请输入x的值：";
       cin>>x;
       y=lagrange(x,count);
    cout<<y<<endl;
  }
  else 
  {
   cout<<"输入有误"<<endl;
     }
}

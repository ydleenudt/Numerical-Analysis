/*下面举一个例,代码运行一下：取e=0.0001,用龙贝格方法计算积分
 I = ∫01 ( 4/1+X2) dx
解 按上述五步计算，此处        f(x)=4/(1+x2)   a=0 b=1      f(0)=4    f(1)=2  
由梯形公式得 
        T1=1/2[f(0)+f(1)]=3 
        计算f(1/2)=16/5   用变步长梯形公式得 
        T2=1/2[T1+f(1/2)]=3.1 
        由加速公式得 
        S1=1/3(4T2-T1)=3.133333333 

        求出f(1/4)    f(3/4) 进而求得 
        T4=1/2{T2+1/2[f(1/4)+f(3/4)]}
           =3.131176471 
        S2=1/3(4T4-T2)=3.141568628 
        C1=1/15(16S2-S1)=3.142117648 

        计算f(1/8)   f(3/8)   f(5/8)   f(7/8)进而求得 
        T8=1/2{T4+1/4[f(1/8)+f(3/8)+f(5/8)+f(7/8)]} 
            =3.138988495 
        S4=1/3(4T3-T4)=3.141592503 
        C2=1/15(16S4-S2)=3.141594095 
        R1=1/63(64C2-C1)=3.141585784
 
      把区间再二分，重复上述步骤算得
      T16=3.140941613    S8=3.141592652
      C4=3.141592662      R2=3.141592640
      由于 |R1-R2|<=0.00001,计算可停止，取R2=3.14159
代码如下:
*/
#include<iostream>
#include<cmath>

using namespace std;

#define f(x) (4.0/(1+x*x))  //举例函数
#define epsilon 0.0001  //精度
#define MAXREPT  10   //迭代次数,到最后仍达不到精度要求,则输出T(m=10).

double Romberg(double aa, double bb)
{ //aa,bb 积分上下限
    int m, n;//m控制迭代次数, 而n控制复化梯形积分的分点数. n=2^m
    double h, x;
    double s, q;
    double ep; //精度要求
    double *y = new double[MAXREPT];//为节省空间,只需一维数组
    //每次循环依次存储Romberg计算表的每行元素,以供计算下一行,算完后更新
    double p;//p总是指示待计算元素的前一个元素(同一行)

    //迭代初值
    h = bb - aa;
    y[0] = h*(f(aa) + f(bb))/2.0;
    m = 1;
    n = 1;
    ep = epsilon + 1.0;

    //迭代计算
    while ((ep >= epsilon) && (m < MAXREPT))
    {
        //复化积分公式求T2n(Romberg计算表中的第一列),n初始为1,以后倍增
        p = 0.0;
        for (int i=0; i<n; i++)//求Hn
        {
            x = aa + (i+0.5)*h;
            p = p + f(x);
        }
        p = (y[0] + h*p)/2.0;//求T2n = 1/2(Tn+Hn),用p指示

        //求第m行元素,根据Romberg计算表本行的前一个元素(p指示),
        //和上一行左上角元素(y[k-1]指示)求得.        
        s = 1.0;
        for (int k=1; k<=m; k++)
        {
            s = 4.0*s;
            q = (s*p - y[k-1])/(s - 1.0);
            y[k-1] = p;
            p = q;
        }

        p = fabs(q - y[m-1]);
        m = m + 1;
        y[m-1] = q;
        n = n + n; h = h/2.0;
    }

    return (q);
}


int main()
{
    double a,b;
    cout<<"Romberg积分,请输入积分范围a,b:"<<endl;
    cin>>a>>b;

    cout<<"积分结果:"<<Romberg(a, b)<<endl;

    system("pause");
    return 0;
}

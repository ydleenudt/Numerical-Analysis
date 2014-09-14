/*类traezoidal的数据成员*/
/*k           int       计数器*/
/*n           int       分段的个数*/
/*a,b         double    积分的下限和上限*/
/*f           double    定义被积函数*/
/*h           double    每段的宽度*/
/*integral    double    积分值*/
/*sum         double    和式*/

#inlcude<iostream.h>
#include<math.h>

class trapezoidal
{
  private:
    int n,k;
    double a, b, f, h, integral, sum;
  public:
    double func(double v)
    {
      f=24.6/(v-0.065)-5.5/pow(v,2);
      return f;
    }
    void intergration();
};

void main()
{
  trapezoidal trape;
  trape.intergration();
}

void trapezoidal::intergration()
{
  cout<<"\n输入下限和上限";
  cin>>a>>b;
  cout<<"\n输入你要的段数";
  cin>>n;
  h=(b-a)/n;
  sum=0.0;
  for(k=1;k<n;k++)
  {
    sum+=func(a+k*n);
  }
  integral=(h/2.0)*(func(a)+2.0*sum+func(b));
  cout<<endl<<"积分值 = "<<integral<<endl;
}

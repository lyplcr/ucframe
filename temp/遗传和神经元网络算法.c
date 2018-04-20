#include<fstream.h>   
 #include <iostream>   
 #include <conio.h>    
 #include <time.h>    
 #include "malloc.h"   
 #include <math.h>   
 #include "stdlib.h"   
    
    
 int n=0;//表示输入神经元个数   
 int o=0;//表示输出神经元个数   
 int h=0;//表示隐层神经元个数   
 double e=0;//表示误差   
 double s=0;//步长   
 double a=0;//学习   
 int num=0;//训练个数   
 double **X;//表示输入   
 double *XY1;   
 double *XY3;   
 double *XY2;//存放各各神经元的输入值   
 double **Y;//存放最后一列的输入值   
 double **W1,**WChangei;//表示各层的权值   
 double **W2,**WChangeo;//存放最后一列的权值   
 double *DX2,*DX3;//存放各层误差   
 double *IHB,*HOB;//存入阀值   
 ifstream fin("output.txt");   
 ifstream fin2("test2.txt");   
 ifstream fin1("GAdata.txt");   
 double dblErr=0;   
 double **individual,**Tindividual;//初始种群T是temp   
 double *bestChrom;//最佳个体染色体   
 double *fitness;//各种群的适应度   
 double minFitness=100.0;   
 double pc;//交叉概率   
 double pm;//变异概率   
 int popsize;//种群大小   
 int lchrom;//染色体长度   
 int gen;//当前世代数   
 int maxgen;//最大世代数   
 double sumfitness;//总的适应度   
 double rl=0;   
 int *b;double *bTemp;//临时变量   
 static double oldrand[55];   
 static int jrand;   
 static double rndx2;   
 static int rndcalcflag;   
 void advance_random();   
 int flip(double);rnd(int, int);   
 void randomize();   
 double randomnormaldeviate();   
 double randomperc(),rndreal(double,double);   
 void warmup_random(double);   
 void forward(int);   
 void forward1(int);   
 double randab(double , double );   
    
 void advance_random()  /* 产生55个随机数 */   
 {   
     int j1;   
     double new_random;   
     for(j1 = 0; j1 < 24; j1++)   
     {   
         new_random = oldrand[j1] - oldrand[j1+31];   
         if(new_random < 0.0) new_random = new_random + 1.0;   
         oldrand[j1] = new_random;   
     }   
     for(j1 = 24; j1 < 55; j1++)   
     {   
         new_random = oldrand [j1] - oldrand [j1-24];   
         if(new_random < 0.0) new_random = new_random + 1.0;   
         oldrand[j1] = new_random;   
     }   
 }   
    
 int flip(double prob) /* 以一定概率产生0或1 */   
 {   
     if(randab(-1.0,1.0) <= prob)   
         return(1);   
     else   
         return(0);   
 }   
    
 void randomize()  /* 设定随机数种子并初始化随机数发生器 */   
 {   
     float randomseed=1.0;   
     int j1;   
     for(j1=0; j1<=54; j1++)   
       oldrand[j1] = 0.0;   
     jrand=0;   
       do   
         {   
                
              printf("随机数种子[0-1]:");   
               scanf("%f", &randomseed);   
          }   
         while((randomseed < 0.0) || (randomseed > 1.0));   
     warmup_random(randomseed);   
 }   
    
 double randomnormaldeviate() /* 产生随机标准差 */   
 {   
     double t, rndx1;   
     if(rndcalcflag)   
     {   rndx1 = sqrt(- 2.0*log((double) randomperc()));   
         t = 6.2831853072 * (double) randomperc();   
         rndx2 = rndx1 * sin(t);   
         rndcalcflag = 0;   
         return(rndx1 * cos(t));   
     }   
     else   
     {   
         rndcalcflag = 1;   
         return(rndx2);   
     }   
 }   
    
 double randomperc() /*与库函数random()作用相同, 产生[0,1]之间一个随机数 */   
 {   
     jrand++;   
     if(jrand >= 55)   
     {   
         jrand = 1;   
         advance_random();   
     }   
     return((double) oldrand[jrand]);   
 }   
    
 int rnd(int low, int high) /*在整数low和high之间产生一个随机整数*/   
 {   
     int i;   
     double randomperc();   
     if(low >= high)   
         i = low;   
     else   
     {   
         i =(int)((randomperc() * (high - low + 1)) + low);   
         if(i > high) i = high;   
     }   
     return(i);   
 }   
    
    
 void warmup_random(double random_seed)  /* 初始化随机数发生器*/   
 {   
     int j1, ii;   
     double new_random, prev_random;   
    
     oldrand[54] = random_seed;   
     new_random = 0.000000001;   
     prev_random = random_seed;   
     for(j1 = 1 ; j1 <= 54; j1++)   
     {   
         ii = (21*j1)%54;   
         oldrand[ii] = new_random;   
         new_random = prev_random-new_random;   
         if(new_random<0.0) new_random = new_random + 1.0;   
         prev_random = oldrand[ii];   
     }   
     advance_random();   
     advance_random();   
     advance_random();   
     jrand = 0;   
 }   
    
 void initPop()   
 {   
     fin1>>popsize>>pc>>pm>>maxgen;   
     lchrom=n*h+h*o+h+o;   
     fitness=new double[popsize+1];   
     bestChrom=new double[lchrom+1];   
     individual=new double*[popsize+1];   
     Tindividual=new double*[popsize+1];   
     for(int i=1;i<=popsize;i++)   
     {   
         Tindividual[i]=new double[lchrom+1];   
         individual[i]=new double[lchrom+1];   
         for(int j=1;j<=lchrom;j++)   
         {   
             //individual[i][j]=(double)randomperc();   
             individual[i][j]=randab(-1.0,1.0);   
             cout<<individual[i][j]<<endl;   
         }   
            
     }   
        
     b=new int[popsize+1];   
     bTemp=new double[lchrom+1];   
 }   
 void initPop1()   
 {   
     lchrom=n;   
     fitness=new double[popsize+1];   
     bestChrom=new double[lchrom+1];   
     individual=new double*[popsize+1];   
     Tindividual=new double*[popsize+1];   
     for(int i=1;i<=popsize;i++)   
     {   
         Tindividual[i]=new double[lchrom+1];   
         individual[i]=new double[lchrom+1];   
         for(int j=1;j<=lchrom;j++)   
         {   
             individual[i][j]=randab(-1.0,1.0);   
         }   
            
     }   
        
     b=new int[popsize+1];   
     bTemp=new double[lchrom+1];   
 }   
 void Swap2(int &a,int &b)   
 {   
     int temp;   
     temp=a;   
     a=b;   
     b=temp;   
 }   
    
 void Swap(double &a,double &b)   
 {   
     double temp;   
     temp=a;   
     a=b;   
     b=temp;   
 }   
 int Partition(double a[],int b[],int p,int r)   
 {   
     int i=p,j=r+1;   
     double x=a[p];   
     while(true)   
     {   
         while(a[++i]>x);   
         while(a[--j]<x);   
         if(i>=j) break;   
         Swap(a[i],a[j]);   
         Swap2(b[i],b[j]);   
            
     }   
     a[p]=a[j];   
     a[j]=x;   
     return j;   
 }   
 void QuickSort(double a[],int b[],int p,int r)   
 {   
     if(p<r)   
     {   
         int q=Partition(a,b,p,r);   
         QuickSort(a,b,p,q-1);   
         QuickSort(a,b,q+1,r);   
     }   
 }   
    
 void setFitness()   
 {   
        
         for(int g=1;g<=popsize;g++)   
         {   
                
             for(int i=1;i<=n;i++)   
                 for(int j=1;j<=h;j++)   
                     W1[i][j]=individual[g][(i-1)*h+j];   
    
             for(i=1;i<=h;i++)   
                 for(int j=1;j<=o;j++)   
                     W2[i][j]=individual[g][n*h+(i-1)*o+j];   
                 for(i=1;i<=h;i++)   
                     IHB[i]=individual[g][n*h+h*o+i];   
                 for(i=1;i<=o;i++)   
                     HOB[i]=individual[g][n*h+h*o+h+i];   
    
                 double dblTotal=0.0;   
                 for(int iSample=1;iSample<=num;iSample++)   
                 {   
                     forward(iSample);   
                     dblErr=0.0;   
                     for(i=1;i<=o;i++)   
                     dblErr+=0.5*(Y[iSample][i]-XY3[i])*(Y[iSample][i]-XY3[i]);   
                     dblTotal+=dblErr;//总误差   
                 }   
                 fitness[g]=dblTotal;   
                 if(minFitness>dblTotal)   
                 {cout<<"dblTotal"<<dblTotal<<endl;   
                     minFitness=dblTotal;   
                     for(int i=1;i<=lchrom;i++)   
                         bestChrom[i]=individual[g][i];   
                        
                 }   
         }   
         //排序   
            
         for(g=1;g<=popsize;g++)   
         b[g]=g;   
         QuickSort(fitness,b,1,popsize);   
         for(g=1;g<=popsize;g++)   
             for(int i=1;i<=popsize;i++)   
             {   
                 if(b[i]==g)   
                 {   
                     for(int j=1;j<=lchrom;j++)   
                     {   
                         bTemp[j]=individual[g][j];   
                         individual[g][j]=individual[i][j];   
                         individual[i][j]=bTemp[j];   
                     }   
                 }   
             }   
    
 }   
 void setFitness1()   
 {   
        
         for(int g=1;g<=popsize;g++)   
         {   
    
             double dblTotal=0.0;   
             forward1(g);   
             for(int i=1;i<=o;i++)   
                 dblTotal=XY3[i];   
                     //总误差   
                
             fitness[g]=dblTotal;   
             if(minFitness>dblTotal)   
             {cout<<"dblTotal1"<<dblTotal<<endl;   
                 minFitness=dblTotal;   
                 for(int i=1;i<=lchrom;i++)   
                         bestChrom[i]=individual[g][i];   
                        
             }   
         }   
         //排序   
            
         for(g=1;g<=popsize;g++)   
         b[g]=g;   
         QuickSort(fitness,b,1,popsize);   
         for(g=1;g<=popsize;g++)   
             for(int i=1;i<=popsize;i++)   
             {   
                 if(b[i]==g)   
                 {   
                     for(int j=1;j<=lchrom;j++)   
                     {   
                         bTemp[j]=individual[g][j];   
                         individual[g][j]=individual[i][j];   
                         individual[i][j]=bTemp[j];   
                     }   
                 }   
             }   
    
 }   
 void preselect()   
 {   
     sumfitness=0;   
     for(int j=1;j<=popsize;j++)   
         sumfitness+=fitness[j];   
 }   
    
 int select()   
 {   
     double sum, pick;   
     int i;   
     pick=randab(-1.0,1.0);   
     sum = 0;   
     if(sumfitness != 0)   
     {   
         for(i = 1; (sum < pick) && (i <=popsize); i++)   
             sum += (double)(fitness[i]/sumfitness);   
     }   
     else   
         i = rnd(1,popsize);   
     return(i-1);   
 }   
 void crossover(int x1,int x2)//交叉运算   
 {   
     if(flip(pc))   
     {   
         rl=randab(-1.0,1.0);   
     for(int i=1;i<=popsize;i++)   
         individual[x1][i]=individual[x1][i]*rl+individual[x2][i]*(1-rl);   
     for(i=1;i<=popsize;i++)   
         individual[x2][i]=individual[x2][i]*rl+individual[x1][i]*(1-rl);   
     }   
    
 }   
    
    
 void mutation(int x)//变异   
 {   
     for(int i=1;i<=lchrom;i++)   
     {   
         if(flip(pm))    
             //individual[x][i]=randomperc();   
             individual[x][i]=randab(-1.0,1.0);   
             //esle individual[temp][i]=1+   
     }   
 }   
    
 void generation()   
 {   
   int mate1, mate2, j = 0;   
   /*  每代运算前进行预选 */   
   setFitness();   
   preselect();   
   /* 选择, 交叉, 变异 */   
   do   
     {   
       /* 挑选交叉配对 */   
       mate1 = select();   
       mate2 = select();   
    
       /* 交叉和变异 */   
       crossover(mate1,mate2);   
       for(int g=1;g<=lchrom;g++)   
       {   
           Tindividual[j+1][g]=individual[j+1][g];   
           Tindividual[j+2][g]=individual[j+2][g];   
       }   
       mutation(j+1);   
       mutation(j+2);   
       /* 解码, 计算适应度 */   
       j = j + 2;   
     }   
   while(j < (popsize-1));   
   for(int i=1;i<=popsize;i++)   
       for(int j=1;j<=lchrom;j++)   
           individual[i][j]=Tindividual[i][j];   
    
 }   
 void generation1()   
 {   
   int mate1, mate2, j = 0;   
   /*  每代运算前进行预选 */   
   setFitness1();   
   preselect();   
   /* 选择, 交叉, 变异 */   
   do   
     {   
       /* 挑选交叉配对 */   
       mate1 = select();   
       mate2 = select();   
    
       /* 交叉和变异 */   
       crossover(mate1,mate2);   
       for(int g=1;g<=lchrom;g++)   
       {   
           Tindividual[j+1][g]=individual[j+1][g];   
           Tindividual[j+2][g]=individual[j+2][g];   
       }   
       mutation(j+1);   
       mutation(j+2);   
       /* 解码, 计算适应度 */   
       j = j + 2;   
     }   
   while(j < (popsize-1));   
   for(int i=1;i<=popsize;i++)   
       for(int j=1;j<=lchrom;j++)   
           individual[i][j]=Tindividual[i][j];   
    
 }   
    
 double randab(double a, double b)   
 {   
          
   double temp=((float)(rand()-rand())/32767*0.1);   
 if(temp<0) temp=temp*-1.0;   
   return temp;   
 }   
 void init()   
 {   
     srand((unsigned int)time((time_t *)NULL));   
     fin>>n;   
     fin>>o;   
     fin>>h;   
     fin>>e;   
     fin>>s;   
     fin>>a;   
     fin>>num;   
     W1=new double *[n+1];   
     for(int j=1;j<=n;j++)   
     {   
         W1[j]=new double[h+1];   
         for(int i=1;i<=h;i++)   
             W1[j][i]=randomperc();//randab(-1.0,1.0);   
     }   
     W2=new double *[h+1];   
     for(j=1;j<=h;j++)   
     {   
         W2[j]=new double[o+1];   
         for(int i=1;i<=o;i++)   
             W2[j][i]=randomperc();//randab(-1.0,1.0);   
     }   
     IHB=new double[h+1];   
     for(j=1;j<=h;j++)   
         IHB[j]=randomperc();//randab(-1.0,1.0);   
     HOB=new double[o+1];   
     for(j=1;j<=o;j++)   
         HOB[j]=randomperc();//randab(-1.0,1.0);   
        
     WChangei=new double *[n+1];   
     for(j=1;j<=n;j++)   
     {   
         WChangei[j]=new double[h+1];   
         for(int i=1;i<=h;i++)   
             WChangei[j][i]=0.0;   
     }   
     WChangeo=new double *[h+1];   
     for(j=1;j<=h;j++)   
     {   
         WChangeo[j]=new double[o+1];   
         for(int i=1;i<=o;i++)   
             WChangeo[j][i]=0.0;   
     }   
        
        
     DX3=new double[o+1];   
     for(j=1;j<=o;j++)   
         DX3[j]=0.0;   
     DX2=new double[h+1];   
     for(j=1;j<=h;j++)   
         DX2[j]=0.0;   
        
    
        
     XY1=new double[n+2];   
     XY2=new double[h+1];   
     XY3=new double[o+1];   
     X=new double *[num+1];   
     for(j=1;j<=num;j++)   
         X[j]=new double[n+2];   
     Y=new double*[num+1];   
     for(j=1;j<=num;j++)   
         Y[j]=new double[o+1];   
        
 }   
 void readXY()   
 {   
     for(int j=1;j<=num;j++)   
     {   
         for(int i=1;i<=n;i++)   
         {   
             fin>>X[j][i];   
         }   
         for(i=1;i<=o;i++)   
         fin>>Y[j][i];   
     }   
        
 }   
    
 void forward(int iSample)   
 {   
 //根据第iSample个样本，前向计算   
     int i,j;   
     double sum=0.0;   
    
     //输入层数据   
     for(i=1;i<=n;i++)   
         XY1[i]=X[iSample][i];   
        
     //隐层数据   
        
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=n;i++)               
             sum+=XY1[i]*W1[i][j];;   
            
         sum-=IHB[j];    
         XY2[j]=1.0/(1.0+exp(-sum));   
     }   
            
     //输出数据   
     for(j=1;j<=o;j++){   
         sum=0.0;   
         for(i=1;i<=h;i++)   
             sum+=XY2[i]*W2[i][j];   
         sum-=HOB[j];    
         XY3[j]=1.0/(1.0+exp(-sum));   
     }   
        
 }   
 void forward1(int g)   
 {   
 //根据第iSample个样本，前向计算   
     int i;   
     double sum=0.0;   
    
     //输入层数据   
     for(int j=1;j<=lchrom;j++)   
     {   
        
         XY1[j]=individual[g][j];   
    
     }   
     //隐层数据   
        
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=n;i++)               
             sum+=XY1[i]*W1[i][j];;   
            
         sum-=IHB[j];    
         XY2[j]=1.0/(1.0+exp(-sum));   
     }   
            
     //输出数据   
     for(j=1;j<=o;j++){   
         sum=0.0;   
         for(i=1;i<=h;i++)   
             sum+=XY2[i]*W2[i][j];   
         sum-=HOB[j];    
         XY3[j]=1.0/(1.0+exp(-sum));   
     }   
        
 }   
    
 void backward(int iSample)   
 {   
        
     int i,j;   
        
     //输出误差   
     for(i=1;i<=o;i++)   
         DX3[i]=XY3[i]*(1-XY3[i])*(Y[iSample][i]-XY3[i]);   
        
     //隐层误差   
     double sum=0.0;   
     for(j=1;j<=h;j++){   
         sum=0.0;   
         for(i=1;i<=o;i++)   
             sum+=DX3[i]*W2[j][i];   
         DX2[j]=XY2[j]*(1-XY2[j])*sum;   
     }   
     //更新隐层－输出权重   
        
     double dblChange;   
     for(j=1;j<=h;j++)   
         for(i=1;i<=o;i++){   
             dblChange=DX3[i]*XY2[j];   
             W2[j][i]=W2[j][i]+s*dblChange+a*WChangeo[j][i];   
             WChangeo[j][i]=dblChange;   
         }   
        
     //更新输入－隐层权重   
     for(i=1;i<=n;i++)   
         for(j=1;j<=h;j++){   
             dblChange=DX2[j]*XY1[i];   
             W1[i][j]=W1[i][j]+s*dblChange+a*WChangei[i][j];    
             WChangei[i][j]=dblChange;   
         }   
     //修改阙值   
     for(j=1;j<=o;j++)   
         HOB[j]-=s*DX3[j];     
     for(i=1;i<=h;i++)    
         IHB[i]-=s*DX2[i];    
     //计算误差   
     dblErr=0.0;   
     for(i=1;i<=o;i++)   
         dblErr+=0.5*(Y[iSample][i]-XY3[i])*(Y[iSample][i]-XY3[i]);   
        
 }   
    
 void learn()   
 {   
     int count=0;   
     double dblError=1.0;   
     int iSample=1;   
     double dblTotal;   
     while(dblError>e)   
     {   
         dblTotal=0.0;   
         for(iSample=1;iSample<=num;iSample++){   
             forward(iSample);   
             backward(iSample);   
             dblTotal+=dblErr;//总误差   
         }   
         if(dblTotal/dblError>1.04)   
         {//动态改变学习速率   
            s*=0.7;   
            
         }   
         else{   
            s*=1.05;   
         }   
         count++;   
         dblError=dblTotal;   
         ///////////显示训练数次和误差//////   
        
     }   
     cout<<count<<endl;   
 }   
    
    
    
 void getWBFormChrom()   
 {   
     for(int i=1;i<=n;i++)   
         for(int j=1;j<=h;j++)   
                 W1[i][j]=bestChrom[(i-1)*h+j];   
    
     for(i=1;i<=h;i++)   
         for(int j=1;j<=o;j++)   
                 W2[i][j]=bestChrom[n*h+(i-1)*o+j];   
     for(i=1;i<=h;i++)   
             IHB[i]=bestChrom[n*h+h*o+i];   
     for(i=1;i<=o;i++)   
             HOB[i]=bestChrom[n*h+h*o+h+i];   
    
 }   
    
    
 void main()   
 {   
    
    
         //思想：先用GA来训练神经网络，再用GA来求该网络的最优解!   
         randomize();   
         init();   
         readXY();   
         initPop();   
         for(int i=1;i<=maxgen;i++)   
             generation();   
         getWBFormChrom();   
         learn();   
         initPop1();   
         for(i=1;i<=1;i++)   
             generation1();   
    
            
    
 }    



  

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <math>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


long double Evm = -4.65*pow(10,-19);  // энергия активации вакансий
long double Eim = -1.38*pow(10,-20); // энергия активации SIA
int T=500; // температура

long double Esvv = -4.8*pow(10,-19); //энергия связи для вакансий
long double Esvi = -1.38*pow(10,-21); // энергия связи для SIA
long double w0= 1.0*pow(10,13); // частота дебая


long double dist = 2.35*pow(10,-10); //дистанция скачка
long double recomb = 4*pow(10,-10); // дистанция рекомбинации
long double kb = 1.380649*pow(10,-23); 

int p_conc=10; //радиус для расчета локальной концентрации


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
   n=100; // размер решетки
//   sum=pow(10,3);

   // инициализация структур
   (unsigned int *)matrix=(unsigned int *)new int[sizeof(int)*(2*n+1)];
   for(int i=0;i<2*n;i++) (unsigned int *)matrix[i]=(unsigned int *)new int[sizeof(int)*(2*n+1)];

   (unsigned int *)events=(unsigned int *)new int[sizeof(int)*(2*n+1)];
   for(int i=0;i<2*n;i++) (unsigned int *)events[i]=(unsigned int *)new int[sizeof(int)*(2*n+1)];
   for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++)(unsigned int *)events[i][j]=(unsigned int *)new int[sizeof(int)*(4)];

   for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++) matrix[i][j]=false;
   for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++) for(int k=0;k<4;k++) events[i][j][k]=0;
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::GetSIA(int x,int y)
{
    // возвращает наличие SIA в позиции
    int x1=2*x+1;
    int y1=2*y+1;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    return matrix[x1][y1];
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::GetEventSIA(int x,int y,int index)
{
    // возвращает частоту перехода для SIA в заданном направлении

    if(index<0 || index>3) return -1;
    int x1=2*x+1;
    int y1=2*y+1;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    return events[x1][y1][index];

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetSIA(int x,int y,bool Value)
{
    // устанавливает наличие/отсутствие SIA в позиции
    int x1=2*x+1;
    int y1=2*y+1;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    matrix[x1][y1]=Value;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::SetEventSIA(int x,int y,int index,long double Value)
{

    // устанавливает частоту перехода для SIA в заданном направлении

    if(index<0 || index>3) return;
    int x1=2*x+1;
    int y1=2*y+1;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    events[x1][y1][index]=Value;

}

//---------------------------------------------------------------------------

bool __fastcall TForm1::GetVAC(int x,int y)
{
    int x1=2*x;
    int y1=2*y;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    return matrix[x1][y1];
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::GetEventVAC(int x,int y,int index)
{

    if(index<0 || index>3) return -1;
    int x1=2*x;
    int y1=2*y;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    return events[x1][y1][index];

}

//---------------------------------------------------------------------------

void __fastcall TForm1::SetEventVAC(int x,int y,int index,long double Value)
{

    if(index<0 || index>3) return;
    int x1=2*x;
    int y1=2*y;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    events[x1][y1][index]=Value;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SetVAC(int x,int y,bool Value)
{
    int x1=2*x;
    int y1=2*y;
    if(x1<0) x1=x1+2*n;
    if(y1<0) y1=y1+2*n;

    if(x1>2*n-1) x1=x1-2*n;
    if(y1>2*n-1) y1=y1-2*n;

    matrix[x1][y1]=Value;
}

//---------------------------------------------------------------------------

bool __fastcall TForm1::GetNearVAC(int x,int y,int index)
{
  // возвращает ближайший SIA в заданном направлении
  if(index<0 || index>3) return true;
  switch(index)
  {
     case 0: return GetVAC(x+1,y);
     case 1: return GetVAC(x,y+1);
     case 2: return GetVAC(x-1,y);
     case 3: return GetVAC(x,y-1);
  }
  return true;
}
//---------------------------------------------------------------------------

long double __fastcall TForm1::GetConcSIAFull(int x,int y)
{
    // возвращает локальную концентрацию SIA в позиции
    int result=0;
    int n=p_conc;
    for(int i=-n;i<=n;i++)
    {
      for(int j=-n;j<=n;j++)
      {
         if(GetSIA(x+i,y+j)) result++;
      }
    }
    if(GetSIA(x,y) && result>0) result--;
    return (long double)(result)/((2*n+1)*(2*n+1)*1.0);
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::GetConcSIA(int x,int y,int index)
{
    // возвращает локальную концентрацию SIA в позиции в заданном направлении
    int result=0;
    int n=p_conc;
    switch(index)
    {
      case 0:
      {
        for(int i=0;i<=n;i++)
        {
          for(int j=-n;j<=n;j++)
          {
             if(GetSIA(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 1:
      {
        for(int i=-n;i<=n;i++)
        {
          for(int j=0;j<=n;j++)
          {
             if(GetSIA(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 2:
      {
        for(int i=-n;i<=0;i++)
        {
          for(int j=-n;j<=n;j++)
          {
             if(GetSIA(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 3:
      {
        for(int i=-n;i<=n;i++)
        {
          for(int j=-n;j<=0;j++)
          {
             if(GetSIA(x+i,y+j)) result++;
          }
        }
        break;
      }

    }
    if(GetSIA(x,y) && result>0) result--;
    return (long double)(result)/((2*n+1)*n+2*n);
}


//---------------------------------------------------------------------------

long double __fastcall TForm1::GetConcVACFull(int x,int y)
{
    int result=0;
    int n=p_conc;
    for(int i=-n;i<=n;i++)
    {
      for(int j=-n;j<=n;j++)
      {
         if(GetVAC(x+i,y+j)) result++;
      }
    }
    if(GetVAC(x,y) && result>0) result--;
    return (long double)(result)/((2*n+1)*(2*n+1)*1.0);
}


//---------------------------------------------------------------------------

long double __fastcall TForm1::GetConcVAC(int x,int y,int index)
{
    int result=0;
    int n=p_conc;

    switch(index)
    {
      case 0:
      {
        for(int i=0;i<=n;i++)
        {
          for(int j=-n;j<=n;j++)
          {
             if(GetVAC(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 1:
      {
        for(int i=-n;i<=n;i++)
        {
          for(int j=0;j<=n;j++)
          {
             if(GetVAC(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 2:
      {
        for(int i=-n;i<=0;i++)
        {
          for(int j=-n;j<=n;j++)
          {
             if(GetVAC(x+i,y+j)) result++;
          }
        }
        break;
      }
      case 3:
      {
        for(int i=-n;i<=n;i++)
        {
          for(int j=-n;j<=0;j++)
          {
             if(GetVAC(x+i,y+j)) result++;
          }
        }
        break;
      }

    }
/*    for(int i=-n;i<=n;i++)
    {
      for(int j=-n;j<=n;j++)
      {
         if(GetVAC(x+i,y+j)) result++;
      }
    }*/
    if(GetVAC(x,y) && result>0) result--;
    return (long double)(result)/((2*n+1)*n+2*n);
}
//---------------------------------------------------------------------------

bool __fastcall TForm1::GetNearSIA(int x,int y,int index)
{
  if(index<0 || index>3) return true;
  switch(index)
  {
     case 0: return GetSIA(x+1,y);
     case 1: return GetSIA(x,y+1);
     case 2: return GetSIA(x-1,y);
     case 3: return GetSIA(x,y-1);
  }
  return true;
}


//---------------------------------------------------------------------------

void __fastcall TForm1::CalculateRatesVAC(int x,int y)
{
   // пересчитывает частоты переходов вакансий в заданной позиции
    if(!GetVAC(x,y))
   {
      for(int i=0;i<4;i++)
      {
         SetEventVAC(x,y,i,0);
         switch(i)
         {
            case 0: if(GetVAC(x+1,y)) SetEventVAC(x+1,y,i^2,CalculateRateVAC(x+1,y,i^2)); else SetEventVAC(x+1,y,i^2,0); break;
            case 1: if(GetVAC(x,y+1)) SetEventVAC(x,y+1,i^2,CalculateRateVAC(x,y+1,i^2)); else SetEventVAC(x,y+1,i^2,0); break;
            case 2: if(GetVAC(x-1,y)) SetEventVAC(x-1,y,i^2,CalculateRateVAC(x-1,y,i^2)); else SetEventVAC(x-1,y,i^2,0); break;
            case 3: if(GetVAC(x,y-1)) SetEventVAC(x,y-1,i^2,CalculateRateVAC(x,y-1,i^2)); else SetEventVAC(x,y-1,i^2,0); break;
         }
      }

   } else
   {
     for(int i=0;i<4;i++)
     {
        if(GetNearVAC(x,y,i))
        {
           SetEventVAC(x,y,i,0);
           switch(i)
           {
              case 0: SetEventVAC(x+1,y,i^2,0); break;
              case 1: SetEventVAC(x,y+1,i^2,0); break;
              case 2: SetEventVAC(x-1,y,i^2,0); break;
              case 3: SetEventVAC(x,y-1,i^2,0); break;
           }
        }
        else SetEventVAC(x,y,i,CalculateRateVAC(x,y,i));
     }
   }
}

//---------------------------------------------------------------------------

int __fastcall TForm1::RecombinationStep(int x,int y,int dx,int dy)
{
         // выполняет рекомбинацию дефектов на заданном расстоянии для позиции
         int Result=0;
         if(GetSIA(x+dx,y+dy) && GetVAC(x,y))
         {
           SetVAC(x,y,false);
           SetSIA(x+dx,y+dy,false);
           CalculateRatesVAC(x,y);
           CalculateRatesSIA(x+dx,y+dy);
           Result++;
         } else
         {
           if(GetVAC(x+dx,y+dy) && GetSIA(x,y))
           {
             SetSIA(x,y,false);
             SetVAC(x+dx,y+dy,false);
             CalculateRatesSIA(x,y);
             CalculateRatesVAC(x+dx,y+dy);
             Result++;
           }
         }
         return Result;
}

//---------------------------------------------------------------------------

int __fastcall TForm1::RecombinationVACSIA(int x,int y)
{
   //выполняет рекомбинацию дефектов для dist и recomb
   int index=ceil(recomb/(dist*sqrt(2)));
//   RecombinationStep(x,y,0,0);

   int Result=0;
//   int index=floor(recomb/(dist*sqrt(2)));
   for(int i=0;i<index;i++)
   {
       Result+=RecombinationStep(x,y,i,0);
       Result+=RecombinationStep(x,y,0,i);
       Result+=RecombinationStep(x,y,-i,0);
       Result+=RecombinationStep(x,y,0,-i);
       Result+=RecombinationStep(x,y,i,i);
       Result+=RecombinationStep(x,y,-i,-i);
       Result+=RecombinationStep(x,y,-i,i);
       Result+=RecombinationStep(x,y,i,-i);
   }
   return Result;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::CalculateRatesSIA(int x,int y)
{
   // пересчитывает частоты переходов SIA в заданной позиции

   if(!GetSIA(x,y))
   {
      for(int i=0;i<4;i++)
      {
         SetEventSIA(x,y,i,0);
         switch(i)
         {
            case 0: if(GetSIA(x+1,y)) SetEventSIA(x+1,y,i^2,CalculateRateSIA(x+1,y,i^2)); else SetEventSIA(x+1,y,i^2,0); break;
            case 1: if(GetSIA(x,y+1)) SetEventSIA(x,y+1,i^2,CalculateRateSIA(x,y+1,i^2)); else SetEventSIA(x,y+1,i^2,0); break;
            case 2: if(GetSIA(x-1,y)) SetEventSIA(x-1,y,i^2,CalculateRateSIA(x-1,y,i^2)); else SetEventSIA(x-1,y,i^2,0); break;
            case 3: if(GetSIA(x,y-1)) SetEventSIA(x,y-1,i^2,CalculateRateSIA(x,y-1,i^2)); else SetEventSIA(x,y-1,i^2,0); break;
         }

      }

   } else
   {
     for(int i=0;i<4;i++)
     {
        if(GetNearSIA(x,y,i))
        {
           SetEventSIA(x,y,i,0);
           switch(i)
           {
              case 0: SetEventSIA(x+1,y,i^2,0); break;
              case 1: SetEventSIA(x,y+1,i^2,0); break;
              case 2: SetEventSIA(x-1,y,i^2,0); break;
              case 3: SetEventSIA(x,y-1,i^2,0); break;
           }
        } else SetEventSIA(x,y,i,CalculateRateSIA(x,y,i));
     }
   }
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::CalculateMuVAC(int x,int y)
{

// вычисляет химический потенциал для вакансий
   long double up,down,right,left;

   right=GetConcVACFull(x+1,y);
   up=GetConcVACFull(x,y+1);
   left=GetConcVACFull(x-1,y);
   down=GetConcVACFull(x,y-1);


   long double ph=GetConcVACFull(x,y);
   long double b=1;
   long double a=0.5;
   long double dst=1;
   return 2*b*(-3*pow(ph,2)+ph+2*pow(ph,3))-(a/(dst*dst))*(up+down+right+left-4*ph);


   //return b*(-ph+pow(ph,3))-(a/(dst*dst))*(up+down+right+left-4*ph);
   //return 3*b*pow(10,-19)*(1-2*ph)+1.38*b*pow(10,-23)*T*(log(ph)-log(1-ph))+(a/(dst*dst))*(up+down+right+left-4*ph);
   //return 32*(-3*b*pow(ph,2)+b*ph+2*b*pow(ph,3))-(a/(dst*dst))*(up+down+right+left-4*ph);
   //return -b*pow(ph,2)+b*ph+b*pow(ph,3)+(a/(dst*dst))*(up+down+right+left-4*ph);


}

//---------------------------------------------------------------------------

long double __fastcall TForm1::CalculateEnergyVAC(int x,int y)
{
// вычисляет изменеие концентрации вакансий в заданной позиции по кан-хилларду
   long double up,down,right,left;
   long double dup,ddown,dright,dleft;
   long double dirxl,dirxr,diryu,diryd;
   dirxl=0;
   dirxr=0;
   diryu=0;
   diryd=0;

   right=CalculateMuVAC(x+1,y);
   up=CalculateMuVAC(x,y+1);
   left=CalculateMuVAC(x-1,y);
   down=CalculateMuVAC(x,y-1);
   long double mu=CalculateMuVAC(x,y);
   long double dst=1;

   dright=dirxr*(right-mu)/dst;
   dleft=dirxl*(mu-left)/dst;
   dup=diryu*(up-mu)/dst;
   ddown=diryd*(mu-down)/dst;

   long double diver=(dright-dleft)/(2*dst)+(dup-ddown)/(2*dst);



   long double tm=1.0*pow(10,-15);
   //long double a=1/sum;
//   long double sum=GetSumEvents();
   //return GetConcVACFull(x,y)+(tm/(dst*dst))*(up+down+right+left-4*mu);
   //return GetConcVACFull(x,y)+tm*diver;
   return tm*diver;
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::CalculateEnergySIA(int x,int y)
{
// вычисляет изменеие концентрации SIA в заданной позиции по кан-хилларду
   long double up,down,right,left;
   long double dup,ddown,dright,dleft;
   long double dirxl,dirxr,diryu,diryd;
   dirxl=0;
   dirxr=0;
   diryu=0;
   diryd=0;


   right=GetConcSIAFull(x+1,y);
   up=GetConcSIAFull(x,y+1);
   left=GetConcSIAFull(x-1,y);
   down=GetConcSIAFull(x,y-1);
   long double ttt1=GetConcSIAFull(x,y);
   long double dst=1.0;

   dright=dirxr*(right-ttt1)/dst;
   dleft=dirxl*(ttt1-left)/dst;
   dup=diryu*(up-ttt1)/dst;
   ddown=diryd*(ttt1-down)/dst;

   long double diver=(dright-dleft)/(2*dst)+(dup-ddown)/(2*dst);

   //long double ttt1=(GetConcSIA(x,y,0)+GetConcSIA(x,y,1)+GetConcSIA(x,y,2)+GetConcSIA(x,y,3))/3;
   //ttt1=1*GetSIA(x,y)/9;
   long double tm=1.0*pow(10,-15);
//   long double KoeffDiff=1;
//   long double sum=GetSumEvents();
//   return GetConcSIAFull(x,y)+tm*(up+down+right+left-4*ttt1)/(dst*dst);
   //return GetConcSIAFull(x,y)+tm*diver;
     return tm*diver;
//   return diver;
//   return KoeffDiff*(up-down+right-left)/dst;


}

//---------------------------------------------------------------------------

long double __fastcall TForm1::CalculateRateVAC(int x,int y,int index)
{

  //вычисляет частоту перехода в заданном направлении для вакансий 
  long double Result;
  int x1;
  int y1;
  long double direct;
  switch(index)
  {
     case 0: x1=x+1; y1=y; direct=1; break;
     case 1: x1=x; y1=y+1; direct=1; break;
     case 2: x1=x-1; y1=y; direct=1; break;
     case 3: x1=x; y1=y-1; direct=1; break;
  }

  long double E2=GetConcVACFull(x1,y1)+CalculateEnergyVAC(x1,y1);
  long double E1=GetConcVACFull(x,y)+CalculateEnergyVAC(x,y);

  //Result=w0*direct*(exp(Evm/(kb*T)-(Esvv/(kb*T))*((2*p_conc+1)*(2*p_conc+1)/2.0)*(E2-E1)));
  Result=w0*direct*(exp(-(Esvv/(kb*T))*((2*p_conc+1)*(2*p_conc+1)/100.0)*(E2-E1)));
  return Result;
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::CalculateRateSIA(int x,int y,int index)
{

  //вычисляет частоту перехода в заданном направлении для SIA
  long double Result;
  int x1;
  int y1;
  long double direct;

  switch(index)
  {
     case 0: x1=x+1;y1=y;direct=1; break;
     case 1: x1=x;y1=y+1;direct=1; break;
     case 2: x1=x-1;y1=y;direct=1; break;
     case 3: x1=x;y1=y-1;direct=1; break;
  }

  long double E2=GetConcSIAFull(x1,y1)+CalculateEnergySIA(x1,y1);
  long double E1=GetConcSIAFull(x,y)+CalculateEnergySIA(x,y);


  Result=w0*direct*(exp(-(Esvv/(kb*T))*((2*p_conc+1)*(2*p_conc+1)/100.0)*(E2-E1)));
  return Result;

}


//---------------------------------------------------------------------------

void __fastcall TForm1::RunHopVAC(int x,int y,int index)
{
  //совершает скачок вакансии в заданном направлении
   int x1;
   int y1;
   if(GetVAC(x,y))
   {
      SetVAC(x,y,false);
      switch(index)
      {
         case 0: { x1=x+1; y1=y; break; }
         case 1: { x1=x; y1=y+1; break; }
         case 2: { x1=x-1; y1=y; break; }
         case 3: { x1=x; y1=y-1; break; }
      }
      if(!GetVAC(x1,y1))
      {
        SetVAC(x1,y1,true);
        CalculateRatesVAC(x,y);
        CalculateRatesVAC(x1,y1);
      }
   }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::RunHopSIA(int x,int y,int index)
{
//совершает скачок SIA в заданном направлении
   int x1;
   int y1;
   if(GetSIA(x,y))
   {
      SetSIA(x,y,false);
      switch(index)
      {
         case 0: { x1=x+1; y1=y; break; }
         case 1: { x1=x; y1=y+1; break; }
         case 2: { x1=x-1; y1=y; break; }
         case 3: { x1=x; y1=y-1; break; }
      }
      if(!GetSIA(x1,y1))
      {
        SetSIA(x1,y1,true);
        CalculateRatesSIA(x,y);
        CalculateRatesSIA(x1,y1);
      }
   }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DrawSIA(int x,int y)
{
//отрисовка SIA в заданной позиции
    int scal=Panel1->Height/(2*n);
    int gx=(2*x+1)*scal;
    int gy=Panel1->Height-(2*y+1)*scal;
    if(GetSIA(x,y))
    {
       Image1->Canvas->Brush->Color = clRed;
       Image1->Canvas->Ellipse(gx-4,gy-4,gx+4,gy+4);
    } else
    {
       Image1->Canvas->Pen->Color=clWhite;
       Image1->Canvas->Brush->Color = clWhite;
       Image1->Canvas->Rectangle(gx-4,gy-4,gx+4,gy+4);
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GenerateOneDefect(void)
{
//генерация одного дефекта френкеля
    int l=0;
    while(l<1)
    {
       int k=random(n*n);
       int y=int((long double)(k)/(long double)(n));
       int x=k-y*n;
       if(GetSIA(x,y)) continue;
       else
       {
          SetSIA(x,y,true);
          CalculateRatesSIA(x,y);
          l++;
       }
    }
    l=0;
    while(l<1)
    {
       int k=random(n*n);
       int y=int((long double)(k)/(long double)(n));
       int x=k-y*n;
       if(GetVAC(x,y)) continue;
       else
       {
          SetVAC(x,y,true);
          CalculateRatesVAC(x,y);
          l++;
       }
    }
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::GetSumEventsSIA(void)
{
//получить сумму частот для SIA
    long double sum=0;
    for(int x=0;x<n;x++)
      for(int y=0;y<n;y++)
        for(int k=0;k<4;k++)
        {
          sum+=GetEventSIA(x,y,k);
        }
    return sum;
}

//---------------------------------------------------------------------------

long double __fastcall TForm1::GetSumEventsVAC(void)
{
//получить сумму частот для вакансий
    long double sum=0;
    for(int x=0;x<n;x++)
      for(int y=0;y<n;y++)
        for(int k=0;k<4;k++)
        {
          sum+=GetEventVAC(x,y,k);
        }
    return sum;
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GetEventUpBelowSIA(long double sum,CurrentHop &ch)
{
  long double factor=random(100000)*1.0/(100000*1.0);
  long double por=sum*factor;
  long double det_sum=0;
  ch.x=ch.y=ch.direct=ch.type=0;
  bool flag=false;
  for(int x=n-1;x>=0;x--)
  {
    for(int y=n-1;y>=0;y--)
    {
      for(int k=3;k>=0;k--)
      {
        det_sum+=GetEventSIA(x,y,k);
        if(det_sum>por)
        {
           ch.x=x;
           ch.y=y;
           ch.direct=k;
           ch.type=1;
           flag=true;
           break;
        }
      }
      if(flag) break;
    }
    if(flag) break;
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GetEventUpBelow(long double sum,CurrentHop &ch)
{
//получить событие перехода ближайшее меньшее к порогу по сумме
  long double factor=random(100000)*1.0/(100000*1.0);
  long double por=sum*factor;
  long double det_sum=0;
  ch.x=ch.y=ch.direct=ch.type=0;
  bool flag=false;
  for(int x=n-1;x>=0;x--)
  {
    for(int y=n-1;y>=0;y--)
    {
      for(int k=3;k>=0;k--)
      {
        det_sum+=GetEventSIA(x,y,k);
        if(det_sum>por)
        {
           ch.x=x;
           ch.y=y;
           ch.direct=k;
           ch.type=1;
           flag=true;
           break;
        }
        det_sum+=GetEventVAC(x,y,k);
        if(det_sum>por)
        {
           ch.x=x;
           ch.y=y;
           ch.direct=k;
           ch.type=2;
           flag=true;
           break;
        }
      }
      if(flag) break;
    }
    if(flag) break;
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::GetEventUpBelowVAC(long double sum,CurrentHop &ch)
{
  long double factor=random(100000)*1.0/(100000*1.0);
  long double por=sum*factor;
  long double det_sum=0;
  ch.x=ch.y=ch.direct=ch.type=0;
  bool flag=false;
  for(int x=n-1;x>=0;x--)
  {
    for(int y=n-1;y>=0;y--)
    {
      for(int k=3;k>=0;k--)
      {
        det_sum+=GetEventVAC(x,y,k);
        if(det_sum>por)
        {
           ch.x=x;
           ch.y=y;
           ch.direct=k;
           ch.type=2;
           flag=true;
           break;
        }
      }
      if(flag) break;
    }
    if(flag) break;
  }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DrawVAC(int x,int y)
{
//отрисовка вакансии в заданной позиции
    int scal=Panel1->Height/(2*n);
    int gx=(2*x)*scal;
    int gy=Panel1->Height-(2*y)*scal;
    if(GetVAC(x,y))
    {
       Image1->Canvas->Brush->Color = clBlue;
       Image1->Canvas->Ellipse(gx-4,gy-4,gx+4,gy+4);
    } else
    {
       Image1->Canvas->Pen->Color=clWhite;
       Image1->Canvas->Brush->Color = clWhite;
       Image1->Canvas->Rectangle(gx-4,gy-4,gx+4,gy+4);
    }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DrawAllVAC(void)
{
//отрисовка вакансий
   for(int x=0;x<n;x++) for(int y=0;y<n;y++) DrawVAC(x,y);
}

//---------------------------------------------------------------------------

void __fastcall TForm1::DrawAllSIA(void)
{
//отрисовка SIA
   for(int x=0;x<n;x++) for(int y=0;y<n;y++) DrawSIA(x,y);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
// основной цикл обработки
  int cnt=int(n*n*1/100);
// генерация 1% дефектов случайным образом
  randomize();
  int l=0;
  for(int i=0;i<cnt;i++) GenerateOneDefect();

// выполняется рекомбинация после генерации
  for(int x=0;x<n;x++)
    for(int y=0;y<n;y++)
    {
       RecombinationVACSIA(x,y);
    }
//  отрисовка;
  DrawAllVAC();

  for(int j=0;j<1000000;j++)
  {

    int Res=0;
// выполняется рекомбинация после генерации
    for(int x=0;x<n;x++) for(int y=0;y<n;y++) Res+=RecombinationVACSIA(x,y);

//===============================================================
    //выполняется генерация дефекта на каждом деятом шаге алгоритма
    if(!(j%10)) GenerateOneDefect();
//===============================================================

//получаем суммы частот всех переходов

    sum_s=GetSumEventsSIA();
    sum_v=GetSumEventsVAC();

//получаем необходимый нам переход
    CurrentHop ch;
    GetEventUpBelow(sum_s+sum_v,ch);

// выполняем переход
    switch(ch.type)
    {
       case 1: RunHopSIA(ch.x,ch.y,ch.direct); break;
       case 2: RunHopVAC(ch.x,ch.y,ch.direct); break;
    }
// отрисовка на каждом 1000-ном шаге
    if(!(j%1000))
    {
      DrawAllVAC();
      Application->ProcessMessages();
    }
  }
  ShowMessage("Ok");
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

typedef struct {
  int count_hop;
  bool busy;
} VPoint;

typedef struct {
  int x;
  int y;
  int direct;
  int type;
} CurrentHop;

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TPanel *Panel1;
        TImage *Image1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int n;
        bool **matrix;
        long double ***events;
        bool __fastcall GetVAC(int x,int y);
        bool __fastcall GetSIA(int x,int y);
        long double __fastcall GetEventSIA(int x,int y,int index);
        void __fastcall SetEventSIA(int x,int y,int index,long double Value);
        void __fastcall SetVAC(int x,int y,bool Value);
        long double __fastcall GetEventVAC(int x,int y,int index);
        void __fastcall SetEventVAC(int x,int y,int index,long double Value);
        void __fastcall SetSIA(int x,int y,bool Value);
        bool __fastcall GetNearSIA(int x,int y,int index);
        bool __fastcall GetNearVAC(int x,int y,int index);
        long double __fastcall GetConcSIA(int x,int y,int index);
        long double __fastcall GetConcSIAFull(int x,int y);
        long double __fastcall GetConcVAC(int x,int y,int index);
        long double __fastcall GetConcVACFull(int x,int y);
        int __fastcall RecombinationStep(int x,int y,int dx,int dy);
        void __fastcall CalculateRatesVAC(int x,int y);
        long double __fastcall CalculateRateVAC(int x,int y,int index);
        long double __fastcall CalculateRateSIA(int x,int y,int index);
        void __fastcall CalculateRatesSIA(int x,int y);
        int __fastcall RecombinationVACSIA(int x,int y);
        long double __fastcall CalculateMuVAC(int x,int y);
        long double __fastcall CalculateEnergySIA(int x,int y);
        long double __fastcall CalculateEnergyVAC(int x,int y);
        void __fastcall GenerateOneDefect(void);
        long double __fastcall GetSumEventsSIA(void);
        long double __fastcall GetSumEventsVAC(void);
        void __fastcall GetEventUpBelowSIA(long double sum,CurrentHop &ch);
        void __fastcall GetEventUpBelowVAC(long double sum,CurrentHop &ch);
        void __fastcall GetEventUpBelow(long double sum,CurrentHop &ch);

        void __fastcall DrawSIA(int x,int y);
        void __fastcall DrawVAC(int x,int y);
        void __fastcall DrawAllVAC(void);
        void __fastcall DrawAllSIA(void);

        void __fastcall RunHopVAC(int x,int y,int index);
        void __fastcall RunHopSIA(int x,int y,int index);

        long double sum_s,sum_v;

        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ReportADODataSet.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TReportADODataSet *)
{
        new TReportADODataSet(NULL);
}
//---------------------------------------------------------------------------
__fastcall TReportADODataSet::TReportADODataSet(TComponent* Owner)
        : TADODataSet(Owner)
{
  FADOConnection= new TADOConnection(this);
  FADOConnection->LoginPrompt= false;
  FADOQuery= new TADOQuery(this);
  FADOQuery->Connection= FADOConnection;
}
//---------------------------------------------------------------------------
__fastcall TReportADODataSet::~TReportADODataSet()
{
  FADOQuery->Free();
  FADOConnection->Free();
}
//---------------------------------------------------------------------------
AnsiString __fastcall TReportADODataSet::GetHTMLCode()
{
  AnsiString HTMLCode;
  return HTMLCode;
}
//---------------------------------------------------------------------------
namespace Reportadodataset
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TReportADODataSet)};
                 RegisterComponents("Samples", classes, 0);
        }
}
//---------------------------------------------------------------------------
 
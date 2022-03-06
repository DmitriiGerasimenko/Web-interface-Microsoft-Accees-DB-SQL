//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ADOOpenDatabase.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//

static inline void ValidCtrCheck(TADOOpenDatabase *)
{
        new TADOOpenDatabase(NULL);
}
//---------------------------------------------------------------------------
__fastcall TADOOpenDatabase::TADOOpenDatabase(TComponent* Owner)
        : TADOQuery(Owner)
{
  FADOConnection= new TADOConnection(this);
  FADOConnection->LoginPrompt= false;
  TADOQuery::Connection= FADOConnection;
  FDatabaseFileName="";
  FSQL="";
}
//---------------------------------------------------------------------------
__fastcall TADOOpenDatabase::~TADOOpenDatabase()
{
  FADOConnection->Free();
}
//---------------------------------------------------------------------------
namespace Adoopendatabase
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TADOOpenDatabase)};
                 RegisterComponents("Samples", classes, 0);
        }
}
//---------------------------------------------------------------------------
void __fastcall TADOOpenDatabase::SetDatabaseFileName(TFileName FileName)
{
  if(FDatabaseFileName != FileName)
  {
        FDatabaseFileName= FileName;;
        AnsiString ConnectionString, ConnectionFormat=
                "Provider=MSDataShape.1;"
                "Persist Security Info=True;"
                "Data Source=%s;"
                "Data Provider=Microsoft.Jet.OLEDB.4.0";
        ConnectionString.sprintf(ConnectionFormat.c_str(), FDatabaseFileName.c_str());
        FADOConnection->Connected= false;
        FADOConnection->ConnectionString= ConnectionString;
        FADOConnection->Connected = true;
  }
}
//---------------------------------------------------------------------------
void __fastcall TADOOpenDatabase::SetSQL(AnsiString SQLString)
{
  if (FSQL != SQLString) {FSQL= SQLString;}
}
//---------------------------------------------------------------------------
void __fastcall TADOOpenDatabase::Open()
{
  TADOQuery::Close();
  TADOQuery::SQL->Clear();
  TADOQuery::SQL->Add(FSQL);
  TADOQuery::Open();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

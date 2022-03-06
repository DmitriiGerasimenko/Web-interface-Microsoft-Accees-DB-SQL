//---------------------------------------------------------------------------

#ifndef ADOOpenDatabaseH
#define ADOOpenDatabaseH
//---------------------------------------------------------------------------
#include <ADODB.hpp>
//#include <Db.hpp>
#include <vector>

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif
//---------------------------------------------------------------------------
typedef std::vector<double, std::allocator<double> >  TDoubleVector;
typedef std::vector<double, std::allocator<double> >::iterator TDoubleVectorIterator;
//---------------------------------------------------------------------------
class PACKAGE TADOOpenDatabase : public TADOQuery
{
private:
        TDoubleVector  *FDoubleVector;
        TADOConnection *FADOConnection;
        AnsiString FDatabaseFileName;
        AnsiString FSQL;
protected:
        void __fastcall SetDatabaseFileName(TFileName FileName);
        void __fastcall SetSQL(AnsiString SQLString);
public:
        void __fastcall Open();
public:
        __fastcall TADOOpenDatabase(TComponent* Owner);
        __fastcall virtual ~TADOOpenDatabase(void);
__published:
	__property AnsiString DatabaseFileName= {read=FDatabaseFileName, write=SetDatabaseFileName};
	__property AnsiString SQL= {read=FSQL, write=SetSQL};
};
//---------------------------------------------------------------------------
#endif

//---------------------------------------------------------------------------

#ifndef ReportADODataSetH
#define ReportADODataSetH
//---------------------------------------------------------------------------
#include <ADODB.hpp>
#include <Db.hpp>
#include <vector>

#ifndef _RWSTD_NO_NAMESPACE
using namespace std;
#endif
//---------------------------------------------------------------------------
typedef std::vector<double, std::allocator<double> >  TDoubleVector;
typedef std::vector<double, std::allocator<double> >::iterator TDoubleVectorIterator;
//---------------------------------------------------------------------------
class PACKAGE TReportADODataSet : public TADODataSet
{
private:
        TDoubleVector  *FDoubleVector;
        TADOConnection *FADOConnection;
        TADOQuery      *FADOQuery;
protected:
        AnsiString __fastcall GetHTMLCode();
public:
        __fastcall TReportADODataSet(TComponent* Owner);
        __fastcall virtual ~TReportADODataSet(void);
__published:
        __property AnsiString HTMLCode= {read=GetHTMLCode};
};
//---------------------------------------------------------------------------
#endif

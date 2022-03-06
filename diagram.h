//---------------------------------------------------------------------------
#ifndef DataSetJpgH
#define DataSetJpgH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <ADOdb.hpp>
#include <JPeg.hpp>
#include <algorithm>    /*  for max()   */
#include <printers.hpp>
#include <set>

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

//typedef std::set<std::string, std::allocator<std::string> >  TSetString;
typedef std::set<TPen*, std::less<TPen*>, std::allocator<TPen*> > TSetTPen;
typedef std::set<TPen*, std::less<TPen*>, std::allocator<TPen*> >::iterator TSetIteratorTPen;

typedef std::set<TPenStyle, std::less<TPenStyle>, std::allocator<TPenStyle> > TSetTPenStyle;
typedef std::set<TPenStyle, std::less<TPenStyle>, std::allocator<TPenStyle> >::iterator TSetIteratorTPenStyle;

namespace Datasetjpg
{
        void __fastcall PACKAGE Register();
}
//...
PChar search_token_dt(PChar t, WORD &i);
void __fastcall AnsiStringToSystemTime(const AnsiString &String, _SYSTEMTIME &SystemTime);
AnsiString __fastcall SystemTimeToAnsiString(_SYSTEMTIME &SystemTime);
//double __fastcall SystemTimeToDouble(_SYSTEMTIME &SystemTime);
void Rotate(Graphics::TBitmap* Bitmap);
//---------------------------------------------------------------------------
enum TDiagramSizeStyle {wsRecordCount, wsDateTime, wsFixed };
//---------------------------------------------------------------------------
class PACKAGE TDBDiagram : public TComponent
{
private:
        int FHeight;
        int FWidth;

        int FMaxHeight;
        int FMinHeight;
        int FMaxWidth;
        int FMinWidth;
        //-------------------------------------------------------------------
        TRect  rInformation;
        TRect  rDiagramNames;
        TRect  rDiagramNumeric;
        TRect  rTop;
        TRect  rBottom;
        TRect  rLeft;
        TRect  rRight;
        TRect  rCenter;
        TRect  rCopiright;
        int    FReserve;
        AnsiString FFormatString;

        TColor FBackgroundInformation;
        TColor FBackgroundDiagramNames;
        TColor FBackgroundDiagramNumeric;
        TColor FBackgroundDiagramNumericLabel;
        TColor FBackgroundLeft;
        TColor FBackgroundRight;
        TColor FBackgroundTop;
        TColor FBackgroundBottom;
        TColor FBackgroundGraph;
        TColor FBackgroundPen;
        TColor FBackgroundCopyright;

        TColor FForegroundInformation;
        TColor FForegroundDiagramNames;
        TColor FForegroundDiagramNumeric;
        TColor FForegroundDiagramNumericLabel;
        TColor FForegroundLeft;
        TColor FForegroundRight;
        TColor FForegroundTop;
        TColor FForegroundBottom;
        TColor FForegroundGraph;
        TColor FForegroundPen;
        TColor FForegroundBorder;
        TColor FForegroundCopyright;

        TSetTPen FSetTPen;
        int FPenWidth;
        int FDiagramaNumericPenWidth;

        TDiagramSizeStyle FWidthStyle;
        TDiagramSizeStyle FHeightStyle;

        int FPixelsInData;
        int FInformationTextSize;
        int FRangeTextSize;
        int FDateTimeTextSize;
//        int FTablesCount; // Количество графиков на диаграмме.

        TFont* FFontInformation;
        TFont* FFontDiagramNames;
        TFont* FFontDiagramNumeric;
        TFont* FFontDateTime;
        TFont* FFontRange;
        //-------------------------------------------------------------------
        TStringList* FListInformationText;
        Graphics::TBitmap *Graph;

        TADOConnection* FADOConnection;
        TADOQuery* FADOQuery;

//        TStringList* FTables;
        TStringList* FTableNames;

        AnsiString FDatabaseName;
        AnsiString FSQL;

        AnsiString FCopyrightInfo;
        bool FVisibleBorder;

        // System::TDateTime FFrom;
        // System::TDateTime FTo;
        SYSTEMTIME from, to;

        double FMax;
        double FMin;
        bool FAutoMax;
        bool FAutoMin;

        //-----------------------------------------------------------
	void       __fastcall SetDatabaseName(AnsiString DatabaseName);
	AnsiString __fastcall GetDatabaseName();

	void __fastcall SetTableName(AnsiString DatabaseName);
        void __fastcall SetDataSQLFile(AnsiString String);

	void __fastcall SetFrom(AnsiString String);
	void __fastcall SetTo(AnsiString String);

	AnsiString __fastcall GetFrom();
	AnsiString __fastcall GetTo();

        /*
	void __fastcall SetFrom(TDateTime Value);
	void __fastcall SetTo(TDateTime Value);
	TDateTime __fastcall GetFrom();
	TDateTime __fastcall GetTo();
        */

//        void __fastcall SetWidth(int iWidth);
//        void __fastcall SetHeight(int iHeight);
//        int __fastcall GetWidth();
//        int __fastcall GetHeight();

        void __fastcall SetMax(double Value);
        void __fastcall SetMin(double Value);

        void __fastcall SetAutoRange(Boolean bValue);
        void __fastcall SetAutoTo(Boolean bValue);

        void __fastcall SetGraphName(AnsiString String);
        void __fastcall SetGraphPenWidth(int Value);
private:
        void __fastcall MemoryInformation(const AnsiString Block,
                                        bool VisibleMessage);
        void __fastcall RequestRange();
        void __fastcall Request();

//        AnsiString __fastcall CreateSQLReguest1();

        TColor __fastcall GetNextColor(BOOL state);

        double __fastcall GetMin();
        double __fastcall GetMax();
        //-----------------------------------------------------------
        void __fastcall SetAutoMax(bool Value);
        void __fastcall SetAutoMin(bool Value);
        //-----------------------------------------------------------
        int __fastcall GetInformationTextHeight();
        int __fastcall GetInformationTextWidth();
        int __fastcall GetDiagramNamesTextHeight();
        int __fastcall GetDiagramNamesTextWidth();
        int __fastcall GetDiagramNumericTextHeight();
        int __fastcall GetDiagramNumericTextWidth();
        int __fastcall GetRangeTextHeight();
        int __fastcall GetRangeTextWidth();
        int __fastcall GetDateTimeTextHeight();
        int __fastcall GetDateTimeTextWidth();
        //-----------------------------------------------------------
        void __fastcall SetBackgroundInformation(TColor Color);
        void __fastcall SetBackgroundLeft(TColor Color);
        void __fastcall SetBackgroundRight(TColor Color);
        void __fastcall SetBackgroundTop(TColor Color);
        void __fastcall SetBackgroundBottom(TColor Color);
        void __fastcall SetBackgroundGraph(TColor Color);
        void __fastcall SetBackgroundPen(TColor Color);
        void __fastcall SetBackgroundBorder(TColor Color);

        void __fastcall SetForegroundInformation(TColor Color);
        void __fastcall SetForegroundLeft(TColor Color);
        void __fastcall SetForegroundRight(TColor Color);
        void __fastcall SetForegroundTop(TColor Color);
        void __fastcall SetForegroundBottom(TColor Color);
        void __fastcall SetForegroundGraph(TColor Color);
        void __fastcall SetForegroundPen(TColor Color);
        void __fastcall SetForegroundBorder(TColor Color);

        void __fastcall SetCopyrightInfo(AnsiString Str);
        void __fastcall SetVisibleBorder(bool Bool);
        //-----------------------------------------------------------
        void __fastcall SetPenWidth(int Value);
        //-----------------------------------------------------------
        void __fastcall SetHeightStyle(TDiagramSizeStyle Style);

        void __fastcall Resize(TDiagramSizeStyle DiagramSizeStyle);

//        void __fastcall ResizeWidth(TDiagramSizeStyle DiagramSizeStyle);
//        void __fastcall ResizeHeight(TDiagramSizeStyle DiagramSizeStyle);

        void __fastcall DoPaintBorder(TCanvas *Cvs);
        void __fastcall DoPaintBackground(TCanvas *Cvs);
        void __fastcall DoPaintInformation(TCanvas *Cvs);
        void __fastcall DoPaintDiagramNames(TCanvas *Cvs);
        void __fastcall DoPaintDiagramNumeric(TCanvas *Cvs);
        void __fastcall DoPaintRange(TCanvas *Cvs);
        void __fastcall DoPaintDateTime(TCanvas *Cvs);
        void __fastcall DoPaintGraph(TCanvas *Cvs);
        void __fastcall DoPaint(TCanvas *Cvs);

        AnsiString __fastcall ReadFile(AnsiString FileName);

protected:
public:
        AnsiString __fastcall SaveToFile(AnsiString ImagePath);
        void __fastcall SaveToStream(TMemoryStream* Stream);
        void __fastcall Print();
//        AnsiString __fastcall CreateSQLReguest();
__published:
	__property AnsiString DatabaseName = {read=GetDatabaseName, write=SetDatabaseName};
        __property AnsiString From = {read= GetFrom, write=SetFrom};
        __property AnsiString To = {read= GetTo, write=SetTo};
        __property AnsiString SQL= {read=FSQL, write= FSQL};
        __property AnsiString CopyrightInfo= {read= FCopyrightInfo, write= SetCopyrightInfo};

        __property int Width = {read=FWidth , write=FWidth};
        __property int Height = {read=FHeight, write=FHeight};

        __property bool AutoMax = {read=FAutoMax, write= SetAutoMax};
        __property bool AutoMin = {read=FAutoMin, write= SetAutoMin};

        __property double Max = {read=FMax, write=SetMax};
        __property double Min = {read=FMin, write=SetMin};

        __property int DiagramaNumericPenWidth = {read= FDiagramaNumericPenWidth, write=FDiagramaNumericPenWidth};
        __property int PenWidth = {read= FPenWidth, write=SetPenWidth};
        __property int PixelsInData = {read= FPixelsInData, write= FPixelsInData};

        __property TColor BackgroundInformation= {read= FBackgroundInformation, write=SetBackgroundInformation};
        __property TColor BackgroundLeft= {read= FBackgroundLeft, write=SetBackgroundLeft};
        __property TColor BackgroundRight= {read= FBackgroundRight, write=SetBackgroundRight};
        __property TColor BackgroundTop= {read= FBackgroundTop, write=SetBackgroundTop};
        __property TColor BackgroundBottom= {read= FBackgroundBottom, write=SetBackgroundTop};
        __property TColor BackgroundGraph= {read= FBackgroundGraph, write=SetBackgroundGraph};
        __property TColor BackgroundPen= {read= FBackgroundPen, write=SetBackgroundPen};

        __property TColor BackgroundDiagramNames= {read= FBackgroundDiagramNames, write= FBackgroundDiagramNames};
        __property TColor BackgroundDiagramNumeric= {read= FBackgroundDiagramNumeric, write= FBackgroundDiagramNumeric};
        __property TColor BackgroundDiagramNumericLabel= {read= FBackgroundDiagramNumericLabel, write= FBackgroundDiagramNumericLabel};

        __property TColor ForegroundInformation= {read= FForegroundInformation, write=SetForegroundInformation};
        __property TColor ForegroundLeft= {read= FForegroundLeft, write=SetForegroundLeft};
        __property TColor ForegroundRight= {read= FForegroundRight, write=SetForegroundRight};
        __property TColor ForegroundTop= {read= FForegroundTop, write=SetForegroundTop};
        __property TColor ForegroundBottom= {read= FForegroundBottom, write=SetForegroundBottom};
        __property TColor ForegroundGraph= {read= FForegroundGraph, write=SetForegroundGraph};
        __property TColor ForegroundPen= {read= FForegroundPen, write=SetForegroundPen};
        __property TColor ForegroundBorder= {read= FForegroundBorder, write=SetForegroundBorder};

        __property TColor ForegroundDiagramNames= {read= FForegroundDiagramNames, write=FForegroundDiagramNames};
        __property TColor ForegroundDiagramNumeric= {read= FForegroundDiagramNumeric, write=FForegroundDiagramNumeric};
        __property TColor ForegroundDiagramNumericLabel= {read= FForegroundDiagramNumericLabel, write=FForegroundDiagramNumericLabel};


        __property TFont* FontInformation= {read= FFontInformation, write= FFontInformation};
        __property TFont* FontDateTime= {read= FFontDateTime, write= FFontDateTime};
        __property TFont* FontRange= {read= FFontRange, write= FFontRange};
        __property TFont* FontDiagramNames= {read= FFontDiagramNames, write= FFontDiagramNames};
        __property TFont* FontDiagramNumeric= {read= FFontDiagramNumeric, write= FFontDiagramNumeric};

        __property bool Border= {read= FVisibleBorder, write= SetVisibleBorder};
        __property TDiagramSizeStyle HeightStyle= {read= FHeightStyle, write= SetHeightStyle};

//        __property int MaxPixelsInPageHeight= {read= FMaxPixelsInPageHeight, write= FMaxPixelsInPageHeight};
//        __property int MaxPixelsInPageWidth= {read= FMaxPixelsInPageWidth, write= FMaxPixelsInPageWidth};

        __property int MaxHeight= {read= FMaxHeight, write= FMaxHeight};
        __property int MinHeight= {read= FMinHeight, write= FMinHeight};
        __property int MaxWidth= {read= FMinWidth, write= FMinWidth};
        __property int MinWidth= {read= FMinWidth, write= FMinWidth};

//        __property int TablesCount= {read= FTablesCount, write= FTablesCount};
//        __property TStringList* Tables= {read= FTables};
        __property TStringList* TableNames= {read= FTableNames};
public:
        __fastcall TDBDiagram(TComponent* Owner);
        __fastcall virtual ~TDBDiagram(void);
};
//---------------------------------------------------------------------------
#endif



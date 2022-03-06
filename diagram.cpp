//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include <stdio.h>
#include "diagram.h"
#pragma package(smart_init)

//---------------------------------------------------------------------------
// ValidCtrCheck is used to assure that the components created do not have
// any pure virtual functions.
//
static inline void ValidCtrCheck(TDBDiagram *)
{
        new TDBDiagram(NULL);
}
//---------------------------------------------------------------------------
namespace DBDiagram
{
        void __fastcall PACKAGE Register()
        {
                 TComponentClass classes[1] = {__classid(TDBDiagram)};
                 //RegisterComponents("", classes, 0);
                 RegisterClasses(classes, 0);
        }
}
//---------------------------------------------------------------------------
__fastcall TDBDiagram::TDBDiagram(TComponent* Owner) : TComponent(Owner)
{
  Graph= new Graphics::TBitmap;
//  FTables= new TStringList;
  FTableNames= new TStringList;
  Graph->PixelFormat= pf4bit; //pf8bit;

  FHeight= 800;
  FWidth= 600;

  //FMaxPixelsInPageHeight= 800;
  //FMaxPixelsInPageWidth= 600;

  FMaxHeight= 10000;
  FMinHeight= 800;
  FMaxWidth= 1000;
  FMinWidth= 700;

  FADOConnection = new TADOConnection(this);
  FADOConnection->LoginPrompt = false;

  FADOQuery = new TADOQuery(this);
  FADOQuery->Connection = FADOConnection;

  FDatabaseName= ""; // 072001.mdb

  FCopyrightInfo= "Петрозаводская ТЭЦ, АСУ ТП (ЦТАИ), телефон: (331)";
  FVisibleBorder= true;

//  FAutoRange = true;
  FAutoMax= false;
  FAutoMin= false;

  FMax = 0;
  FMin = 100;

  /* ... */
  setmem(&from, sizeof(SYSTEMTIME), '\0');
  setmem(&to, sizeof(SYSTEMTIME), '\0');
  /* ... */
  /*
  AnsiString Str; // = Now();
  AnsiStringToSystemTime("", from);
  AnsiStringToSystemTime("", to);
  /*
  DateTimeToSystemTime(Now(), from);
  DateTimeToSystemTime(Now(), to);
  */
  /**/
  //-------------------------------------------------------
  FFormatString= "dd.mm.yy hh:nn";
  FReserve= 20;
  //-------------------------------------------------------
  FListInformationText= new TStringList;
  FListInformationText->Add("Организация: %s");
  FListInformationText->Add("Текущее время: %s");
  FListInformationText->Add("Диапазон запроса: %.2d.%.2d.%.2d %.2d:%.2d ... %.2d.%.2d.%.2d %.2d:%.2d");
  FListInformationText->Add("Диапазон данных: Min= %.2f; Max= %.2f; Количество данных= %d");
  //-------------------------------------------------------
  FFontInformation= new TFont;
  FFontDiagramNames= new TFont;
  FFontDiagramNumeric= new TFont;
  FFontDateTime= new TFont;
  FFontRange= new TFont;

  FFontInformation->Size= 10;
  FFontInformation->Name= "Arial";
  FFontInformation->Style= TFontStyles()<< fsBold;

  FFontDiagramNames->Size= 10;
  FFontDiagramNames->Name= "Arial";
  FFontDiagramNames->Style= TFontStyles()<< fsBold;

  FFontDiagramNumeric->Size= 12;
  FFontDiagramNumeric->Name= "Arial";
  FFontDiagramNumeric->Style= TFontStyles()<< fsBold;

  FFontDateTime->Size= 10;
  FFontDateTime->Name= "Arial";
  FFontDateTime->Style= TFontStyles()<< fsBold;

  FFontRange->Size= 10;
  FFontRange->Name= "Arial";
  FFontRange->Style= TFontStyles()<< fsBold;
//*
  TFont    *pFont;
  TLogFont  rFont;
  //...
  pFont= new TFont;
  pFont->Assign(FFontRange);
  ::GetObject(pFont->Handle, sizeof(rFont), &rFont);
  rFont.lfEscapement= 2700;
  rFont.lfOrientation= 2700;
  pFont->Handle= CreateFontIndirect(&rFont);
  FFontRange->Assign(pFont);
  pFont->Free();
//*/
  //-------------------------------------------------------
  FBackgroundInformation= clWhite; //clTeal; //clRed;
  FBackgroundDiagramNames= clWhite; // clLime; //
  FBackgroundDiagramNumeric= clWhite; // clTeal; //
  FBackgroundDiagramNumericLabel= clWhite; // clYellow; //
  FBackgroundLeft   = clWhite; //clLime;//clWhite;
  FBackgroundRight  = clWhite; //clLime; //clWhite;
  FBackgroundTop    = clWhite;
  FBackgroundBottom = clWhite; //clYellow; //clWhite;
  FBackgroundGraph  = clWhite; //clYellow; //cclLtGray; // Border!
  FBackgroundCopyright= clWhite; //clLime; //cclLtGray; // Border!
  FBackgroundPen= clRed;

  FForegroundInformation= clBlack;
  FForegroundDiagramNames= clBlack;
  FForegroundDiagramNumeric= clBlack;
  FForegroundDiagramNumericLabel= clBlack;
  FForegroundLeft= clBlack;
  FForegroundRight= clBlack;
  FForegroundTop= clBlack;
  FForegroundBottom= clBlack;
  FForegroundGraph= clBlack;
  FForegroundCopyright= clBlack;
  FForegroundPen= clRed;
  FForegroundBorder= clBlack;

  FWidthStyle= wsFixed; //wsRecordCount; //, wsDateTime,  };
  FHeightStyle=  wsRecordCount; //// wsFixed; //
  FPenWidth= 2;
  FDiagramaNumericPenWidth= 2;
  FPixelsInData= 5;
//  FTablesCount= 0;
}
//---------------------------------------------------------------------------
TColor __fastcall TDBDiagram::GetNextColor(BOOL state)
{
  static TColor PenColor[]= {clRed, clGreen, clBlue, clLime, clMaroon, clBlack };
  TColor CurrentColor;
  static I = 0;
  static Size= sizeof(PenColor) / sizeof(PenColor[0]);

  CurrentColor= PenColor[I++];
  
  if (state) I = 0;
  if (I >= Size) I = 0;
  return CurrentColor;
}
//---------------------------------------------------------------------------
__fastcall TDBDiagram::~TDBDiagram()
{
  FFontInformation->Free();
  FFontDiagramNames->Free();
  FFontDiagramNumeric->Free();
  FFontDateTime->Free();
  FFontRange->Free();

  Graph->Free();
  FADOQuery->Free();
  FADOConnection->Free();
  FListInformationText->Free();
 // FTables->Free();
  FTableNames->Free();
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundInformation(TColor Color)
{
  if (Color != FBackgroundInformation) {FBackgroundInformation= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundLeft(TColor Color)
{
  if (Color != FBackgroundLeft) {FBackgroundLeft= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundRight(TColor Color)
{
  if (Color != FBackgroundRight) {FBackgroundRight= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundTop(TColor Color)
{
  if (Color != FBackgroundTop) {FBackgroundTop= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundBottom(TColor Color)
{
  if (Color != FBackgroundBottom) {FBackgroundBottom= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundGraph(TColor Color)
{
  if (Color != FBackgroundGraph) {FBackgroundGraph= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetBackgroundPen(TColor Color)
{
  if (Color != FBackgroundPen) {FBackgroundPen= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundInformation(TColor Color)
{
  if (Color != FForegroundInformation) {FForegroundInformation= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundLeft(TColor Color)
{
  if (Color != FForegroundLeft) {FForegroundLeft= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundRight(TColor Color)
{
  if (Color != FForegroundRight) {ForegroundRight= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundTop(TColor Color)
{
  if (Color != FForegroundTop) {FForegroundTop= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundBottom(TColor Color)
{
  if (Color != FForegroundTop) {FForegroundTop= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundGraph(TColor Color)
{
  if (Color != FForegroundGraph) {FForegroundGraph= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundPen(TColor Color)
{
  if (Color != FForegroundPen) {FForegroundPen= Color;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetForegroundBorder(TColor Color)
{
  if (Color != FForegroundBorder) {FForegroundBorder= Color;}
}
/*
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetWidth()  {  return Graph->Width;  }
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetHeight() {  return Graph->Height; }
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetWidth(int iWidth)
{
  if (iWidth != Graph->Width)  {
        Resize(iWidth, Graph->Height);
  }
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetHeight(int iHeight)
{
  if (iHeight != Graph->Height)  {
        Resize(Graph->Width, iHeight);
  }
}
*/
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetMax(double Value)
{
  if (Value != FMax)  {FMax= Value;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetMin(double Value)
{
  if (Value != FMin)  {FMin= Value;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetDatabaseName(AnsiString SValue)
{
//  if (SValue != FDatabaseName)  {  FDatabaseName= SValue;  }
  //FADOConnection->Connected == false &&

  if ( FDatabaseName != SValue)
  {
        FDatabaseName = SValue;
        //ShowMessage("SetDatabaseName");
        //MemoryInformation("SetDatabaseName", FALSE);

        AnsiString CFormat =
                "Provider=MSDataShape.1;"
                "Persist Security Info=True;"
                "Data Source=%s;"
                "Data Provider=Microsoft.Jet.OLEDB.4.0";
        //-------------------------------------------------------------------
        FADOConnection->Connected = false;
        FADOConnection->ConnectionString =
                        Format(CFormat, OPENARRAY(TVarRec,( FDatabaseName )));
        FADOConnection->Connected = true;
        //MemoryInformation("SetDatabaseName", FALSE);
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TDBDiagram::GetDatabaseName() {return FDatabaseName;}
//---------------------------------------------------------------------------
AnsiString __fastcall TDBDiagram::ReadFile(AnsiString FileName)
{
  TFileStream*  FMyFile= new TFileStream(FileName, fmOpenRead);
  AnsiString S;

  S.SetLength(FMyFile->Size + 1);
  FMyFile->Read(S.c_str(), FMyFile->Size);
  S[FMyFile->Size] = '\0';
  FMyFile->Free();
  return S;
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetAutoMax(bool Value)
{
  if (Value != FAutoMax) {FAutoMax= Value;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetAutoMin(bool Value)
{
  if (Value != FAutoMin) {FAutoMin= Value;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::RequestRange()
{
/*
  AnsiString  SQLFormat, SQL;

  if (FAutoMax || FAutoMin)  {

        SQLFormat = ReadFile(FAgregateSQLFile);
        SQL = Format(SQLFormat, OPENARRAY(TVarRec,(
                FTableName.c_str(),
                from.wMonth, from.wDay, from.wYear, from.wHour, from.wMinute,
                to.wMonth,   to.wDay,   to.wYear,   to.wHour,   to.wMinute )));

        FADOQuery->Close();
        FADOQuery->SQL->Clear();
        FADOQuery->SQL->Add( SQL );
        FADOQuery->Open();

        if (FAutoMax)  FMax= FADOQuery->Fields->Fields[0]->AsFloat;
        if (FAutoMin)  FMin= FADOQuery->Fields->Fields[1]->AsFloat;
  }
*/
  if (FAutoMax || FAutoMin)  {
        double FieldsMin, FieldsMax;
        FieldsMin= FADOQuery->Fields->Fields[2]->AsFloat;
        FieldsMax= FADOQuery->Fields->Fields[2]->AsFloat;
        for (int C = 2; C < FADOQuery->Fields->Count; C++)
        {
                FADOQuery->First();
                while ( !(FADOQuery->Eof))  {
                        FieldsMin= min(FieldsMin, FADOQuery->Fields->Fields[C]->AsFloat);
                        FieldsMax= max(FieldsMax, FADOQuery->Fields->Fields[C]->AsFloat);
                        FADOQuery->Next();
                }// while (!(Eof));
        } // for (C)
        if (FAutoMax)  FMax= FieldsMax;
        if (FAutoMin)  FMin= FieldsMin;
  }
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::Request()
{
  AnsiString  SQLFormat, SQL;

  FADOQuery->Close();
  FADOQuery->SQL->Clear();
  FADOQuery->SQL->Add( FSQL );
  FADOQuery->Open();
  //ShowMessage("ConnectionString = " + FADOConnection->ConnectionString);
  //-------------------------------------------------------------------
  //MemoryInformation("SQL", FALSE);
  //MemoryInformation("Request", FALSE);
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetFrom(AnsiString Str)
{
  //ShowMessage("AnsiString: " + Str);
  AnsiStringToSystemTime(Str, from);
  //ShowMessage("SystemTime:" + SystemTimeToAnsiString(from));
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetTo(AnsiString Str)
{
  //ShowMessage("AnsiString: " + Str);
  AnsiStringToSystemTime(Str, to);
  //ShowMessage("SystemTime:" + SystemTimeToAnsiString(to));
}
//---------------------------------------------------------------------------
AnsiString __fastcall TDBDiagram::GetFrom()
{
  return SystemTimeToAnsiString(from);
}
//---------------------------------------------------------------------------
AnsiString __fastcall TDBDiagram::GetTo()
{
  return SystemTimeToAnsiString(to);
}
//---------------------------------------------------------------------------
double __fastcall TDBDiagram::GetMax() {return FMax;}
//---------------------------------------------------------------------------
double __fastcall TDBDiagram::GetMin() {return FMin;}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetInformationTextHeight()
{
  Graph->Canvas->Font->Assign(FFontInformation);
  return Graph->Canvas->TextHeight(FListInformationText->Strings[0]);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetInformationTextWidth()
{
  Graph->Canvas->Font->Assign(FFontInformation);
  return Graph->Canvas->TextWidth(FListInformationText->Strings[0]);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDiagramNamesTextHeight()
{
  Graph->Canvas->Font->Assign(FFontDiagramNames);
  return Graph->Canvas->TextHeight(FListInformationText->Strings[0]);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDiagramNamesTextWidth()
{
  Graph->Canvas->Font->Assign(FFontDiagramNames);
  return Graph->Canvas->TextWidth(FListInformationText->Strings[0]);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDiagramNumericTextHeight()
{
  Graph->Canvas->Font->Assign(FFontDiagramNumeric);
  return Graph->Canvas->TextHeight(FListInformationText->Strings[0]);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDiagramNumericTextWidth()
{
  AnsiString Number(0);
  Graph->Canvas->Font->Assign(FFontDiagramNumeric);
  return Graph->Canvas->TextWidth(Number);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetRangeTextHeight()
{
  AnsiString S;
  S.sprintf("%.2f", FMin);
  Graph->Canvas->Font->Assign(FFontRange);
  return Graph->Canvas->TextHeight(S);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetRangeTextWidth()
{
  AnsiString S;
  S.sprintf("%.2f", FMax);
  Graph->Canvas->Font->Assign(FFontRange);
  return Graph->Canvas->TextWidth(S);
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDateTimeTextHeight()
{
  Graph->Canvas->Font->Assign(FFontDateTime);
  return Graph->Canvas->TextHeight(Now().FormatString(FFormatString));
}
//---------------------------------------------------------------------------
int __fastcall TDBDiagram::GetDateTimeTextWidth()
{
  Graph->Canvas->Font->Assign(FFontDateTime);
  return Graph->Canvas->TextWidth(Now().FormatString(FFormatString));
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetPenWidth(int Value)
{
  if (Value != FPenWidth) {FPenWidth= Value;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::Resize(TDiagramSizeStyle DiagramSizeStyle)
{
  AnsiString S;
  int iInformationTextHeight= GetInformationTextHeight();
  int iRangeTextWidth= GetRangeTextWidth();
  int iDateTimeTextHeight= GetDateTimeTextHeight();
  int iDateTimeTextWidth= GetDateTimeTextWidth();
  int iDiagramNamesTextHeight= GetDiagramNamesTextHeight();
  int iDiagramNumericTextHeight= GetDiagramNumericTextHeight();

switch (DiagramSizeStyle) // FHeightStyle)
{
case wsFixed:   //--------------------------------------------------------
{
  /* Размеры */
  Graph->Width= Width;
  Graph->Height= Height;

  /* Определяем размер верхней области, предназначенной для печати служебной информации */
  rInformation.Left   = 0;
  rInformation.Top    = 0;
  rInformation.Right  = Width - 1;
  rInformation.Bottom = FListInformationText->Count * iInformationTextHeight + FReserve;

  /* Определяем размер  */
  rDiagramNames.Left   = 0;
  rDiagramNames.Top    = rInformation.Bottom;
  rDiagramNames.Right  = Width - 1;
  rDiagramNames.Bottom = FTableNames->Count * iDiagramNamesTextHeight + FReserve;
  rDiagramNames.Bottom += rInformation.Bottom;

  /* Определяем размер  */
  rDiagramNumeric.Left   = 0;
  rDiagramNumeric.Top    = rDiagramNames.Bottom;
  rDiagramNumeric.Right  = Width - 1;
  rDiagramNumeric.Bottom = FTableNames->Count * iDiagramNumericTextHeight;
  rDiagramNumeric.Bottom += rDiagramNames.Bottom;

  /* Определяем размер верхней области диапазона данных */
  rTop.Left    = 0;
  rTop.Top     = rDiagramNumeric.Bottom;
  rTop.Right   = Width - 1;
  rTop.Bottom  = rTop.Top; // rDiagramNumeric.Bottom + iRangeTextWidth + FReserve;

  /* Определяем размер левой области даты и времени */
  rLeft.Left= 0;
  rLeft.Top= rTop.Bottom;
  rLeft.Right= iDateTimeTextWidth + FReserve;
  rLeft.Bottom= Height - iRangeTextWidth - FReserve;;

  /* Определяем размер правой области даты и времени */
  /* - GetDateTimeTextWidth() Печать даты и времени на правой области
        удалена по требованию.
  */
  rRight.Left= Width - 1 - FReserve;
  rRight.Top= rTop.Bottom;
  rRight.Right= Width - 1;
  rRight.Bottom= rLeft.Bottom;


  /* Определяем размер нижней области диапазона данных */
  rBottom.Left= 0;
  rBottom.Top= rLeft.Bottom;
  rBottom.Right= Width - 1;
  rBottom.Bottom= Height;

  /* Определяем размер области рисования графика */
  rCenter.Left= rLeft.Right;
  rCenter.Top= rTop.Bottom + iDateTimeTextHeight / 2; // FReserve; //
  rCenter.Right= rRight.Left;
  rCenter.Bottom= rBottom.Top - iDateTimeTextHeight / 2; // FReserve; //
}
break;

case wsRecordCount:  //--------------------------------------------------------
{
  /* Размеры */
  Graph->Width= Width;

  int CenterWidth= FPixelsInData * FADOQuery->RecordCount;

  /* Определяем размер верхней области, предназначенной для печати служебной информации */
  rInformation.Left   = 0;
  rInformation.Top    = 0;
  rInformation.Right  = Width - 1;
  rInformation.Bottom = FListInformationText->Count * iInformationTextHeight + FReserve;

  /* Определяем размер  */
  rDiagramNames.Left   = 0;
  rDiagramNames.Top    = rInformation.Bottom;
  rDiagramNames.Right  = Width - 1;
  rDiagramNames.Bottom = FTableNames->Count * iDiagramNamesTextHeight + FReserve;
  rDiagramNames.Bottom += rInformation.Bottom;

  /* Определяем размер  */
  rDiagramNumeric.Left   = 0;
  rDiagramNumeric.Top    = rDiagramNames.Bottom;
  rDiagramNumeric.Right  = Width - 1;
  rDiagramNumeric.Bottom = FTableNames->Count * iDiagramNumericTextHeight;
  rDiagramNumeric.Bottom += rDiagramNames.Bottom;

  /* Определяем размер верхней области диапазона данных */
  rTop.Left   = 0;
  rTop.Top    = rDiagramNumeric.Bottom;
  rTop.Right  = Width - 1;
  rTop.Bottom = rTop.Top; // rTop.Top + iRangeTextWidth + FReserve;

  /* Определяем размер левой области даты и времени */
  rLeft.Left   = 0;
  rLeft.Top    = rTop.Bottom;
  rLeft.Right  = iDateTimeTextWidth + FReserve;
  rLeft.Bottom = rLeft.Top + CenterWidth + iDateTimeTextHeight;

  /* Определяем размер правой области даты и времени */
  /* - GetDateTimeTextWidth() Печать даты и времени на правой области
        удалена по требованию.
  */
  rRight.Left   = Width - 1 - FReserve;
  rRight.Top    = rTop.Bottom;
  rRight.Right  = Width - 1;
  rRight.Bottom = rRight.Top + CenterWidth + iDateTimeTextHeight;

  /* Определяем размер области рисования графика */
  rCenter.Left   = rLeft.Right;
  rCenter.Top    = rTop.Bottom + iDateTimeTextHeight / 2; // FReserve; //
  rCenter.Right  = rRight.Left;
  rCenter.Bottom = rCenter.Top + CenterWidth;
  //rBottom.Top - iDateTimeTextHeight / 2; // FReserve; //

  /* Определяем размер нижней области диапазона данных */
  rBottom.Left   = 0;
  rBottom.Top    = rLeft.Bottom;
  rBottom.Right  = Width - 1;
  rBottom.Bottom = rBottom.Top + iRangeTextWidth + FReserve;

//  Graph->Height= rBottom.Bottom;
  //*

  if (rBottom.Bottom < FMinHeight)
  {
        // Если вычисления показали что высота диаграммы менее высоты листа
        // делаем её равным высоте листа
        FHeight= FMinHeight;
        Resize(wsFixed);

  } else if (rBottom.Bottom > FMaxHeight)
  {
        // Если вычисления показали что высота диаграммы менее высоты листа
        // делаем её равным высоте листа
        FHeight= FMaxHeight;
        Resize(wsFixed);

  } else {
        Graph->Height= rBottom.Bottom;
  }
  //*/
}
break;
case wsDateTime:  //--------------------------------------------------------
{
  /* Размеры */
  Graph->Width= Width;

  /* Определяем размер верхней области, предназначенной для печати служебной информации */
  rInformation.Left   = 0;
  rInformation.Top    = 0;
  rInformation.Right  = Width - 1;
  rInformation.Bottom = FListInformationText->Count * iInformationTextHeight + FReserve;

  /* Определяем размер  */
  rDiagramNames.Left   = 0;
  rDiagramNames.Top    = rInformation.Bottom;
  rDiagramNames.Right  = Width - 1;
  rDiagramNames.Bottom = FTableNames->Count * iDiagramNamesTextHeight + FReserve;
  rDiagramNames.Bottom += rInformation.Bottom;

  /* Определяем размер  */
  rDiagramNumeric.Left   = 0;
  rDiagramNumeric.Top    = rDiagramNames.Bottom;
  rDiagramNumeric.Right  = Width - 1;
  rDiagramNumeric.Bottom = FTableNames->Count * iDiagramNumericTextHeight;
  rDiagramNumeric.Bottom += rDiagramNames.Bottom;

  /* Определяем размер верхней области диапазона данных */
  rTop.Left   = 0;
  rTop.Top    = rDiagramNumeric.Bottom;
  rTop.Right  = Width - 1;
  rTop.Bottom = rTop.Top; // rTop.Top + iRangeTextWidth + FReserve;

  /* Определяем размер левой области даты и времени */
  rLeft.Left   = 0;
  rLeft.Top    = rTop.Bottom;
  rLeft.Right  = iDateTimeTextWidth + FReserve;
  rLeft.Bottom = rLeft.Top + (FADOQuery->RecordCount * iDateTimeTextHeight);

  /* Определяем размер правой области даты и времени */
  /* - GetDateTimeTextWidth() Печать даты и времени на правой области
        удалена по требованию.
  */
  rRight.Left   = Width - 1 - FReserve;
  rRight.Top    = rTop.Bottom;
  rRight.Right  = Width - 1;
  rRight.Bottom = rRight.Top + (FADOQuery->RecordCount * iDateTimeTextHeight);

  /* Определяем размер области рисования графика */
  rCenter.Left   = rLeft.Right;
  rCenter.Top    = rTop.Bottom + iDateTimeTextHeight / 2; // FReserve; //
  rCenter.Right  = rRight.Left;
  rCenter.Bottom = rCenter.Top + (FADOQuery->RecordCount * iDateTimeTextHeight) - iDateTimeTextHeight;

  /* Определяем размер нижней области диапазона данных */
  rBottom.Left   = 0;
  rBottom.Top    = rLeft.Bottom;
  rBottom.Right  = Width - 1;
  rBottom.Bottom = rBottom.Top + iRangeTextWidth + FReserve;

  Graph->Height= rBottom.Bottom;
        /*
  if (rBottom.Bottom < FPixelPerPageHeight)
  {
        FHeight= FPixelPerPageHeight;
        FHeightStyle= wsFixed;
        Resize();

  } else {
        Graph->Height= rBottom.Bottom;
  }
*/
}
break;
} // switch(FHeightStyle)

}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintBackground(TCanvas *Cvs)
{
  /* Заливаем области диграммы */

  //Cvs->Pen->Color= FForegroundInformation;
  Cvs->Pen->Color= FBackgroundInformation;
  Cvs->Brush->Color= FBackgroundInformation;
  Cvs->Rectangle(rInformation);
  //Cvs->FillRect(rInformation);
  //Cvs->FrameRect(rInformation);

  //Cvs->Pen->Color= FBackgroundDiagramNames;
  Cvs->Pen->Color= FBackgroundDiagramNames;
  Cvs->Brush->Color= FBackgroundDiagramNames;
  Cvs->Rectangle(rDiagramNames);
  //Cvs->FillRect(rDiagramNames);
  //Cvs->FrameRect(rDiagramNames);

  //Cvs->Pen->Color= FBackgroundDiagramNnumeric;
  Cvs->Pen->Color= FBackgroundDiagramNumeric;
  Cvs->Brush->Color= FBackgroundDiagramNumeric;
  Cvs->Rectangle(rDiagramNumeric);
  //Cvs->FillRect(rDiagramNumeric);
  //Cvs->FrameRect(rDiagramNumeric);


  //Cvs->Pen->Color= FForegroundTop;
  Cvs->Pen->Color= FBackgroundTop;
  Cvs->Brush->Color= FBackgroundTop;
  Cvs->Rectangle(rTop);
  //Cvs->FillRect(rTop);
  //Cvs->FrameRect(rTop);

  //Cvs->Pen->Color= FForegroundBottom;
  Cvs->Pen->Color= FBackgroundBottom;
  Cvs->Brush->Color= FBackgroundBottom;
  Cvs->Rectangle(rBottom);
  //Cvs->FillRect(rBottom);
  //Cvs->FrameRect(rBottom);

  //Cvs->Pen->Color= FForegroundLeft;
  Cvs->Pen->Color= FBackgroundLeft;
  Cvs->Brush->Color= FBackgroundLeft;
  Cvs->Rectangle(rLeft);
  //Cvs->FillRect(rLeft);
  //Cvs->FrameRect(rLeft);

  //Cvs->Pen->Color= FForegroundRight;
  Cvs->Pen->Color= FBackgroundRight;
  Cvs->Brush->Color= FBackgroundRight;
  Cvs->Rectangle(rRight);
  //Cvs->FillRect(rRight);
  //Cvs->FrameRect(rRight);

  //Cvs->Pen->Color= FForegroundGraph;
  Cvs->Pen->Color= FBackgroundGraph;
  Cvs->Brush->Color= FBackgroundGraph;
  Cvs->Rectangle(rCenter);

  Cvs->Brush->Color= FForegroundGraph;
  //Cvs->Rectangle(rCenter);
  Cvs->FrameRect(rCenter);
  //Cvs->FillRect(rCenter);
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaint(TCanvas *Cvs)
{
  /*
    Получаем данные из базы данных здесь т.к. нужно знать RecordCount для
    FHeightStyle = wsRecordCount
  */
  // Запускаем SQL запрос, и получаем данные
  Request();
  // Находим минимум и максимум.
  RequestRange();
  Resize(FHeightStyle);
  //ResizeWidth(FWidthStyle);
  //ResizeHeight(FHeightStyle);
  DoPaintBackground(Cvs);
  DoPaintInformation(Cvs);
  DoPaintDiagramNames(Cvs);
  DoPaintDiagramNumeric(Cvs);
  DoPaintRange(Cvs);
  DoPaintDateTime(Cvs);
  DoPaintGraph(Cvs);
  DoPaintBorder(Cvs);
  return;
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintInformation(TCanvas *Cvs)
{
  AnsiString S;
  int iLeft= rInformation.Left + FReserve / 2;
  int iTop= rInformation.Top + FReserve / 2;
  int iTextHeight= GetInformationTextHeight();

  Cvs->Pen->Color= FForegroundInformation;
  Cvs->Brush->Color= FBackgroundInformation;
  Cvs->Font->Assign(FFontInformation);

  S.printf(FListInformationText->Strings[0].c_str(), FCopyrightInfo.c_str());
  Cvs->TextOutA(iLeft, iTop, S);
  iTop += iTextHeight;
  //-------------------------------------------------------------------------
  S.sprintf(FListInformationText->Strings[1].c_str(), Now().DateTimeString().c_str());
  Cvs->TextOutA(iLeft, iTop, S);
  iTop += iTextHeight;
  //-------------------------------------------------------------------------
  S.sprintf(FListInformationText->Strings[2].c_str(),
  from.wDay, from.wMonth, from.wYear, from.wHour, from.wMinute, // from.wSecond,
  to.wDay, to.wMonth, to.wYear, to.wHour, to.wMinute); // , to.wSecond
  Cvs->TextOutA(iLeft, iTop, S);
  iTop += iTextHeight;
  //-------------------------------------------------------------------------
  S.printf(FListInformationText->Strings[3].c_str(), FMin, FMax, FADOQuery->RecordCount);
  Cvs->TextOutA(iLeft, iTop, S);
  iTop += iTextHeight;
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintDiagramNames(TCanvas *Cvs)
{
  int iLeft= rDiagramNames.Left + FReserve / 2;
  int iTop= rDiagramNames.Top + FReserve / 2;
  int iTextHeight= GetDiagramNamesTextHeight();
  AnsiString S, Buffer;

  Cvs->Pen->Color= FForegroundDiagramNames;
  Cvs->Brush->Color= FBackgroundDiagramNames;
  Cvs->Font->Assign(FFontDiagramNames);

  for (int I = 0; I < FTableNames->Count; I ++, iTop += iTextHeight)
  {
        S.printf("%d - %s", I + 1, FTableNames->Strings[I].c_str());
        Cvs->TextOutA(iLeft, iTop, S);
  }
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintDiagramNumeric(TCanvas *Cvs)
{
  int iLeft= rDiagramNumeric.Left;
  int iTop = rDiagramNumeric.Top;

  int iTextWidth= GetDiagramNumericTextWidth();
  int iTextHeight= GetDiagramNumericTextHeight();
  int iMax= max(iTextWidth, iTextHeight);
  int iMin= min(iTextWidth, iTextHeight);

  Cvs->Pen->Color= FForegroundDiagramNumericLabel;
  Cvs->Brush->Color= FBackgroundDiagramNumericLabel;
  FFontDiagramNumeric->Size -= 4;
  Cvs->Font->Assign(FFontDiagramNumeric);

  iTextWidth= GetDiagramNumericTextWidth();
  iTextHeight= GetDiagramNumericTextHeight();

  int iWidth= (rCenter.Right - rCenter.Left);
  int iHeight= (rCenter.Bottom - rCenter.Top);
  double kx= (double)(iWidth  + 1) / (double)(FMax - FMin);
  int iSaveWidthPen;

  iSaveWidthPen= Cvs->Pen->Width;
  // Сбрасываем счётчик цветов на начало
  GetNextColor(TRUE);
  // Устанавливаем курсор на начало данных
  FADOQuery->First();
  for (int C = 2, DiagramNo = 1, iTop= rDiagramNumeric.Top; C < FADOQuery->Fields->Count; C++, iTop += iMax, DiagramNo ++ )
  {
        double dData= FADOQuery->Fields->Fields[C]->AsFloat;
        int iX= (int)(kx * (dData - FMin)) + rCenter.Left;

        Cvs->Pen->Width= FDiagramaNumericPenWidth;
        Cvs->Pen->Color= GetNextColor(FALSE);

        Cvs->MoveTo(iX, rCenter.Top);
        Cvs->LineTo(iX, iTop);

        Cvs->Pen->Width= iSaveWidthPen;
        iX -= (iMax / 2);
        Cvs->Ellipse(iX, iTop, iX + iMax, iTop + iMax);
        Cvs->TextOutA(iX + (iMax - iTextWidth) / 2, iTop + (iMax - iTextHeight) / 2, IntToStr(DiagramNo)); // iLeft
  }
//        Cvs->TextOutA(0,0, FloatToStr(FMin) + "," + FloatToStr(FMax));
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintRange(TCanvas *Cvs)
{
  AnsiString S;
  int iWidth= (rCenter.Right - rCenter.Left);
  int iTextHeight= GetRangeTextHeight();
  int iTextWidth= GetRangeTextWidth();
  double dOffset;
  double kx= (double)(FMax - FMin) / (double)(iWidth - 1);
  int iHalfTextHeight= iTextHeight / 2;
  int iHalfReserve= FReserve / 2;
  int dCountTextPerHeight= (iWidth - 1) / iTextHeight;
  double step= (double)(iWidth - 1) / (double)dCountTextPerHeight;
  int iRight= (int)((double)dCountTextPerHeight * step);

  Cvs->Brush->Color= FBackgroundTop;
  Cvs->Pen->Color= FForegroundTop;
  Cvs->Pen->Width= 1;
  Cvs->Font->Assign(FFontRange);

  /* Рисуем минимум и максимум */
  for (double dx= rCenter.Left; dx <= rCenter.Right; dx += step)
  {
        Cvs->MoveTo(dx, rCenter.Top); //iRight); // Cvs->MoveTo(dx, rCenter.Top);     //
        Cvs->LineTo(dx, rCenter.Bottom + FReserve*2); // Cvs->LineTo(dx, rCenter.Bottom);  // 

        dOffset= (dx - (double)rCenter.Left) * kx;

        S.sprintf("%.2f", FMin + dOffset); //S.sprintf("%.2f [%.2f]", FMin, iRecNo);
//        Cvs->TextOutA(dx + iHalfTextHeight, rTop.Top + iHalfReserve, S); //
        Cvs->TextOutA(dx + iHalfTextHeight, rLeft.Bottom + iHalfReserve, S); // iTextWidth
  }
/*
  Cvs->Font->Assign(FFontDateTime);
  int iLeftOutput= 230;
  int iTopOutput= 180;
//  S.sprintf("iHeight = %d",iHeight);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("kx = %f",kx);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("step = %.10f",step);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
//  S.sprintf("temp = %.10f",temp);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("dCountTextPerHeight = %d",dCountTextPerHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("iWidth = %d",iWidth);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("Max-Min = %f",FMax-FMin);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
//  S.sprintf("dx = %f",dx);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
*/
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintDateTime(TCanvas *Cvs)
{
  if (!FADOQuery->RecordCount) return;

  TDateTime Date, Time;
  AnsiString S;

  int iHeight= (rCenter.Bottom - rCenter.Top);
  double ki= (double)(FADOQuery->RecordCount) / (double)(iHeight - 1);
  int iTextHeight= GetDateTimeTextHeight();
  int iHalfTextHeight= iTextHeight / 2;
  int dCountTextPerHeight= (iHeight - 1) / iTextHeight;
  int iHalfReserve= FReserve / 2;
  double temp, ky, step;

  if ((FADOQuery->RecordCount - 1) <= dCountTextPerHeight)
  {
        step= (double)(iHeight - 1) / (FADOQuery->RecordCount - 1); // (int)temp; //
  } else
  {
        ky= (double)(iHeight - 0) / (double)(FADOQuery->RecordCount - 1);
        temp= (double)iTextHeight / (double)ky;
        temp= ceil(temp);
        step= ky * temp;
  }
  //-------------------------------------------------------------------------
  Cvs->Font->Assign(FFontDateTime);
  Cvs->Brush->Color= FBackgroundLeft;
  Cvs->Pen->Color= FForegroundLeft;
  Cvs->Pen->Width= 1;

  /* Рисуем дату и время. */
  for (double dy= rCenter.Top; dy <= rCenter.Bottom; dy += step)
  {
        Cvs->MoveTo(rCenter.Left - FReserve,  dy);
        Cvs->LineTo(rCenter.Right, dy); //  + FReserve
        int iRecNo= (dy - rCenter.Top) * ki;
        //-------------------------------------------------------------------
        FADOQuery->First();
        FADOQuery->MoveBy(iRecNo);
        Cvs->Brush->Color= FBackgroundLeft;
        Cvs->Pen->Color= FForegroundLeft;
        Date= FADOQuery->FieldByName("Дата")->AsDateTime;
        Time= FADOQuery->FieldByName("Время")->AsDateTime;
        S= Date.FormatString("dd.mm.yy") + " " + Time.FormatString("hh:nn");
        //S += ("[" + IntToStr(iRecNo) + "] dy= " + FloatToStr(dy - rCenter.Top));
        Cvs->TextOutA(rLeft.Left  + iHalfReserve, dy - iHalfTextHeight, S);
        //Cvs->TextOutA(rRight.Left + iHalfReserve, dy - iHalfTextHeight, S);
  }
/*
  Cvs->Font->Assign(FFontDateTime);
  int iLeftOutput= 180;
  int iTopOutput= 180;

  S.sprintf("iHeight = %d",iHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

  S.sprintf("kx = %f",ky);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

  S.sprintf("iTextHeight = %d", iTextHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

  S.sprintf("iHalfTextHeight = %d", iHalfTextHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

  S.sprintf("dCountTextPerHeight = %d",dCountTextPerHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

  S.sprintf("d1 = %f", d1);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("d2 = %f", d2);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("d3 = %f", d3);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("step = %.f",step);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
*/
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintGraph(TCanvas *Cvs)
{
  int iRecNo = 0;
  int iX, iY;
//  int iLeft=10;
//  int iTop= 400;
  int iWidth= (rCenter.Right - rCenter.Left);
  int iHeight= (rCenter.Bottom - rCenter.Top);

  double kx= (double)(iWidth  + 1) / (double)(FMax - FMin);
  double ky= (double)(iHeight - 0) / (double)(FADOQuery->RecordCount - 1);

  Cvs->Pen->Width= FPenWidth;
  Cvs->Pen->Color= clRed; //FForegroundPen;
  Cvs->Brush->Color= clWhite; //FBackgroundPen;
  Cvs->Font->Assign(FFontDateTime);

  // Сбрасываем счётчик в 0
  GetNextColor(TRUE);
  for (int C = 2; C < FADOQuery->Fields->Count; C++)
  {
  iRecNo= 0;
  FADOQuery->First();
  //TBrushStyle= ;
//  Cvs->Brush->Style= bsCross;
//  Cvs->Pen->Style= PenStyle[C];
  Cvs->Pen->Color= GetNextColor(FALSE);
  while ( !(FADOQuery->Eof))  {

        double dData= FADOQuery->Fields->Fields[C]->AsFloat;

        iX = (int)(kx * (dData - FMin)) + rCenter.Left;
        iY = (int)(ky * iRecNo) + rCenter.Top;

        // Проверяем не вылезет ли график диаграммы за пределеы
        //
        //
        //if (iX >= rCenter.Left && iX <= rCenter.Right )
        {
                if (iRecNo==0) {
                        Cvs->MoveTo(iX, iY);
                        //AnsiString sC(FADOQuery->Fields->Count); // FTables->Count
                        //Cvs->TextOutA(iX - Cvs->TextHeight(sC)/2, iY - Cvs->TextWidth(sC)/2, sC);
                }
                else
                {
                        Cvs->LineTo(iX, iY);
                }
        }
//  S.sprintf("[%f][iX=%d, kx=%f, dData= %f] [iY= %d, ky=%f, iRecNo= %d]", temp, iX, kx, dData, iY, ky, iRecNo);
//  Cvs->TextOutA(iLeft, iTop, S);
//  iTop += 20;
        FADOQuery->Next();
        iRecNo++;
  }// while (!(Eof));
  } // for (C)

//---------------------------------------------------------------------------
/*
  Cvs->Pen->Width= 1;
        iRecNo=0;
  FADOQuery->First();
  while ( !(FADOQuery->Eof))  {

        iY = (int)(ky * iRecNo) + rCenter.Top;

        // рисуем вспомогательные линии
        Cvs->MoveTo(rCenter.Left, iY);
        Cvs->LineTo(rRight.Right, iY);

        FADOQuery->Next();
        iRecNo++;
  }// while (!(Eof));
*/
/*
  Cvs->Font->Assign(FFontDateTime);
  int iLeftOutput= 180;
  int iTopOutput= 400;
  AnsiString S;
  S.sprintf("iHeight = %d",iHeight);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("ky = %f",ky);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("kx = %f",kx);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);

//  S.sprintf("step = %.10f",step);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
//  S.sprintf("temp = %.10f",temp);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
//  S.sprintf("dCountTextPerHeight = %d",dCountTextPerHeight);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("iWidth = %d",iWidth);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
  S.sprintf("Max-Min = %f",FMax-FMin);
  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
//  S.sprintf("dx = %f",dx);
//  Cvs->TextOutA(iLeftOutput, iTopOutput += 20, S);
*/
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::DoPaintBorder(TCanvas *Cvs)
{
  if (FVisibleBorder)
  {
        Cvs->Brush->Color= ForegroundBorder;
        Cvs->FrameRect(Cvs->ClipRect);
  }
  /*
  else {
        Cvs->Pen->Color= FBackgroundBorder;
        Cvs->Brush->Color= FBackgroundBorder;
  }
  */
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetHeightStyle(TDiagramSizeStyle Style)
{
  if (Style != FHeightStyle) {FHeightStyle= Style;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetCopyrightInfo(AnsiString S)
{
  if (S != FCopyrightInfo) {FCopyrightInfo= S;}
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SetVisibleBorder(bool Value)
{
  if (FVisibleBorder != Value) {FVisibleBorder= Value;}
}

AnsiString __fastcall TDBDiagram::SaveToFile(AnsiString ImagePath)
{
  TJPEGImage *Jpg = new TJPEGImage();
  AnsiString JpgFileName, BaseFile;
  char deliver= '+';
  //char d1= '@', d2= '_';
  SYSTEMTIME lt;

  GetLocalTime(&lt);
  BaseFile.sprintf(
  "%.2d%c%.2d%c%.2d%c%.2d%c%.2d%c%.2d%c%d",
  lt.wDay,
  deliver,
  lt.wMonth,
  deliver,
  lt.wYear,
  deliver,
  lt.wHour,
  deliver,
  lt.wMinute,
  deliver,
  lt.wSecond,
  deliver,
  lt.wMilliseconds
  );

  JpgFileName= BaseFile + AnsiString(".jpg");
  // BmpFileName= BaseFile + AnsiString(".bmp");
  // JpgFileName.sprintf("%f.jpg", Now().operator double());

  try
  {
    // Рисуем диаграмму
    DoPaint(Graph->Canvas);

//    Bitmap->PixelFormat= pf4bit;
//    Bitmap->Height= Graph->Height;
//    Bitmap->Width= Graph->Width;
//    Bitmap->Canvas->Draw(0,0, Graph);
//    Assign(Graph);
//    Bitmap->PixelFormat= pf4bit;
//    Bitmap->SaveToFile(ImagePath + BmpFileName );

    Jpg->Assign(Graph);
    Jpg->SaveToFile(ImagePath + JpgFileName);

    return JpgFileName; //BmpFileName; //;
  }
  __finally
  {
    Jpg->Free();
  }
    return AnsiString("");
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::SaveToStream(TMemoryStream* Stream)
{
  TJPEGImage *Jpg= new TJPEGImage();

  try
  {
        /* Рисуем диаграмму */
        DoPaint(Graph->Canvas);
        //Jpg->Assign(Bitmap); // Jpg->Assign(P->Graphic);
        //Graph->SaveToFile("c:\\pic.bmp");

        Jpg->Assign(Graph);
        //Jpg->PixelFormat= jf8Bit; //{jf24Bit, };
        //Jpg->Performance= jpBestQuality; //, jpBestSpeed};
        //Jpg->CompressionQuality= 100;
        //Jpg->Compress();

        Jpg->SaveToStream(Stream);
        //Jpg->SaveToFile("c:\\pic.jpg");
  }
  __finally
  {
        Jpg->Free();
  }
/*  catch(Exception &e) {   //e.Message.c_str(), IID_IEditServer); } */
}
//---------------------------------------------------------------------------
PChar search_token_dt(PChar t, WORD &i)
{
  PChar pt, pn;
  Char Buffer[14];

  pt = t;
  pn = Buffer;
  //...
  while (!isdigit(*pt) && *pt != '\0') pt++;

  //  if (*pt == '\0') return NULL;

  while (*pt && isdigit(*pt) && (pn-Buffer < sizeof(Buffer)-1)) *pn++ = *pt++;
  //  if (*pt && isdigit(*pt)) { *pn++ = *pt++; /*printf("Buffer[c] = %c\n", Buffer[0]); */}
  //  if (*pt && isdigit(*pt)) { *pn++ = *pt++; /*printf("Buffer[c] = %c\n", Buffer[1]);*/ }
  //...
  *pn = '\0';
  i = (WORD)atoi(Buffer);
  return pt;
}
//---------------------------------------------------------------------------
void __fastcall AnsiStringToSystemTime(
        const AnsiString &String,
        _SYSTEMTIME &SystemTime)
{
  /* Format 00.00.00 00:00 */
  PChar S;

  S = String.c_str();
  if ((S = search_token_dt(S, SystemTime.wDay)) != NULL)
        if ((S = search_token_dt(S, SystemTime.wMonth)) != NULL)
                if ((S = search_token_dt(S, SystemTime.wYear)) != NULL)
                        if ((S = search_token_dt(S, SystemTime.wHour)) != NULL)
                                if ((S = search_token_dt(S, SystemTime.wMinute)) != NULL)
                                        S = search_token_dt(S, SystemTime.wSecond);
}
//---------------------------------------------------------------------------
/*
double __fastcall SystemTimeToDouble(_SYSTEMTIME &SystemTime)
{
  double d;
  // Проанализировать возможность ошибки здесь.
  int    iDayInMonth = 30; // из расчета - 30 дней в месяце

  d =     SystemTime.wYear * 12 * iDayInMonth * 24 * 60
        + SystemTime.wMonth * iDayInMonth * 24 * 60
        + SystemTime.wDay * 24 * 60
        + SystemTime.wHour * 60
        + SystemTime.wMinute;
  return d;
}
*/
//---------------------------------------------------------------------------
AnsiString __fastcall SystemTimeToAnsiString(_SYSTEMTIME &SystemTime)
{
  return Format("%d/%d/%d %.2d:%.2d", OPENARRAY(TVarRec,(
                SystemTime.wDay,
                SystemTime.wMonth,
                SystemTime.wYear,
                SystemTime.wHour,
                SystemTime.wMinute
                )));
}
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::MemoryInformation(const AnsiString Block, bool VisibleMessage)
{
  AnsiString deliver = "-------------------------------------------------------- \n";
  TMemoryStatus MS;
  AnsiString Message, Buffer;
  static flag;

  MS.dwLength = sizeof(MS);
  GlobalMemoryStatus(&MS);

  //  Buffer = Now().DateTimeString().c_str();
  Message += deliver;
  Message += Buffer.sprintf("Block = %s\n", Block.c_str() );
  Message += Buffer.sprintf("flag = %d\n", flag );
  Message += Buffer.sprintf("Current datetime = %s\n", Now().DateTimeString().c_str() );
  Message += Buffer.sprintf("dwMemoryLoad = %u %%\n", MS.dwMemoryLoad);
  Message += Buffer.sprintf("dwTotalPhys = %u KB\n", MS.dwTotalPhys / 1024);
  Message += Buffer.sprintf("dwAvailPhys = %u KB\n", MS.dwAvailPhys / 1024);
  Message += Buffer.sprintf("dwTotalPageFile = %u\n", MS.dwTotalPageFile);
  Message += Buffer.sprintf("dwAvailPageFile = %u\n", MS.dwAvailPageFile);
  Message += Buffer.sprintf("dwTotalVirtual = %u KB\n", MS.dwTotalVirtual / 1024);
  Message += Buffer.sprintf("dwAvailVirtual = %u KB\n", MS.dwAvailVirtual / 1024);
  Message += deliver;
  //...
  if (VisibleMessage)
        ShowMessage(Message);
  //...
  FILE *in;
  if ((in = fopen("LOG.TXT", "at"))  == NULL)
        return;
  fwrite(Message.c_str(), Message.Length(), 1, in);
  fclose(in);

  flag = !flag;
}
//---------------------------------------------------------------------------
/* Поварачивает изображение на 90 градусов по часовой стрелке  */
/*
void Rotate(Graphics::TBitmap* Bitmap)
{
  Graphics::TBitmap* BMPTemp;
  Byte *ptr;
  Byte *newscanline;
  BMPTemp = new Graphics::TBitmap;

  BMPTemp->Assign(Bitmap);
  BMPTemp->Height = Bitmap->Width;
  BMPTemp->Width = Bitmap->Height;
//  BMPTemp->PixelFormat = Bitmap->PixelFormat;
//  BMPTemp->Palette = Bitmap->Palette;
  //
   for (int yNew = 0; yNew < BMPTemp->Height; yNew++)
   {
      newscanline = (Byte*)BMPTemp->ScanLine[yNew];
        for (int xNew= 0; xNew < BMPTemp->Width; xNew++)
        {
                ptr = (Byte*)Bitmap->ScanLine[Bitmap->Height - xNew - 1];//
                newscanline[xNew]= ptr[yNew];
        }
   }
  //


  //Jpg->SaveToFile(FileName);
  Bitmap->Height= BMPTemp->Height;
  Bitmap->Width= BMPTemp->Width;
//  Bitmap->Canvas->Draw(0,0, BMPTemp);
//  Bitmap->Assign(BMPTemp);

  BMPTemp->SaveToFile("C:\\BMPTemp.BMP");
  BMPTemp->Free();
}
*/
//---------------------------------------------------------------------------
void __fastcall TDBDiagram::Print()
{
  TPrinter *Prntr;
  
  Prntr= Printer();

  /* Получаем данные из базы данных */
  Request();
  /* Рисуем диаграмму */
  DoPaint(Graph->Canvas);
  Prntr->BeginDoc();
//  Prntr->Canvas->
  Prntr->Canvas->CopyRect(Prntr->Canvas->ClipRect, Graph->Canvas, Graph->Canvas->ClipRect);
  Prntr->EndDoc();
  Prntr->Free();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------



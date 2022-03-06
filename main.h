//---------------------------------------------------------------------------
// Borland C++Builder
// Copyright (c) 2001, Дипломная работа Герасименко Дмитрия Александровича
// Шифр: 54-0401
// gerasimenko@karelia.ru
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
//#include <SysUtils.hpp>
//#include <Classes.hpp>
//#include <DBTables.hpp>
//#include <SysInit.hpp>
//#include <System.hpp>
//#include <Controls.hpp>
//#include <Forms.hpp>
//#include <Messages.hpp>
//#include <Windows.hpp>
//#include <DSProd.hpp>
//#include <ADODB.hpp>
#include <IniFiles.hpp>
#include <DBWeb.hpp>
#include <ADODB.hpp>
#include <DSProd.hpp>
#include <Db.hpp>
#include <HTTPApp.hpp>
#include <Classes.hpp>
#include <stdio.h>
#include "diagram.h"
#include <set>

#ifndef _RWSTD_NO_NAMESPACE
  using namespace std;
#endif

//typedef std::set<std::string, std::allocator<std::string> >  TSetString;
typedef std::set<AnsiString, std::less<AnsiString>, std::allocator<AnsiString> > TSetAnsiString;
typedef std::set<AnsiString, std::less<AnsiString>, std::allocator<AnsiString> >::iterator TSetIteratorAnsiString;

//---------------------------------------------------------------------------
class TCInfoModule : public TWebModule
{
__published:	// IDE-managed Components
        TPageProducer *AdminPageProducer;
        TPageProducer *MainPageProducer;
        TPageProducer *SQLPageProducer;
        TPageProducer *ErrorPageProducer;
        TADOConnection *ADOConnection1;
        TADOQuery *ADOQuery;
        TDataSetTableProducer *ADODataSet;
        TPageProducer *ReportPageProducer;
        TPageProducer *Diagram_step1PageProducer;
        TDataSetPageProducer *ParametrNowPageProducer;
        TPageProducer *Diagram_step3PageProducer;
        TPageProducer *SQLDiagramPageProducer;
        TPageProducer *Diagram_step2PageProducer;
        TPageProducer *HeadReportProducer;
        TPageProducer *Diagram_step2SelectTablesPageProducer;
        TPageProducer *SQLFilePageProducer;
        void __fastcall RootHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall CustInfoModCreate(TObject *Sender);
        void __fastcall CInfoModuleConfigAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
        void __fastcall CInfoModuleMainAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
        void __fastcall AdminPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall pictureHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall MainPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall CInfoModuleReportAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
        void __fastcall SQLPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall ErrorPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall ADODataSetFormatCell(TObject *Sender, int CellRow,
          int CellColumn, THTMLBgColor &BgColor, THTMLAlign &Align,
          THTMLVAlign &VAlign, AnsiString &CustomAttrs,
          AnsiString &CellData);
        void __fastcall CInfoModuleerrorAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
        void __fastcall ReportPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall Diagram_step3PageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall IndexHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall ParametrNowPageProducerHTMLTag(TObject *Sender, TTag Tag,
          const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall CInfoModuleParametrNowAction(TObject *Sender,
          TWebRequest *Request, TWebResponse *Response, bool &Handled);
        void __fastcall SQLDiagramPageProducerHTMLTag(TObject *Sender,
          TTag Tag, const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall CInfoModuleWebActionDiagram_step1Action(
          TObject *Sender, TWebRequest *Request, TWebResponse *Response,
          bool &Handled);
        void __fastcall CInfoModuleWebActionDiagram_step2Action(
          TObject *Sender, TWebRequest *Request, TWebResponse *Response,
          bool &Handled);
        void __fastcall CInfoModuleWebActionDiagram_step3Action(
          TObject *Sender, TWebRequest *Request, TWebResponse *Response,
          bool &Handled);
        void __fastcall Diagram_step1PageProducerHTMLTag(TObject *Sender,
          TTag Tag, const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall Diagram_step2PageProducerHTMLTag(TObject *Sender,
          TTag Tag, const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall SQLFilePageProducerHTMLTag(TObject *Sender,
          TTag Tag, const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
        void __fastcall HeadReportProducerHTMLTag(TObject *Sender,
          TTag Tag, const AnsiString TagString, TStrings *TagParams,
          AnsiString &ReplaceText);
private:	// User declarations
        //------------------------------------------------------------------
        AnsiString   BufferError;
        AnsiString   FImageFileName;
        TStringList  *ini;
        TStringList  *FSections;
        TStrings *FQueryFields;
        //------------------------------------------------------------------
        void __fastcall DeleteImageFiles();
        void __fastcall ReadTableParametrs(TDBDiagram *DBDiagram);
        //
        void __fastcall ReadINIFIle();
        int __fastcall GetDaysInMonth(const iMonth);
        AnsiString __fastcall GetUserSQLRequest();
        AnsiString __fastcall GetFromDateTimeString();
        AnsiString __fastcall GetToDateTimeString();
        AnsiString __fastcall GetFormatDateTimeString(int iDay,
                int iMonth, int iYear, int iHour, int iMinute);
        AnsiString __fastcall GetConfig();
        AnsiString __fastcall OpenDatabase(AnsiString DatabaseName, AnsiString SQL);

        AnsiString __fastcall GetSQLText();
        AnsiString __fastcall GetSQLText(
        int iFromYear, int iFromMonth, int iFromDay, int iFromHour, int iFromMinute,
        int iToYear, int iToMonth, int iToDay, int iToHour, int iToMinute);

        AnsiString __fastcall GetHeader();
        //------------------------------------------------------------------
        void __fastcall GetDatabaseListYears(TStringList* List);
        AnsiString __fastcall GetWorkDatabaseName(TFileName FileName);
        //AnsiString __fastcall GetFromDatabaseFileName();
        //AnsiString __fastcall GetToDatabaseFileName();
        AnsiString __fastcall GetFromYearHTMLControl();
        AnsiString __fastcall GetFromMonthHTMLControl();
        AnsiString __fastcall GetFromDayHTMLControl();
        AnsiString __fastcall GetFromHourHTMLControl();
        AnsiString __fastcall GetFromMinuteHTMLControl();
        AnsiString __fastcall GetDiagrammFromDateTimeString();
        AnsiString __fastcall GetDiagrammToDateTimeString();
        AnsiString __fastcall GetToYearHTMLControl();
        AnsiString __fastcall GetToMonthHTMLControl();
        AnsiString __fastcall GetToDayHTMLControl();
        AnsiString __fastcall GetToHourHTMLControl();
        AnsiString __fastcall GetToMinuteHTMLControl();
        AnsiString __fastcall GetSelectTablesHTMLControl();        
        //------------------------------------------------------------------
        void __fastcall GetHTMLPath(TPageProducer* PageProducer);
        //------------------------------------------------------------------
        AnsiString __fastcall GenerateDiagramsName();
        //------------------------------------------------------------------
public:		// User declarations
	__fastcall TCInfoModule(TComponent* Owner);
        virtual __fastcall ~TCInfoModule();
};
//---------------------------------------------------------------------------
extern PACKAGE TCInfoModule *CInfoModule;
//---------------------------------------------------------------------------
#endif

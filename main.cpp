//---------------------------------------------------------------------------
// Borland C++Builder
// Copyright (c) 2001-2002, Герасименко Д.А.
// Информационная система Коммерческого Узла Учёта Ткплосчётчика СПТ961
// gerasimenko@karelia.ru
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include "main.h"
#include "string.h"

#include <io.h>
#include <dir.h>  #include "ADOOpenDatabase.h"
            /* for fnsplin */
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
TCInfoModule* CInfoModule;
AnsiString    sExtHtml = ".html";
//---------------------------------------------------------------------------
__fastcall TCInfoModule::TCInfoModule(TComponent* Owner)
	: TWebModule(Owner)
{
  ini = new TStringList();
  FQueryFields= new TStringList();
}
//---------------------------------------------------------------------------
__fastcall TCInfoModule::~TCInfoModule()
{
  ini->Free();
  FQueryFields->Free();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CustInfoModCreate(TObject *Sender)
{
  char drive[MAXDRIVE];
  char dir[MAXDIR];
  char file[MAXFILE];
  char ext[MAXEXT];
  int  flags;

  char* filename = new char[MAX_PATH - 1];
  GetModuleFileName(HInstance, filename,MAX_PATH-1);
  //-------------------------------------------------------------
  flags= fnsplit(filename, drive, dir, file, ext);
  if(flags & FILENAME)
  ini->Values["IniFileName"]=
  AnsiString(drive) + AnsiString(dir) + AnsiString(file) + AnsiString(".INI");
  // AnsiString().sprintf("%s%s%s".ini",drive,dir,file);
  //-------------------------------------------------------------
  ini->Values["ScriptName"]= AnsiString(file) + AnsiString(ext);
  ini->Values["CurrentDir"] = AnsiString(drive) + AnsiString(dir);

  delete[] filename;
  //--------------------------------------------------------------
  ReadINIFIle();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::ReadINIFIle()
{
  AnsiString tgNext = "<hr size=\"1\"><br>";
  AnsiString IniFileName = ini->Values["IniFileName"];
  //--------------------------------------------
  if (access(IniFileName.c_str(), 0)==0)
  {
        TIniFile     *IniFile  = new TIniFile(IniFileName);
        TStringList  *Sections = new TStringList();
        //--------------------------------------------
        IniFile->ReadSections(Sections);
        if (Sections->Count)
          IniFile->ReadSectionValues(Sections->Strings[0], ini);
        //--------------------------------------------
        delete Sections;
        delete IniFile;
  }
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::GetHTMLPath(TPageProducer* p)
{
  p->HTMLFile = ini->Values["HtmlDirectory"] + p->HTMLFile;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetConfig()
{
  AnsiString  Config;
  AnsiString  tgNext = "<hr size=\"1\"><br>";
  //---------------------------------------------------------
  Config  = "";
  Config += "<html><body></d>";
  Config += tgNext;
  Config += "<h3></h3><br>";
  //---------------------------------------------------------
  //*
  for (int i = 0; i< ini->Count; i++) {
          Config += ini->Strings[i];
          Config += "<br>";
  }
  //---------------------------------------------------------
  Config += "<br>";
  Config += "</d></body></html>";
  return Config;
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleConfigAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  GetHTMLPath(AdminPageProducer);
  Response->Content= AdminPageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleMainAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  GetHTMLPath(MainPageProducer);
  Response->Content= MainPageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleerrorAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  GetHTMLPath(ErrorPageProducer);
  Response->Content= ErrorPageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleReportAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  ini->AddStrings(Request->ContentFields);

  try {
/*
        AnsiString ContentString;
        TFileStream *fstream;

        try {
        GetHTMLPath(header);
        ContentString = header->Content();
        fstream = new TFileStream( header->HTMLFile + ".htm", fmCreate);
        fstream->Write(ContentString.c_str(), ContentString.Length() );
        }
         __finally
        {
                &fstream->Free;
        }
        //-----------------------------------------------
        try {
        GetHTMLPath(report);
        ContentString = report->Content();
        fstream = new TFileStream( report->HTMLFile + ".htm", fmCreate);
        fstream->Write(ContentString.c_str(), ContentString.Length() );
        }
         __finally
        {
                &fstream->Free;
        }

        GetHTMLPath(frame);
        Response->Content = frame->Content();
*/
        GetHTMLPath(ReportPageProducer);
//      GetHTMLPath(error);
        Response->Content= ReportPageProducer->Content(); // + <BR>" + error->Content();

  } catch(Exception& e){

        ini->Values["MESSAGE_ERROR"] = e.Message;
        GetHTMLPath(ErrorPageProducer);
        Response->Content= ErrorPageProducer->Content();
    }
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::RootHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() > 0)
        ReplaceText= ini->Values[TagString];

  if (TagString == AnsiString("MODULENAME")) {ReplaceText = ini->Values["ScriptName"];}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::AdminPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() > 0)
        ReplaceText= ini->Values[TagString];
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::pictureHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  AnsiString sExtJpg= ".jpg";
  AnsiString Customers= "";

  try
        {
        //-------------------------------------------------------------------------
        if (TagString==AnsiString("TITLE")) {ReplaceText= Customers;}
        //Customers= DiagramsQuery->FieldByName("ALIAS")->AsString + sExtJpg;
        //-------------------------------------------------------------------------
        if (TagString==AnsiString("IMAGEDIRECTORY")) {ReplaceText= ini->Values["ImageDirectory"];}
        if (TagString==AnsiString("PICTURE")) {ReplaceText= Customers;} // if
        //Customers= DiagramsQuery->FieldByName("NAME")->AsString + sExtJpg;
        } // try
  catch(EDatabaseError& e){
        String buf = e.Message + "\n" + "[void __fastcall TCInfoModule::pictureHTMLTag]";
        ReplaceText= buf;
  }
  catch(Exception& e){
        String buf = String(e.ClassName()) + " " + e.Message.c_str();
        ReplaceText=  buf;
  }
}
//-------------------------------------------------------------------------
void __fastcall TCInfoModule::MainPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);
  //------------------------------------------------------------
  if (TagString==AnsiString("ServerName"))     {ReplaceText= ini->Values[TagString];}
  if (TagString==AnsiString("ScriptName"))     {ReplaceText= ini->Values[TagString];}
  if (TagString==AnsiString("ImageDirectory")) {ReplaceText= ini->Values[TagString];}
  //------------------------------------------------------------
  if (TagString==AnsiString("FROM_YEAR"))  {ReplaceText= GetFromYearHTMLControl();}
  if (TagString==AnsiString("FROM_MONTH")) {ReplaceText= GetFromMonthHTMLControl();}
  if (TagString==AnsiString("FROM_DAY"))   {ReplaceText= GetFromDayHTMLControl();}
  if (TagString==AnsiString("FROM_HOUR"))  {ReplaceText= GetFromHourHTMLControl();}
  if (TagString==AnsiString("FROM_MINUTE")){ReplaceText= GetFromMinuteHTMLControl();}
  //------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))  {ReplaceText= GetToYearHTMLControl();}
  if (TagString==AnsiString("TO_MONTH")) {ReplaceText= GetToMonthHTMLControl();}
  if (TagString==AnsiString("TO_DAY"))   {ReplaceText= GetToDayHTMLControl();}
  if (TagString==AnsiString("TO_HOUR"))  {ReplaceText= GetToHourHTMLControl();}
  if (TagString==AnsiString("TO_MINUTE")){ReplaceText= GetToMinuteHTMLControl();}

  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::SQLPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];

  if (TagString==AnsiString("FROM_YEAR"))   {ReplaceText= ini->Values["FromYearControl"];}
  if (TagString==AnsiString("FROM_MONTH"))  {ReplaceText= ini->Values["FromMonthControl"];}
  if (TagString==AnsiString("FROM_DAY"))    {ReplaceText= ini->Values["FromDayControl"];}
  if (TagString==AnsiString("FROM_HOUR"))   {ReplaceText= ini->Values["FromHourControl"];}
  if (TagString==AnsiString("FROM_MINUTE")) {ReplaceText= ini->Values["FromMinuteControl"];}
  //------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))   {ReplaceText= ini->Values["ToYearControl"];}
  if (TagString==AnsiString("TO_MONTH"))  {ReplaceText= ini->Values["ToMonthControl"];}
  if (TagString==AnsiString("TO_DAY"))    {ReplaceText= ini->Values["ToDayControl"];}
  if (TagString==AnsiString("TO_HOUR"))   {ReplaceText= ini->Values["ToHourControl"];}
  if (TagString==AnsiString("TO_MINUTE")) {ReplaceText= ini->Values["ToMinuteControl"];}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::ErrorPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];

  if (TagString==AnsiString("VALUES")) {ReplaceText= GetConfig();}
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetHeader()
{
  AnsiString FileName;
  FileName= ini->Values["ReportDirectory"] + ini->Values["report"] + ".htm";
  //...
  HeadReportProducer->HTMLFile= FileName;
  return HeadReportProducer->Content();
}
//-----------------------------------------------------------------------------
void __fastcall TCInfoModule::ADODataSetFormatCell(TObject *Sender,
      int CellRow, int CellColumn, THTMLBgColor &BgColor,
      THTMLAlign &Align, THTMLVAlign &VAlign, AnsiString &CustomAttrs,
      AnsiString &CellData)
{
  if (CellRow == 0) return;
  //  Приводим данные формата: Tfloat к виду: 0.0
  if (CellColumn <= ADOQuery->FieldCount)
  {
        TFieldType FieldType = ADOQuery->Fields->Fields[CellColumn]->DataType;
        //----------------------------------------------------------
        if (FieldType == ftFloat)  {
          double FloatField;
          FloatField = ADOQuery->Fields->Fields[CellColumn]->AsFloat;
          CellData= FormatFloat(ini->Values["FormatFloat"], FloatField);

                // Добавлено 26 февраля 2004 г.
                // Отрицательные значения общей подпитки
                //  выделяем в красный цвет.
                if (FloatField < 0.0) {
                        BgColor= "Lime"; //"Red";
                }
        }
        //----------------------------------------------------------
        if ((FieldType==ftDateTime) && (CellColumn==0))  {
           TDateTime Date = ADOQuery->Fields->Fields[CellColumn]->AsDateTime;
           CellData= Date.DateString();
         }
        //----------------------------------------------------------
        if ((FieldType==ftDateTime) && (CellColumn==1))  {
           TDateTime Time= ADOQuery->Fields->Fields[CellColumn]->AsDateTime;
           CellData= Time.FormatString("hh:nn");
         }
        //----------------------------------------------------------
        if (CellColumn == 0 || CellColumn == 1) {
                BgColor= "Yellow";
        }

  }
}
//---------------------------------------------------------------------------
//  Response->SendRedirect(AnsiString("http://132.171.86.120/"));
void __fastcall TCInfoModule::ReportPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];

  //------------------------------------------------
  if ( TagString==AnsiString("DATA")) {ReplaceText= GetUserSQLRequest();}
  //------------------------------------------------
  if (TagString==AnsiString("HEADER")) {ReplaceText= GetHeader();}
  //------------------------------------------------
  if (TagString==AnsiString("FROM_YEAR"))   {ReplaceText= ini->Values["FromYearControl"];}
  if (TagString==AnsiString("FROM_MONTH"))  {ReplaceText= ini->Values["FromMonthControl"];}
  if (TagString==AnsiString("FROM_DAY"))    {ReplaceText= ini->Values["FromDayControl"];}
  if (TagString==AnsiString("FROM_HOUR"))   {ReplaceText= ini->Values["FromHourControl"];}
  if (TagString==AnsiString("FROM_MINUTE")) {ReplaceText= ini->Values["FromMinuteControl"];}
  //------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))   {ReplaceText= ini->Values["ToYearControl"];}
  if (TagString==AnsiString("TO_MONTH"))  {ReplaceText= ini->Values["ToMonthControl"];}
  if (TagString==AnsiString("TO_DAY"))    {ReplaceText= ini->Values["ToDayControl"];}
  if (TagString==AnsiString("TO_HOUR"))   {ReplaceText= ini->Values["ToHourControl"];}
  if (TagString==AnsiString("TO_MINUTE")) {ReplaceText= ini->Values["ToMinuteControl"];}
  if (TagString==AnsiString("CURENT_DATETIME")) {ReplaceText= Now();}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleWebActionDiagram_step1Action(
      TObject *Sender, TWebRequest *Request, TWebResponse *Response,
      bool &Handled)
{
  ini->AddStrings(Request->ContentFields);
  ini->AddStrings(Request->QueryFields);

  GetHTMLPath(Diagram_step1PageProducer);
  Response->Content= Diagram_step1PageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleWebActionDiagram_step2Action(
      TObject *Sender, TWebRequest *Request, TWebResponse *Response,
      bool &Handled)
{
  ini->AddStrings(Request->ContentFields);
  ini->AddStrings(Request->QueryFields);

  FQueryFields->Assign(Request->QueryFields);

  // Если пользователь забыл выбрать параметры
  // возвращаем его обратно в окно выбора параметров
  if (Request->QueryFields->Count <= 1)
  {
        GetHTMLPath(Diagram_step1PageProducer);
        Response->Content= Diagram_step1PageProducer->Content();
        return;
  }
  GetHTMLPath(Diagram_step2PageProducer);
  Response->Content= Diagram_step2PageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleWebActionDiagram_step3Action(
      TObject *Sender, TWebRequest *Request, TWebResponse *Response,
      bool &Handled)
{
  TDBDiagram* diagrama = new TDBDiagram(this);
  AnsiString Buffer, DataTime, Value, DatabaseFileName, TableName, SELECT_TABLES;
  TStringList *Tables= new TStringList();

  ini->AddStrings(Request->ContentFields);

  try
  {
      try
      {
        // Удаляем все старые диаграммы с диска.
        // Тем самым освобождаем место на диске.
        DeleteImageFiles();
        //
        ReadTableParametrs(diagrama);

        DatabaseFileName= ini->Values["FromMonthControl"] + ini->Values["FromYearControl"] + ".mdb";
        diagrama->DatabaseName= ini->Values["DataBaseDirectory"] + GetWorkDatabaseName(DatabaseFileName);

        SELECT_TABLES= "SELECT_TABLES_"; // SELECT_TABLES

        for (int i=0; i < ini->Count; i++)
        {
                if (strncmp(SELECT_TABLES.c_str(), ini->Names[i].c_str(), SELECT_TABLES.Length()) == 0) //  ==
                {
                        TableName = ini->Names[i].SubString(SELECT_TABLES.Length() + 1, ini->Names[i].Length());
                        Tables->Add(TableName);
                        Buffer= ini->Values[TableName + AnsiString("_name")];
                        Buffer += " ";
                        Buffer += "(";
                        Buffer += ini->Values[TableName + AnsiString("_extended")];
                        Buffer += ")";
                        diagrama->TableNames->Add(Buffer);
                        //Tables += (ini->Names[i].SubString(Buffer.Length() + 1, ini->Names[i].Length()) + ", ");
                }
        }
        //--------------------------------------------------------------------
        for (int I = 0; I < diagrama->TableNames->Count; I ++)
        {
                Buffer= "TABLE_NAME" + IntToStr(1 + I);
                ini->Values[Buffer]= Tables->Strings[I];
        }

        ini->Values["FROM_YEAR"]  = ini->Values["FromYearControl"];
        ini->Values["FROM_MONTH"] = ini->Values["FromMonthControl"];
        ini->Values["FROM_DAY"]   = ini->Values["FromDayControl"];
        ini->Values["FROM_HOUR"]  = ini->Values["FromHourControl"];
        ini->Values["FROM_MINUTE"]= ini->Values["FromMinuteControl"];
        //------------------------------------------------------------
        ini->Values["TO_YEAR"]   = ini->Values["FromYearControl"];
        ini->Values["TO_MONTH"]  = ini->Values["FromMonthControl"];
        ini->Values["TO_DAY"]    = ini->Values["ToDayControl"];
        ini->Values["TO_HOUR"]   = ini->Values["ToHourControl"];
        ini->Values["TO_MINUTE"] = ini->Values["ToMinuteControl"];

        Buffer.sprintf("%s_%d.sql", ini->Values["SQLFILENAME"].c_str(), diagrama->TableNames->Count);
        SQLFilePageProducer->HTMLFile= Buffer;
        diagrama->SQL= SQLFilePageProducer->Content();

        //GetHTMLPath(SQLFilePageProducer);
//        Response->Content= SQLFilePageProducer->Content();

//        GetHTMLPath(ErrorPageProducer);
//        Response->Content= ErrorPageProducer->Content() + SQLFilePageProducer->Content();
//        return;
        //--------------------------------------------------------------------
//        diagrama->TablesCount= diagrama->TableNames->;

        diagrama->From= GetDiagrammFromDateTimeString();
        diagrama->To= GetDiagrammToDateTimeString();

        ini->Values["DIAGRAM_FILENAME"]= 
        diagrama->SaveToFile(ini->Values["DiagramImageDirectory"]);

        GetHTMLPath(Diagram_step3PageProducer);
        Response->Content= Diagram_step3PageProducer->Content();

        //GetHTMLPath(ErrorPageProducer);
        // + ErrorPageProducer->Content()

        //        Response->Content= ErrorPageProducer->Content() + SQLFilePageProducer->Content();
        //--------------------------------------------------------------------
        /*
        // Рисуем диаграмму в памяти. Сохраняем её на диске сервера.
        // И отправляем её к чёртовой матери (клиенту)...
        //
        ini->Values["DIAGRAM_FILENAME"]= diagrama->SaveToFile(ini->Values["DiagramImageDirectory"]);
        GetHTMLPath(Diagram_step3PageProducer);
        Response->Content= Diagram_step3PageProducer->Content();
        */
      }
      catch(Exception& e)
      {
        ini->Values["MESSAGE_ERROR"]= e.Message;
        GetHTMLPath(ErrorPageProducer);
        Response->Content= ErrorPageProducer->Content();
      }
  }
  __finally
  {
        &diagrama->Free;
        Tables->Free();
  }
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::IndexHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::ParametrNowPageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::CInfoModuleParametrNowAction(TObject *Sender,
      TWebRequest *Request, TWebResponse *Response, bool &Handled)
{
  GetHTMLPath(ParametrNowPageProducer);
  Response->Content= ParametrNowPageProducer->Content();
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::ReadTableParametrs(TDBDiagram *diagrama)
{
  AnsiString Buffer;
  int iTemp;
  //-------------------------------------------------------------------
  diagrama->Height = StrToInt(ini->Values["Height"]);
  diagrama->Width  = StrToInt(ini->Values["Width"]);
  diagrama->BackgroundInformation = (TColor)(StrToInt(ini->Values["BackgroundInformation"]));
  diagrama->BackgroundLeft   = (TColor)(StrToInt(ini->Values["BackgroundLeft"]));
  diagrama->BackgroundRight  = (TColor)(StrToInt(ini->Values["BackgroundRight"]));
  diagrama->BackgroundTop    = (TColor)(StrToInt(ini->Values["BackgroundTop"]));
  diagrama->BackgroundBottom = (TColor)(StrToInt(ini->Values["BackgroundBottom"]));
  diagrama->BackgroundGraph  = (TColor)(StrToInt(ini->Values["BackgroundGraph"]));
  diagrama->BackgroundPen    = (TColor)(StrToInt(ini->Values["BackgroundPen"]));
  diagrama->ForegroundInformation = (TColor)(StrToInt(ini->Values["ForegroundInformation"]));
  diagrama->ForegroundLeft   = (TColor)(StrToInt(ini->Values["ForegroundLeft"]));
  diagrama->ForegroundRight  = (TColor)(StrToInt(ini->Values["ForegroundRight"]));
  diagrama->ForegroundTop    = (TColor)(StrToInt(ini->Values["ForegroundTop"]));
  diagrama->ForegroundBottom = (TColor)(StrToInt(ini->Values["ForegroundBottom"]));
  diagrama->ForegroundGraph  = (TColor)(StrToInt(ini->Values["ForegroundGraph"]));
  diagrama->ForegroundPen    = (TColor)(StrToInt(ini->Values["ForegroundPen"]));
  diagrama->ForegroundBorder = (TColor)(StrToInt(ini->Values["ForegroundBorder"]));

  diagrama->BackgroundDiagramNames       = (TColor)(StrToInt(ini->Values["BackgroundDiagramNames"]));
  diagrama->BackgroundDiagramNumeric     = (TColor)(StrToInt(ini->Values["BackgroundDiagramNumeric"]));
  diagrama->BackgroundDiagramNumericLabel= (TColor)(StrToInt(ini->Values["BackgroundDiagramNumericLabel"]));
  diagrama->ForegroundDiagramNames       = (TColor)(StrToInt(ini->Values["ForegroundDiagramNames"]));
  diagrama->ForegroundDiagramNumeric     = (TColor)(StrToInt(ini->Values["ForegroundDiagramNumeric"]));
  diagrama->ForegroundDiagramNumericLabel= (TColor)(StrToInt(ini->Values["ForegroundDiagramNumericLabel"]));

  diagrama->DiagramaNumericPenWidth= StrToInt(ini->Values["DiagramaNumericPenWidth"]);
  //-------------------------------------------------------------------
  diagrama->FontInformation->Size= StrToInt(ini->Values["FontInformation->Size"]);
  diagrama->FontDateTime->Name= ini->Values["FontDateTime->Name"];

  diagrama->FontDiagramNames->Size= StrToInt(ini->Values["FontDiagramNames->Size"]);
  diagrama->FontDiagramNames->Name= ini->Values["FontDiagramNames->Name"];

  diagrama->FontDiagramNumeric->Size= StrToInt(ini->Values["FontDiagramNumeric->Size"]);
  diagrama->FontDiagramNumeric->Name= ini->Values["FontDiagramNumeric->Name"];

  // Меняет угол поворота на исходную.
  //diagrama->FontRange->Size= StrToInt(ini->Values["FontRange->Size"]);
  //diagrama->FontRange->Name= ini->Values["FontRange->Name"];

  diagrama->FontDateTime->Size= StrToInt(ini->Values["FontDateTime->Size"]);
  diagrama->FontDateTime->Name= ini->Values["FontDateTime->Name"];
  //-------------------------------------------------------------------
  diagrama->Border= (bool)StrToInt(ini->Values["Border"]);
  diagrama->HeightStyle= (TDiagramSizeStyle)StrToInt(ini->Values["HeightStyle"]);
  diagrama->MaxHeight= StrToInt(ini->Values["MaxHeight"]);
  diagrama->MinHeight= StrToInt(ini->Values["MinHeight"]);
  diagrama->MaxWidth= StrToInt(ini->Values["MaxWidth"]);
  diagrama->MinWidth= StrToInt(ini->Values["MinWidth"]);
  diagrama->PenWidth= StrToInt(ini->Values["PenWidth"]);
  diagrama->CopyrightInfo= ini->Values["CopyrightInfo"];
  diagrama->AutoMax= (bool)StrToInt(ini->Values["AutoMax"]);
  diagrama->AutoMin= (bool)StrToInt(ini->Values["AutoMin"]);
  diagrama->PixelsInData= StrToInt(ini->Values["PixelsInData"]);
  //-------------------------------------------------------------------
  Buffer= ini->Values["SQLFILENAME"] + "_min";
  diagrama->Min= StrToFloat(ini->Values[Buffer]);
  Buffer= ini->Values["SQLFILENAME"] + "_max";
  diagrama->Max= StrToFloat(ini->Values[Buffer]);
  //-------------------------------------------------------------------
  /* Находим минимум */
  iTemp= StrToInt(ini->Values["MinControl"]);
  switch(iTemp)
  {
        case 0: // Оптимальное значение из файла конфигурации
        break;
        case 1: // Минимальное значение из запрошенного диапазона
                diagrama->AutoMin= true;
        break;
        case 2: // определить минимум :
                diagrama->AutoMin= false;
                diagrama->Min= StrToFloat(ini->Values["MinValue"]);
        break;
        default : break;
        }
  //-------------------------------------------------------------------
  /* Находим максимум */
  iTemp= StrToInt(ini->Values["MaxControl"]);
  switch(iTemp)
  {       // Оптимальное значение из файла конфигурации
        case 0:break;
        case 1: // Минимальное значение из запрошенного диапазона
                diagrama->AutoMax= true;
        break;
        case 2: // определить минимум :
                diagrama->AutoMax= false;
                diagrama->Max= StrToFloat(ini->Values["MaxValue"]);
        break;
        default : break;
  }
  //-------------------------------------------------------------------
  /* Читаем высоту графика из HTML формы */
  iTemp= StrToInt(ini->Values["HeightDiagramControl"]);
  switch(iTemp)
  {       // Автоопределение.
                // Высота вычисляется- шаг диаграммы * количество записей
                // шаг диаграммы. пиксели/одно значение.
                // Нужна, если  HeightStyle= 0 [wsRecordCount]
                // PixelsInData= 5
        case 0:
        break;
                // Разместить на листе формата А4
                // wsRecordCount, wsDateTime, wsFixed
        case 1:
                diagrama->HeightStyle= wsFixed;
                diagrama->Height= StrToInt(ini->Values["MaxPixelsInPageHeight"]);
        break;
        case 2: // определить высоту в пикселях :
                diagrama->HeightStyle= wsFixed;
                diagrama->Height= StrToInt(ini->Values["HeightDiagramValue"]);
        break;
        default : break;
        }
        //-------------------------------------------------------------------
        /* Читаем ширину графика из HTML формы */
        iTemp= StrToInt(ini->Values["WidthDiagramControl"]);
        switch(iTemp)
        {       // Автоопределение.
                // Ширина вычисляется- шаг диаграммы * количество записей
                // шаг диаграммы. пиксели/одно значение.
                // Нужна, если  HeightStyle= 0 [wsRecordCount]
                // PixelsInData= 5
                case 0:
                break;
                // Разместить на листе формата А4
                // wsRecordCount, wsDateTime, wsFixed
                case 1:
                        diagrama->Width= StrToInt(ini->Values["MaxPixelsInPageWidth"]);
                break;
                case 2: // определить высоту в пикселях :
                        diagrama->Width= StrToInt(ini->Values["WidthDiagramValue"]);
                break;
                default : break;
        }
  //-------------------------------------------------------------------
  //diagrama->AutoRange = true;
  //-------------------------------------------------------------------
/*
  } catch(Exception& e){
        AnsiString Message = "Value = " + Value + e.Message;
        ShowMessage(Message);
  }
*/
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::DeleteImageFiles()
{
   AnsiString Path;
   Path= ini->Values["DiagramImageDirectory"] + AnsiString("*.jpg");  // AnsiString("clear.bat"); //

   WIN32_FIND_DATA FindFileData;
   HANDLE hFirstFileHandle = FindFirstFile( Path.c_str(), &FindFileData );

   while ( hFirstFileHandle )
   {
        Path= ini->Values["DiagramImageDirectory"] + AnsiString(FindFileData.cFileName);
        DeleteFile(Path);
        if ( FindNextFile( hFirstFileHandle, &FindFileData ) == FALSE )
		   break;
   }
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::GetDatabaseListYears(TStringList* List)
{
  TSetAnsiString FSetAnsiString;
  TSetIteratorAnsiString FSetIteratorAnsiString;
  AnsiString SearchPath;
  SYSTEMTIME localtime;

  GetLocalTime(&localtime);

  if (List == NULL) return;

  SearchPath= ini->Values["DatabaseDirectory"] + AnsiString("*.mdb");

  WIN32_FIND_DATA FindFileData;
  HANDLE hFirstFileHandle= FindFirstFile( SearchPath.c_str(), &FindFileData );

  //
  // Добавляем текущий год, т.к. оен по любому должен быть
  //
  FSetAnsiString.insert( AnsiString(localtime.wYear) );

  while ( hFirstFileHandle )
  {
        //
        //
        if ( isdigit(FindFileData.cFileName[2])    &&
                isdigit(FindFileData.cFileName[3]) &&
                isdigit(FindFileData.cFileName[4]) &&
                isdigit(FindFileData.cFileName[5]))
        {
                FindFileData.cFileName[6]= '\0';
                char *pstr= &FindFileData.cFileName[2];
                FSetAnsiString.insert( AnsiString(pstr) );
        }

        if ( FindNextFile( hFirstFileHandle, &FindFileData ) == FALSE )
		   break;
  }
  // Переписываем данные в TStringList
  //
  List->Clear();
  FSetIteratorAnsiString= FSetAnsiString.begin();
  while ( FSetIteratorAnsiString != FSetAnsiString.end() )
  {
        //printf("Строка = <%s>\n", (*list_iterator).c_str());
        // advance( list_iterator, 1);
        List->Add( (*FSetIteratorAnsiString) );
        FSetIteratorAnsiString++;
    }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetWorkDatabaseName(TFileName FileName)
{
  AnsiString Today;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);
  Today.sprintf("%.2d%.2d.mdb", localtime.wMonth, localtime.wYear);
  if (Today == FileName) {
        return ini->Values["CurrentDatabaseName"];
  } else {
        return FileName;
  }
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromYearHTMLControl()
{
  AnsiString HTMLControl;
  AnsiString IsSelected;
  TStringList *ListYear= new TStringList;
  SYSTEMTIME localtime;

  GetLocalTime(&localtime);
  GetDatabaseListYears(ListYear);

  HTMLControl = "<SELECT NAME=\"FromYearControl\">\n";
  for (int i = 0; i < ListYear->Count; i ++)
  {
        if (StrToInt(ListYear->Strings[i]) == localtime.wYear )
                IsSelected= "SELECTED";
        else
                IsSelected= "";
        HTMLControl += (("<OPTION " + IsSelected + " VALUE=" + ListYear->Strings[i] + ">" + ListYear->Strings[i] + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";

  ListYear->Free();
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromMonthHTMLControl()
{
  AnsiString HTMLControl, SELECTED, Format;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);

  HTMLControl = "<SELECT NAME=\"FromMonthControl\">\n";
  for (int i = 1; i <= 12; i ++)
  {
        SELECTED= (i==localtime.wMonth) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromDayHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);

  HTMLControl = "<SELECT NAME=\"FromDayControl\">\n";
  for (int i = 1; i <= 31; i ++)
  {
        SELECTED= (i==localtime.wDay) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";

  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromHourHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);

  HTMLControl = "<SELECT NAME=\"FromHourControl\">\n";
  for (int i = 0; i <= 23; i ++)
  {
        SELECTED= (i==0) ? "SELECTED" : ""; // localtime.wHour
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";

  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromMinuteHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);

  HTMLControl = "<SELECT NAME=\"FromMinuteControl\">\n";
  for (int i = 0; i <= 59; i ++)
  {
        SELECTED= (i==0) ? "SELECTED" : ""; // localtime.wMinute
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";

  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToYearHTMLControl()
{
  AnsiString HTMLControl;
  AnsiString IsSelected;
  TStringList *ListYear= new TStringList;
  SYSTEMTIME localtime;

  GetLocalTime(&localtime);
  GetDatabaseListYears(ListYear);

  HTMLControl = "<SELECT NAME=\"ToYearControl\">\n";
  for (int i = 0; i < ListYear->Count; i ++)
  {
        if (StrToInt(ListYear->Strings[i]) == localtime.wYear )
                IsSelected= "SELECTED";
        else
                IsSelected= "";

        HTMLControl += (("<OPTION " + IsSelected + " VALUE=" + ListYear->Strings[i] + ">" + ListYear->Strings[i] + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";

  ListYear->Free();
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToMonthHTMLControl()
{
  AnsiString HTMLControl, SELECTED, Format;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);

  HTMLControl = "<SELECT NAME=\"ToMonthControl\">\n";
  for (int i = 1; i <= 12; i ++)
  {
        SELECTED= (i==localtime.wMonth) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToDayHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);
  HTMLControl = "<SELECT NAME=\"ToDayControl\">\n";
  for (int i = 1; i <= 31; i ++)
  {
        SELECTED= (i==localtime.wDay) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToHourHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);
  HTMLControl = "<SELECT NAME=\"ToHourControl\">\n";
  for (int i = 0; i <= 23; i ++)
  {
        SELECTED= (i==localtime.wHour) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToMinuteHTMLControl()
{
  AnsiString HTMLControl, Format, SELECTED;
  SYSTEMTIME localtime;
  GetLocalTime(&localtime);
  HTMLControl = "<SELECT NAME=\"ToMinuteControl\">\n";
  for (int i = 0; i <= 59; i ++)
  {
        SELECTED= (i==localtime.wMinute) ? "SELECTED" : "";
        Format.sprintf("%.2d", i);
        HTMLControl += (("<OPTION " + SELECTED + " VALUE=" + Format + ">" + Format + "</OPTION>\n"));
  }
  HTMLControl += "</SELECT>";
  return HTMLControl;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetSelectTablesHTMLControl()
{
  AnsiString HTMLControl, HTMLFormat, Format, Name, Extended;
  GetHTMLPath(Diagram_step2SelectTablesPageProducer);
  for (int i = 1; i < FQueryFields->Count; i++ )
  {
        Name= FQueryFields->Names[i] + "_" + "name";
        Extended= FQueryFields->Names[i] + "_" + "extended";

        Format.sprintf(Diagram_step2SelectTablesPageProducer->Content().c_str(),
                FQueryFields->Names[i].c_str(),
                ini->Values[Name].c_str(),
                ini->Values[Extended].c_str()
                );
        HTMLControl += Format;
  }
  return HTMLControl;
}
//---------------------------------------------------------------------------
int __fastcall TCInfoModule::GetDaysInMonth(const iMonth)
{
  // количество дней в Месяце
  int iDaysInMonth[13]= { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
  int iVisikosniyYear= 2000;
  SYSTEMTIME localtime;

  if (iMonth == 2)
  {
        GetLocalTime(&localtime);
        iVisikosniyYear= localtime.wYear - iVisikosniyYear;
        if (!(iVisikosniyYear%4))
                iDaysInMonth[iMonth] ++;
  }
  return iDaysInMonth[iMonth];
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFromDateTimeString()
{
  AnsiString DateTimeString;
  DateTimeString.sprintf(
        "%.2d.%.2d.%.2d %.2d:%.2d",
        atoi( ini->Values["FromDayControl"].c_str()),
        atoi( ini->Values["FromMonthControl"].c_str()),
        atoi( ini->Values["FromYearControl"].c_str()),
        atoi( ini->Values["FromHourControl"].c_str()),
        atoi( ini->Values["FromMinuteControl"].c_str())
        );
  return DateTimeString;
}
//--------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetToDateTimeString()
{
  AnsiString DateTimeString;
  DateTimeString.sprintf(
        "%.2d.%.2d.%.2d %.2d:%.2d",
        atoi( ini->Values["ToDayControl"].c_str()),
        atoi( ini->Values["ToMonthControl"].c_str()),
        atoi( ini->Values["ToYearControl"].c_str()),
        atoi( ini->Values["ToHourControl"].c_str()),
        atoi( ini->Values["ToMinuteControl"].c_str())
        );
  return DateTimeString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetDiagrammFromDateTimeString()
{
  AnsiString DateTimeString;
  DateTimeString.sprintf(
        "%.2d.%.2d.%.2d %.2d:%.2d",
        atoi( ini->Values["FromDayControl"].c_str()),
        atoi( ini->Values["FromMonthControl"].c_str()),
        atoi( ini->Values["FromYearControl"].c_str()),
        atoi( ini->Values["FromHourControl"].c_str()),
        atoi( ini->Values["FromMinuteControl"].c_str())
        );
  return DateTimeString;
}
//--------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetDiagrammToDateTimeString()
{
  AnsiString DateTimeString;
  DateTimeString.sprintf(
        "%.2d.%.2d.%.2d %.2d:%.2d",
        atoi( ini->Values["ToDayControl"].c_str()),
        atoi( ini->Values["FromMonthControl"].c_str()),
        atoi( ini->Values["FromYearControl"].c_str()),
        atoi( ini->Values["ToHourControl"].c_str()),
        atoi( ini->Values["ToMinuteControl"].c_str())
        );
  return DateTimeString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetFormatDateTimeString(int iDay,
                int iMonth, int iYear, int iHour, int iMinute)
{
  AnsiString DateTimeString;
  DateTimeString.sprintf(
  "%.2d.%.2d.%.2d %.2d:%.2d", iDay, iMonth, iYear, iHour, iMinute);
  return DateTimeString;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::OpenDatabase(AnsiString DatabaseName, AnsiString SQLString)
{
  AnsiString ConnectionString= "Provider=MSDataShape.1;Persist Security Info=True;Data Source=%s%s;Data Provider=Microsoft.Jet.OLEDB.4.0";
  ADOConnection1->Connected= false;
  ADOConnection1->ConnectionString= Format(ConnectionString, OPENARRAY(TVarRec,(
                                        ini->Values["DataBaseDirectory"],
                                        DatabaseName
                                        )));
  ADOConnection1->Connected = true;
  ADOQuery->Close();
  ADOQuery->SQL->Clear();
  ADOQuery->SQL->Add( SQLString);
  ADOQuery->Open();

  // Если данных в SQL запросе нет, то HTML код не создаём
  //
  if (ADOQuery->RecordCount > 0) {
        /*
        AnsiString Info("The fields are: ");
        int Min[10];
        int Max[10];
        ADOQuery->First();
        while ( !(ADOQuery->Eof))
        {
                double dData= ADOQuery->Fields->Fields[0]->AsFloat;
                for(int i= 0; i < ADOQuery->FieldCount; i++)
                        Info= Info + ADOQuery->Fields->Fields[i]->FieldName + ", ";
                ADOQuery->Next();
        }

        Info += "<BR>";
        */
        ADODataSet->MaxRows= StrToInt(ini->Values["MaxRows"]);
        return ADODataSet->Content();
  } else
        return AnsiString("");
}
//-----------------------------------------------------------------------------
// Возвращает SQL запрос по умолчанию
AnsiString __fastcall TCInfoModule::GetSQLText()
{
  AnsiString  FileName;
  FileName= ini->Values["ReportDirectory"] + ini->Values["report"] + ".sql";
  SQLPageProducer->HTMLFile= FileName;
  return SQLPageProducer->Content();
}
//--------------------------------------------------------------------------
//
AnsiString __fastcall TCInfoModule::GetSQLText(
int iFromYear, int iFromMonth, int iFromDay, int iFromHour, int iFromMinute,
int iToYear, int iToMonth, int iToDay, int iToHour, int iToMinute)
{
  AnsiString  FileName, SQLText;
  FileName= ini->Values["ReportDirectory"] + ini->Values["report"] + ".sql";
  SQLPageProducer->HTMLFile= FileName;
  SQLText= SQLPageProducer->Content();
  return SQLText;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GetUserSQLRequest()
{
  AnsiString Reguest, DatabaseFileName, SQLText;
  AnsiString RangeDateTime[10];
  int FromYear= atoi(ini->Values["FromYearControl"].c_str());
  int ToYear= atoi(ini->Values["ToYearControl"].c_str());
  int FromMonth, FromDay, FromHour, FromMinute;
  int ToMonth, ToDay, ToHour, ToMinute;
  int From, To;
  bool IsReportTypeControl= (ini->Values["ReportTypeControl"].Length() > 0);

  /*
  From= min(FromYear,ToYear);
  To= max(FromYear,ToYear);
  FromYear= From;
  ToYear= To;
  */
  // GetWorkDatabaseName("")

  for (int iYear= FromYear; iYear <= ToYear; iYear++ )
  {
        FromMonth= 1;
        ToMonth= 12;
        if (IsReportTypeControl || (iYear == FromYear))
        {
                FromMonth= atoi(ini->Values["FromMonthControl"].c_str());
        }
        if (IsReportTypeControl || (iYear == ToYear))
        {
                ToMonth= atoi(ini->Values["ToMonthControl"].c_str());
        }

        //FromMonth  = atoi(ini->Values["FromMonthControl"].c_str());
        //ToMonth  = atoi(ini->Values["ToMonthControl"].c_str());

        for (int iMonth= FromMonth; iMonth <= ToMonth; iMonth++ )
        {
                FromDay= 1;
                FromHour= 0;
                FromMinute= 0;
                ToDay= GetDaysInMonth(iMonth);
                ToHour= 23;
                ToMinute= 59;

                if (iMonth == FromMonth)
                {
                        FromDay    = atoi(ini->Values["FromDayControl"].c_str());
                        FromHour   = atoi(ini->Values["FromHourControl"].c_str());
                        FromMinute = atoi(ini->Values["FromMinuteControl"].c_str());
                }
                if (iMonth == ToMonth)
                {
                        ToDay    = atoi(ini->Values["ToDayControl"].c_str());
                        ToHour   = atoi(ini->Values["ToHourControl"].c_str());
                        ToMinute = atoi(ini->Values["ToMinuteControl"].c_str());
                }
                /*
                // Если выбрана "Выводить заданный фрагмент в каждом месяце"
                if (IsReportTypeControl)
                {
                        FromDay    = atoi(ini->Values["FromDayControl"].c_str());
                        FromHour   = atoi(ini->Values["FromHourControl"].c_str());
                        FromMinute = atoi(ini->Values["FromMinuteControl"].c_str());

                        ToDay    = atoi(ini->Values["ToDayControl"].c_str());
                        ToHour   = atoi(ini->Values["ToHourControl"].c_str());
                        ToMinute = atoi(ini->Values["ToMinuteControl"].c_str());

                        if (FromDay > ToDay)
                                ToDay= GetDaysInMonth(iMonth);
                        if (FromHour > ToHour)
                                ToHour= 23;
                        if (FromMinute > ToMinute)
                                FromMinute= 59;
                }
                */
                /*
                FromDay    = atoi(ini->Values["FromDayControl"].c_str());
                FromHour   = atoi(ini->Values["FromHourControl"].c_str());
                FromMinute = atoi(ini->Values["FromMinuteControl"].c_str());
                ToDay    = atoi(ini->Values["ToDayControl"].c_str());
                ToHour   = atoi(ini->Values["ToHourControl"].c_str());
                ToMinute = atoi(ini->Values["ToMinuteControl"].c_str());
                */
                DatabaseFileName.sprintf("%.2d%.2d.mdb", iMonth, iYear);
                if ( FileExists(ini->Values["DataBaseDirectory"] + GetWorkDatabaseName(DatabaseFileName)) )
                {
                        /*
                        Reguest += "<B><A>";
                        Reguest += "DatabaseFileName= ";
                        Reguest += GetWorkDatabaseName(DatabaseFileName);
                        Reguest += "<BR>";
                        Reguest += "SQLText= ";
                        Reguest += SQLText;
                        Reguest += "</A></B><BR>";
                        */
                        //-----------------------------------------------------
                        // Сохраняем
                        RangeDateTime[0]= ini->Values["FromYearControl"];
                        RangeDateTime[1]= ini->Values["FromMonthControl"];
                        RangeDateTime[2]= ini->Values["FromDayControl"];
                        RangeDateTime[3]= ini->Values["FromHourControl"];
                        RangeDateTime[4]= ini->Values["FromMinuteControl"];
                        RangeDateTime[5]= ini->Values["ToYearControl"];
                        RangeDateTime[6]= ini->Values["ToMonthControl"];
                        RangeDateTime[7]= ini->Values["ToDayControl"];
                        RangeDateTime[8]= ini->Values["ToHourControl"];
                        RangeDateTime[9]= ini->Values["ToMinuteControl"];
                        // Меняем
                        ini->Values["FromYearControl"]  = IntToStr(iYear);
                        ini->Values["FromMonthControl"] = IntToStr(iMonth);
                        ini->Values["FromDayControl"]   = IntToStr(FromDay);
                        ini->Values["FromHourControl"]  = IntToStr(FromHour);
                        ini->Values["FromMinuteControl"]= IntToStr(FromMinute);
                        ini->Values["ToYearControl"]    = IntToStr(iYear);
                        ini->Values["ToMonthControl"]   = IntToStr(iMonth);
                        ini->Values["ToDayControl"]     = IntToStr(ToDay);
                        ini->Values["ToHourControl"]    = IntToStr(ToHour);
                        ini->Values["ToMinuteControl"]  = IntToStr(ToMinute);
                        //-----------------------------------------------------
                        SQLText= GetSQLText();
                        /*
                        Reguest += "IsReportTypeControl= ";
                        Reguest += IntToStr(IsReportTypeControl);
                        Reguest += "<BR>";
                        */
                        Reguest += OpenDatabase(GetWorkDatabaseName(DatabaseFileName), SQLText );
                        //Reguest += (GetWorkDatabaseName(DatabaseFileName) + " [" + GetDaysInMonth(iMonth) + "]" + ", ");
                        //-----------------------------------------------------
                        // Востанавливаем
                        ini->Values["FromYearControl"]  = RangeDateTime[0];
                        ini->Values["FromMonthControl"] = RangeDateTime[1];
                        ini->Values["FromDayControl"]   = RangeDateTime[2];
                        ini->Values["FromHourControl"]  = RangeDateTime[3];
                        ini->Values["FromMinuteControl"]= RangeDateTime[4];
                        ini->Values["ToYearControl"]    = RangeDateTime[5];
                        ini->Values["ToMonthControl"]   = RangeDateTime[6];
                        ini->Values["ToDayControl"]     = RangeDateTime[7];
                        ini->Values["ToHourControl"]    = RangeDateTime[8];
                        ini->Values["ToMinuteControl"]  = RangeDateTime[9];
                        //-----------------------------------------------------
                }
        }
  } // for (;iYear;)
  //----------------------------------------------------------------------
  return Reguest;
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::SQLDiagramPageProducerHTMLTag(
      TObject *Sender, TTag Tag, const AnsiString TagString,
      TStrings *TagParams, AnsiString &ReplaceText)
{
  if (TagString==AnsiString("FROM_YEAR"))   {ReplaceText= ini->Values["FromYearControl"];}
  if (TagString==AnsiString("FROM_MONTH"))  {ReplaceText= ini->Values["FromMonthControl"];}
  if (TagString==AnsiString("FROM_DAY"))    {ReplaceText= ini->Values["FromDayControl"];}
  if (TagString==AnsiString("FROM_HOUR"))   {ReplaceText= ini->Values["FromHourControl"];}
  if (TagString==AnsiString("FROM_MINUTE")) {ReplaceText= ini->Values["FromMinuteControl"];}
  //-------------------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))   {ReplaceText= ini->Values["FromYearControl"];}
  if (TagString==AnsiString("TO_MONTH"))  {ReplaceText= ini->Values["FromMonthControl"];}
  if (TagString==AnsiString("TO_DAY"))    {ReplaceText= ini->Values["ToDayControl"];}
  if (TagString==AnsiString("TO_HOUR"))   {ReplaceText= ini->Values["ToHourControl"];}
  if (TagString==AnsiString("TO_MINUTE")) {ReplaceText= ini->Values["ToMinuteControl"];}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::Diagram_step1PageProducerHTMLTag(
      TObject *Sender, TTag Tag, const AnsiString TagString,
      TStrings *TagParams, AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];
  /*
  ini->Values["FROM_YEAR"]=   GetFromYearHTMLControl();
  ini->Values["FROM_MONTH"]=  GetFromMonthHTMLControl();
  ini->Values["FROM_DAY"]=    GetFromDayHTMLControl();
  ini->Values["FROM_HOUR"]=   GetFromHourHTMLControl();
  ini->Values["FROM_MINUTE"]= GetFromMinuteHTMLControl();
  ini->Values["TO_YEAR"]=     GetToYearHTMLControl();
  ini->Values["TO_MONTH"]=    GetToMonthHTMLControl();
  ini->Values["TO_DAY"]=      GetToDayHTMLControl();
  ini->Values["TO_HOUR"]=     GetToHourHTMLControl();
  ini->Values["TO_MINUTE"]=   GetToMinuteHTMLControl();
  */
  if (TagString==AnsiString("t10"))  {ReplaceText= AnsiString("RRRRRRRRR");}
  //------------------------------------------------------------
  if (TagString==AnsiString("FROM_YEAR"))  {ReplaceText= GetFromYearHTMLControl();}
  if (TagString==AnsiString("FROM_MONTH")) {ReplaceText= GetFromMonthHTMLControl();}
  if (TagString==AnsiString("FROM_DAY"))   {ReplaceText= GetFromDayHTMLControl();}
  if (TagString==AnsiString("FROM_HOUR"))  {ReplaceText= GetFromHourHTMLControl();}
  if (TagString==AnsiString("FROM_MINUTE")){ReplaceText= GetFromMinuteHTMLControl();}
  //------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))  {ReplaceText= GetToYearHTMLControl();}
  if (TagString==AnsiString("TO_MONTH")) {ReplaceText= GetToMonthHTMLControl();}
  if (TagString==AnsiString("TO_DAY"))   {ReplaceText= GetToDayHTMLControl();}
  if (TagString==AnsiString("TO_HOUR"))  {ReplaceText= GetToHourHTMLControl();}
  if (TagString==AnsiString("TO_MINUTE")){ReplaceText= GetToMinuteHTMLControl();}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::Diagram_step2PageProducerHTMLTag(
      TObject *Sender, TTag Tag, const AnsiString TagString,
      TStrings *TagParams, AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];


  if (TagString==AnsiString("SQLFILENAME"))   {ReplaceText= ini->Values["SQLFILENAME"];}
  if (TagString==AnsiString("SELECT_TABLES")) {ReplaceText= GetSelectTablesHTMLControl();}
  //------------------------------------------------------------
  if (TagString==AnsiString("FROM_YEAR"))  {ReplaceText= GetFromYearHTMLControl();}
  if (TagString==AnsiString("FROM_MONTH")) {ReplaceText= GetFromMonthHTMLControl();}
  if (TagString==AnsiString("FROM_DAY"))   {ReplaceText= GetFromDayHTMLControl();}
  if (TagString==AnsiString("FROM_HOUR"))  {ReplaceText= GetFromHourHTMLControl();}
  if (TagString==AnsiString("FROM_MINUTE")){ReplaceText= GetFromMinuteHTMLControl();}
  //------------------------------------------------------------
  if (TagString==AnsiString("TO_YEAR"))  {ReplaceText= GetToYearHTMLControl();}
  if (TagString==AnsiString("TO_MONTH")) {ReplaceText= GetToMonthHTMLControl();}
  if (TagString==AnsiString("TO_DAY"))   {ReplaceText= GetToDayHTMLControl();}
  if (TagString==AnsiString("TO_HOUR"))  {ReplaceText= GetToHourHTMLControl();}
  if (TagString==AnsiString("TO_MINUTE")){ReplaceText= GetToMinuteHTMLControl();}
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::Diagram_step3PageProducerHTMLTag(TObject *Sender, TTag Tag,
      const AnsiString TagString, TStrings *TagParams, AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() > 0)
        ReplaceText= ini->Values[TagString];
}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::SQLFilePageProducerHTMLTag(TObject *Sender,
      TTag Tag, const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() > 0)
        ReplaceText= ini->Values[TagString];

}
//---------------------------------------------------------------------------
void __fastcall TCInfoModule::HeadReportProducerHTMLTag(TObject *Sender,
      TTag Tag, const AnsiString TagString, TStrings *TagParams,
      AnsiString &ReplaceText)
{
  if (ini->Values[TagString].Length() != 0)
        ReplaceText= ini->Values[TagString];

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
AnsiString __fastcall TCInfoModule::GenerateDiagramsName()
{
  AnsiString FileName;
  SYSTEMTIME lt;
  char deliver= '+';

  GetLocalTime(&lt);
  FileName.sprintf(
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

  return FileName;
}
//---------------------------------------------------------------------------

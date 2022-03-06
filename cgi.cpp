//---------------------------------------------------------------------------
// Borland C++Builder
// Copyright (c) 2001, Дипломная работа Герасименко Дмитрия Александровича
// Шифр: 54-0401
// gerasimenko@karelia.ru
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <condefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SysUtils.hpp>
#include <WebBroker.hpp>
#include <CGIApp.hpp>
#pragma hdrstop
USEFORM("main.cpp", CInfoModule);
USE("readme.txt", File);
USEUNIT("diagram.cpp");
//---------------------------------------------------------------------------
#define Application Webbroker::Application
#pragma link "cgiapp.obj"
#pragma link "webbroker.obj"
//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TCInfoModule), &CInfoModule);
                 Application->Run();
	}
	catch (Exception &exception)
	{
		Sysutils::ShowException(&exception, Sysutils::ExceptAddr());
	}
	return 0;
}
//---------------------------------------------------------------------------

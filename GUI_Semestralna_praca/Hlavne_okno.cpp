#include "Hlavne_okno.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThread]

void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	GUISemestralnapraca::Hlavne_okno form;
	Application::Run(% form);
}


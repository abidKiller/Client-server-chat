#include "myUI.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace UI;

int main()
{
	myUI^ x = gcnew myUI();
	x->ShowDialog();
	
}

/*[STAThread]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew UI::myUI);
	
	
}*/
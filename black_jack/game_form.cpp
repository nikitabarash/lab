#include "game_form.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);

    blackjack::game_form mainForm;
    Application::Run(% mainForm);

    return 0;
}
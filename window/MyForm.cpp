#include "MyForm.h"
#using <system.drawing.dll>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	window::MyForm form;
	Application::Run(% form);
}
window::MyForm::MyForm(void)
{
	InitializeComponent();

	game->NewGame(this, game);
	timer->Start();
}

System::Void window::MyForm::bulletTimer_Tick(System::Object^ sender, System::EventArgs^ e)
{
	game->timer(this, game);
	game->UpdateScoreLabel(scoreLabel);
	if (game->GetPlayerLifeModels()->Count == 0 && !isGameOver) {
		isGameOver = true;
		timer->Stop();
		restartButton->Text = "Начать заново";
		restartButton->Location = Point(225, 270);
		restartButton->Font = gcnew System::Drawing::Font("MS Gothic", 14, FontStyle::Bold);
		restartButton->ForeColor = System::Drawing::Color::Red;
		restartButton->Size = System::Drawing::Size(150, 50);
		restartButton->Click += gcnew System::EventHandler(this, &MyForm::RestartButton_Click);
		this->Controls->Add(restartButton);
	}
}

void window::MyForm::RestartButton_Click(System::Object^ sender, System::EventArgs^ e) {
	isGameOver = false;
	game->RestartGame(this, game, restartButton);
	timer->Start();
}
System::Void window::MyForm::Keyboard(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	game->Keys(e);
}
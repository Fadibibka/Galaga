#include "pch.h"
#include "Game.h"

void ClassLibrary1::Game::NewGame(Form^ form, Game^ game)
{
	respawnTimer = 0;
	player = gcnew Player(Point(290, 520), 25, 25, 10, form);
	player->PlayerLifeModels(playerlifemodels);
	SpawnEnemies(form);
	sky = gcnew SkyFullOfStars(150, 5, form);
	score = 0;
}
void ClassLibrary1::Game::SpawnEnemies(Form^ form)
{
	int initialXwasp = 1200;
	int initialYwasp = 1100;
	for (int i = 0; i < 5; i++)
	{
		Point location(initialXwasp + i * 50, initialYwasp + i * 50);
		wasp = gcnew Wasp(location, 25, 25, 7, form);
		wasp->centerX -= i * 30;
		enemies->Add(wasp);
	}
	int initialXlobs = -300;
	int initialYlobs = 800;
	for (int i = 0; i < 5; i++)
	{
		Point location(initialXlobs - i * 50, initialYlobs + i * 50);
		lobster = gcnew Lobster(location, 25, 25, 7, form);
		lobster->centerX -= i * 30;
		enemies->Add(lobster);
	}
	int initialXfly = 290;
	int initialYfly = -200;
	for (int i = 0; i < 5; i++)
	{
		Point location(initialXfly, initialYfly - i * 100);
		fly = gcnew Fly(location, 25, 25, 7, form);
		fly->centerX -= i * 30;
		enemies->Add(fly);
	}
}
void ClassLibrary1::Game::timer(Form^ form, Game^ game)
{
	player->updateBullets();
	game->InitializeWaspLogic(form);
	game->InitializeLobsterLogic(form);
	game->InitializeFlyLogic(form);
	sky->Update();
	if (respawnTimer >= 8000)
    {
		SpawnEnemies(form);
        respawnTimer = 0;
    }
	respawnTimer += 10;
}

void ClassLibrary1::Game::InitializeWaspLogic(Form^ form)
{
	for (int i = 0; i < enemies->Count; i++)
	{
		Enemy^ enemy = enemies[i];
		if (Wasp^ wasp = dynamic_cast<Wasp^>(enemy))
		{
			wasp->moveSequence();
			wasp->updateEnemybullets();
			wasp->bulletdamaging(player, playerlifemodels);
			if (wasp->die(player, form))
			{
				enemies->RemoveAt(i);
				Explosion^ explosion = gcnew Explosion(Point(wasp->GetWaspPictureBox()->Location.X - 20, wasp->GetWaspPictureBox()->Location.Y - 20), 60, 60);
				form->Controls->Add(explosion->GetExplosionPictureBox());
				form->Controls->Remove(wasp->GetWaspPictureBox());
				score += 50;
				wasp->clearBulletdie();
				// Запуск анимации взрыва
				while (!explosion->Animate()) {
					Application::DoEvents(); // Обновление формы для отображения анимации
					System::Threading::Thread::Sleep(1); // Задержка между кадрами анимации
				}
				form->Controls->Remove(explosion->GetExplosionPictureBox());
			}
		}
	}
}

void ClassLibrary1::Game::InitializeLobsterLogic(Form^ form)
{
	for (int i = 0; i < enemies->Count; i++)
	{
		Enemy^ enemy = enemies[i];
		if (Lobster^ lobster = dynamic_cast<Lobster^>(enemy))
		{
			lobster->moveSequence();
			lobster->updateEnemybullets();
			lobster->bulletdamaging(player, playerlifemodels);
			if (lobster->die(player, form))
			{
				enemies->RemoveAt(i);
				Explosion^ explosion = gcnew Explosion(Point(lobster->GetLobsterPictureBox()->Location.X - 20, lobster->GetLobsterPictureBox()->Location.Y - 20), 60, 60);
				form->Controls->Add(explosion->GetExplosionPictureBox());
				score += 50;
				lobster->clearBulletdie();
				// Запуск анимации взрыва
				while (!explosion->Animate()) {
					Application::DoEvents(); // Обновление формы для отображения анимации
					System::Threading::Thread::Sleep(1); // Задержка между кадрами анимации
				}
				form->Controls->Remove(explosion->GetExplosionPictureBox());
			}
		}
	}
}

void ClassLibrary1::Game::InitializeFlyLogic(Form^ form)
{
	for (int i = 0; i < enemies->Count; i++)
	{
		Enemy^ enemy = enemies[i];
		if (Fly^ fly = dynamic_cast<Fly^>(enemy))
		{
			fly->moveSequence();
			fly->bulletdamaging(player, playerlifemodels);
			if (fly->die(player, form))
			{
				enemies->RemoveAt(i);
				Explosion^ explosion = gcnew Explosion(Point(fly->GetFlyPictureBox()->Location.X - 20, fly->GetFlyPictureBox()->Location.Y - 20), 60, 60);
				form->Controls->Add(explosion->GetExplosionPictureBox());
				score += 50;
				// Запуск анимации взрыва
				while (!explosion->Animate()) {
					Application::DoEvents(); // Обновление формы для отображения анимации
					System::Threading::Thread::Sleep(1); // Задержка между кадрами анимации
				}
				form->Controls->Remove(explosion->GetExplosionPictureBox());
			}
		}
	}
}



void ClassLibrary1::Game::RestartGame(Form^ form, Game^ game, Button^ restartButton)
{
	score = 0;
	isGameOver = false;
	for (int i = form->Controls->Count - 1; i >= 0; i--)
	{
		Control^ control = form->Controls[i];
		if (PictureBox::typeid == control->GetType())
		{
			form->Controls->Remove(control);
			delete control;
		}
	}
	playerlifemodels->Clear();
	enemies->Clear();
	form->Controls->Remove(restartButton);
	game->NewGame(form, game);
}

void ClassLibrary1::Game::Keys(System::Windows::Forms::KeyEventArgs^ e)
{
	switch (e->KeyCode) {
	case Keys::Right:
		player->MoveRight();
		break;
	case Keys::Left:
		player->MoveLeft();
		break;
	case Keys::Up:
		player->shoot();

	}
	return System::Void();
}

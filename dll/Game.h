#pragma once
#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#using <system.drawing.dll>
#using <system.windows.forms.dll>
#include "Player.h"
#include "Wasp.h"
#include <Random>
#include "SkyFullOfStars.h"
#include "Lobster.h"
#include "Fly.h"
#include "Explosion.h"
#include "Enemy.h"
#include "Bullet.h"



using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace ClassLibrary1 {
    public ref class Game
    {
    private:
		int score;
		bool isGameOver;
		Player^ player;
		SkyFullOfStars^ sky;
		Wasp^ wasp;
		Lobster^ lobster;
		Fly^ fly;
		List<Player^>^ playerlifemodels = gcnew List<Player^>(5);
		List<Enemy^>^ enemies = gcnew List<Enemy^>();
		int respawnTimer = 0;
    public:
		void NewGame(Form^ form, Game^ game);
		void timer(Form^ form, Game^ game);
		void InitializeWaspLogic(Form^ form);
		void InitializeLobsterLogic(Form^ form);
		void InitializeFlyLogic(Form^ form);
		void SpawnEnemies(Form^ form);
		void UpdateScoreLabel(Label^ scoreLabel) {
			scoreLabel->Text = "Score: " + score.ToString();
		}
		bool getGameOver() {
			return isGameOver;
		}
		List<Player^>^ GetPlayerLifeModels() {
			return playerlifemodels;
		}
		void RestartGame(Form^ form, Game^ game, Button^ restartButton);
		void Keys(System::Windows::Forms::KeyEventArgs^ e);
    };
}

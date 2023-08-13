#pragma once

#include <Windows.h>
#include <iostream>
#include <vector>
#using <system.drawing.dll>
#using <system.windows.forms.dll>
#include "Bullet.h"



using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace ClassLibrary1 {
    public ref class Player
    {
    private:
        PictureBox^ playerPictureBox;
        int speed;
        Form^ form;
        bool canShoot = true;
        System::Windows::Forms::Timer^ shootTimer;
    public:
        List<Bullet^> bullets;
        Player() {};
        Player(Point location, int width, int height, int initialSpeed, Form^ form);
        void OnShootTimerTick(System::Object^ sender, System::EventArgs^ e);
        PictureBox^ GetPlayerPictureBox(); 
        int GetPlayerCoordX();
        int GetPlayerCoordY();
        void MoveLeft();
        void MoveRight();
        void shoot();
        void PlayerLifeModels(List<Player^>^ playerlifemodels);
        void UpdatePlayerLifeModels(List<Player^>^ playerlifemodels);
        void updateBullets();
    };
}

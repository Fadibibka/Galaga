#pragma once
#pragma once
#pragma once

#include <Windows.h>
#include <iostream>
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace ClassLibrary1 {
    public ref class Fly :public Enemy
    {
    private:
        int direction = 0;
        bool Fly::isCircularMotion = false;
        int Fly::circles = 0;
        PictureBox^ Flypicturebox;
        int speed;
        List<Fly^>^ Flys = gcnew List<Fly^>();
        int horizontalDirection;
        int numLobsters = 5;
        bool moveLeft = true;
        int CountGoriz = 0;

    public:
        int radius = 135;
        int centerX = 290;
        Fly(Point location, int width, int height, int InitialSpeed, Form^ form);


        PictureBox^ GetFlyPictureBox()
        {
            return Flypicturebox;
        }

        int GetEnemycoordX() override;
        int GetEnemycoordY() override;
        void moveSequence() override;
        bool bodydamaging(Player^ obj) override;
        bool die(Player^ obj, Form^ form) override;
    };
}
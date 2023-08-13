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
    public ref class Lobster :public Enemy
    {
    private:
        bool Lobster::isCircularMotion = false;
        int Lobster::circles = 0;
        PictureBox^ Lobsterpicturebox;
        int speed;
        List<Lobster^>^ Lobsters = gcnew List<Lobster^>();

        int numLobsters = 5;
        int Circles = 0;
        int CountGoriz = 0;

    public:
        int radius = 135;
        int centerX = 290;
        Lobster(Point location, int width, int height, int InitialSpeed, Form^ form);


        PictureBox^ GetLobsterPictureBox()
        {
            return Lobsterpicturebox;
        }

        int GetEnemycoordX() override;
        int GetEnemycoordY() override;
        void moveSequence() override;
        bool bodydamaging(Player^ obj) override;
        bool die(Player^ obj, Form^ form) override;
    };
}
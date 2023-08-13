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
    public ref class Wasp:public Enemy
    {
    private:
        bool Wasp::isCircularMotion = false;
        int Wasp::circles = 0;
        PictureBox^ wasppicturebox;
        int speed;
        List<Wasp^>^ wasps = gcnew List<Wasp^>();

        int numWasps = 5;
        int Circles = 0;
        int CountGoriz = 0;
        
    public:
        int radius = 135;
        int centerX = 290;
        Wasp(Point location, int width, int height, int InitialSpeed, Form^ form);

        
        PictureBox^ GetWaspPictureBox()
        {
            return wasppicturebox;
        }
        
        int GetEnemycoordX() override;
        int GetEnemycoordY() override;
        void moveSequence() override;
        bool bodydamaging(Player^ obj) override;
        bool die(Player^ obj, Form^ form) override;
        
    };
}

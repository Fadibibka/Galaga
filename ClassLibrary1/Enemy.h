#pragma once
#include <Windows.h>
#include <iostream>
#using <system.drawing.dll>
#using <system.windows.forms.dll>
#include "Bullet.h"
#include "Explosion.h"
#include "Player.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace ClassLibrary1 {
    public ref class Enemy abstract
    {
    private:

    public:
        bool IsDestroyed = false;
        int shootingDelay;
        List<Bullet^> enemybullets;
        Form^ form;
        Enemy() {};
        void attack();
        void bulletdamaging(Player^ obj, List<Player^>^ playerlifemodels);
        void atdelay();
        void clearBulletdie();
        void updateEnemybullets();
        virtual int GetEnemycoordX() = 0;
        virtual int GetEnemycoordY() = 0;
        virtual void moveSequence() = 0;
        virtual bool bodydamaging(Player^ obj) = 0;
        virtual bool die(Player^ obj, Form^ form) = 0;
    };
}

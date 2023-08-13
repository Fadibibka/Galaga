#pragma once

#include <Windows.h>
#include <iostream>
#using <system.drawing.dll>
#using <system.windows.forms.dll>


using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace ClassLibrary1 {
    public ref class Bullet
    {
    private:
        PictureBox^ bulletpicturebox;
        int speed;
        Image^ sprite;

    public:
        Bullet(Point location, int width, int height, int Initialspeed, bool enemy);
        void moveenemybullet();
        PictureBox^ GetBulletPictureBox()
        {
            return bulletpicturebox;
        }
        void movebullet();
        bool IsOutOfBounds();
    };
}

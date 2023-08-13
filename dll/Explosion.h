#pragma once
#include <Windows.h>
#include <iostream>
#using <system.drawing.dll>
#using <system.windows.forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace ClassLibrary1 {
    public ref class Explosion
    {
    private:
        PictureBox^ explosionPictureBox;
        int currentFrame;
        array<Image^>^ frames;
        int frameDelay;
        int frameCount;
    public:
        Explosion(Point location, int width, int height);
        PictureBox^ GetExplosionPictureBox()
        {
            return explosionPictureBox;
        }
        bool Animate();
        
    };
}
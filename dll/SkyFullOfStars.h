#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#using <system.drawing.dll>
#using <system.windows.forms.dll>

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

namespace ClassLibrary1 {
    public ref class SkyFullOfStars
    {
    private:
        List<PictureBox^> stars;
        int speed;
        Form^ form;
        Random^ random;
        int spacing;
        int brightness;

        void PlaceStar(PictureBox^ star)
        {
            // Генерация рандомного местоположения для звезды с учетом расстояния между ними
            int minX = 0;
            int maxX = form->Width - star->Width;
            int minY = -form->Height;
            int maxY = 0;
            int x = random->Next(minX, maxX);
            int y = random->Next(minY, maxY);
            star->Location = Point(x, y);
            // Рандомное затемнение для некоторых звезд
            brightness = random->Next(50, 256);
            star->BackColor = Color::FromArgb(brightness, brightness, brightness);
            star->Tag = brightness;
        }

    public:
        SkyFullOfStars(int numStars, int spacing, Form^ form);
        void Update();
    };
}

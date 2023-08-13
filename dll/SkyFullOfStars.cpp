#include "pch.h"
#include "SkyFullOfStars.h"


ClassLibrary1::SkyFullOfStars::SkyFullOfStars(int numStars, int spacing, Form^ form)
{
    this->spacing = spacing;
    this->form = form;
    random = gcnew Random();
    for (int i = 0; i < numStars; i++)
    {
        PictureBox^ star = gcnew PictureBox();
        star->Size = Size(1, 2);
        PlaceStar(star);
        form->Controls->Add(star);
        stars.Add(star);

    }
}

void ClassLibrary1::SkyFullOfStars::Update()
{
    for (int i = 0; i < stars.Count; i++)
    {
        PictureBox^ star = stars[i];
        int brightness = (int)star->Tag;
        int starSpeed = spacing;
        if (brightness < 180)
        {
            starSpeed = 4;
        }
        if (brightness < 100)
        {
            starSpeed = 3;
        }
        star->Top += starSpeed;
        if (star->Top >= form->Height)
        {
            star->Top = -star->Height;
            PlaceStar(star);
        }
    }
}

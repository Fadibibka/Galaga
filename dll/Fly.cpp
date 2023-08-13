#include "pch.h"
#include "Fly.h"
#include <cmath>


using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

bool moveright = true;
namespace ClassLibrary1 {
    Fly::Fly(Point location, int width, int height, int InitialSpeed, Form^ form) {
        Image^ sprite = Image::FromFile("Sprites//FlySprites.png");
        Flypicturebox = gcnew PictureBox();
        Flypicturebox->Image = sprite;
        Flypicturebox->SizeMode = PictureBoxSizeMode::Zoom;
        Flypicturebox->Location = location;
        Flypicturebox->Width = width;
        Flypicturebox->Height = height;
        /*Graphics^ g = pictureBox->CreateGraphics();
        g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
        g->DrawImage(sprite, pictureBox->ClientRectangle);*/
        speed = InitialSpeed;
        this->form = form;
        form->Controls->Add(Flypicturebox);
        srand(time(0)); 
        shootingDelay = rand() % 9 + 2;
    }
    int Fly::GetEnemycoordX()
    {
        return Flypicturebox->Location.X;
    }

    int Fly::GetEnemycoordY()
    {
        return Flypicturebox->Location.Y;
    }

    void Fly::moveSequence() {
        if (direction == 0)
        {
            // Движение сверху вниз
            Flypicturebox->Top += speed - 2;

            if (Flypicturebox->Top >= 50)
            {
                // Переход к горизонтальному движению
                direction = 1;
            }
        }
        else if (direction == 1)
        {
            if (Flypicturebox->Left > 0 && moveLeft)
            {
                Flypicturebox->Top += speed-6;
                Flypicturebox->Left -= speed-1;
            }
            else if (Flypicturebox->Top <= 180) {
                moveLeft = false;
                Flypicturebox->Top += speed - 2;
            }
            else if (CountGoriz<300) {
                speed = 2;
                for (int i = Flys->Count - 1; i >= 0; i--) {
                    Fly^ otherFly = Flys[i];
                    if (otherFly != this) {
                        if (Flypicturebox->Bounds.IntersectsWith(otherFly->GetFlyPictureBox()->Bounds)) {
                            if (moveright) {
                                Flypicturebox->Left = otherFly->GetFlyPictureBox()->Right + 1;
                            }
                            else {
                                Flypicturebox->Left = otherFly->GetFlyPictureBox()->Left - Flypicturebox->Width - 1;
                            }
                            break;
                        }
                    }
                }
                if (moveright) {
                    if (Flypicturebox->Left > 50) {
                        Flypicturebox->Left -= speed;
                    }
                    else {
                        moveright = false;
                    }
                }
                else {
                    Flypicturebox->Left += speed;
                    if (Flypicturebox->Left > 270) {
                        moveright = true;
                    }
                }
                CountGoriz++;
            }
            else {
                Flypicturebox->Top += speed + 2;
            }
        }
    }
    bool Fly::bodydamaging(Player^ obj)
    {
        if (!IsDestroyed && Flypicturebox->Bounds.IntersectsWith(obj->GetPlayerPictureBox()->Bounds))
        {
            form->Controls->Remove(Flypicturebox);
            IsDestroyed = true;
            return true;
        } else return false;
    }
    bool Fly::die(Player^ obj, Form^ form)
    {
        for (int i = 0; i < obj->bullets.Count; i++)
        {
            Bullet^ bullet = obj->bullets[i];
            if (bullet->GetBulletPictureBox()->Bounds.IntersectsWith(Flypicturebox->Bounds))
            {
                form->Controls->Remove(bullet->GetBulletPictureBox());
                obj->bullets.RemoveAt(i);
                form->Controls->Remove(Flypicturebox);
                return true;
            }
        }
        return false;
    }
}


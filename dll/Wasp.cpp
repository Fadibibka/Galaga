#include "pch.h"
#include "Wasp.h"
#include <cmath>


using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

bool moveleeft = true;
namespace ClassLibrary1 {
    Wasp::Wasp(Point location, int width, int height, int InitialSpeed, Form^ form) {
        Image^ sprite = Image::FromFile("Sprites//WaspSprites.png");
        wasppicturebox = gcnew PictureBox();
        wasppicturebox->Image = sprite;
        wasppicturebox->SizeMode = PictureBoxSizeMode::Zoom;
        wasppicturebox->Location = location;
        wasppicturebox->Width = width;
        wasppicturebox->Height = height;
        /*Graphics^ g = pictureBox->CreateGraphics();
        g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
        g->DrawImage(sprite, pictureBox->ClientRectangle);*/
        speed = InitialSpeed;
        this->form = form;
        form->Controls->Add(wasppicturebox);
        srand(time(0));  // Инициализация генератора случайных чисел
        shootingDelay = rand() % 9 + 2;
    }
    int Wasp::GetEnemycoordX()
    {
        return wasppicturebox->Location.X;
    }

    int Wasp::GetEnemycoordY()
    {
        return wasppicturebox->Location.Y;
    }

    void Wasp::moveSequence() {

        if ((wasppicturebox->Location.Y > 370) && !isCircularMotion) {
            wasppicturebox->Left -= speed;
            wasppicturebox->Top -= speed;
        }
        else if (circles < 50) {
            isCircularMotion = true;
            // Выполните движение по окружности
            int centerX = 420;  // Центральная точка по оси X врага
            int centerY = 370; // Центральная точка по оси Y врага
            int radius = 50;  // Радиус окружности

            // Вычисление новых координат на окружности
            int newX = centerX + static_cast<int>(radius * cos(speed * 3.14 / 180));
            int newY = centerY + static_cast<int>(radius * sin(speed * 3.14 / 180));

            // Установка новых координат
            wasppicturebox->Left = newX;
            wasppicturebox->Top = newY;

            // Увеличение угла движения
            speed += 10;  // Увеличьте или уменьшите значение, чтобы изменить скорость вращения
            circles++;
        }
        else {
            if (wasppicturebox->Top > 110 && wasppicturebox->Left < 440 && CountGoriz<370) {
                speed = 7;
                wasppicturebox->Top -= speed;
                wasppicturebox->Left += speed - 6;
            }
            else if(CountGoriz<490) {
                atdelay();
                speed = 5;
                for (int i = wasps->Count - 1; i >= 0; i--) {
                    Wasp^ otherWasp = wasps[i];
                    if (otherWasp != this) {
                        if (wasppicturebox->Bounds.IntersectsWith(otherWasp->GetWaspPictureBox()->Bounds)) {
                            if (moveleeft) {
                                wasppicturebox->Left = otherWasp->GetWaspPictureBox()->Right + 1;
                            }
                            else {
                                wasppicturebox->Left = otherWasp->GetWaspPictureBox()->Left - wasppicturebox->Width - 1;
                            }
                            break;
                        }
                    }
                }
                if (moveleeft) {
                    if (wasppicturebox->Left > 50) {
                        wasppicturebox->Left -= speed;
                    }
                    else {
                        moveleeft = false;
                    }
                }
                else {
                    wasppicturebox->Left += speed;
                    if (wasppicturebox->Left > 500) {
                        moveleeft = true;
                    }
                }
                CountGoriz++;
            }
            else  {
                wasppicturebox->Top += speed-2;
            }
        }
    }
    bool Wasp::bodydamaging(Player^ obj)
    {
        if (!IsDestroyed && wasppicturebox->Bounds.IntersectsWith(obj->GetPlayerPictureBox()->Bounds))
        {
            form->Controls->Remove(wasppicturebox);
            IsDestroyed = true;
            return true;
        }
        return false;
    }
    bool Wasp::die(Player^ obj, Form^ form)
    {
            for (int i = 0; i < obj->bullets.Count; i++)
            {
                Bullet^ bullet = obj->bullets[i];
                if (bullet->GetBulletPictureBox()->Bounds.IntersectsWith(wasppicturebox->Bounds))
                {
                    form->Controls->Remove(bullet->GetBulletPictureBox());
                    obj->bullets.RemoveAt(i);
                    form->Controls->Remove(wasppicturebox);
                    return true;
                }
            }
            return false;
    }
}

#include "pch.h"
#include "Lobster.h"
#include <cmath>


using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace System::Collections::Generic;

bool moveleft = true;
namespace ClassLibrary1 {
    Lobster::Lobster(Point location, int width, int height, int InitialSpeed, Form^ form) {
        Image^ sprite = Image::FromFile("Sprites//LobsterSprites.png");
        Lobsterpicturebox = gcnew PictureBox();
        Lobsterpicturebox->Image = sprite;
        Lobsterpicturebox->SizeMode = PictureBoxSizeMode::Zoom;
        Lobsterpicturebox->Location = location;
        Lobsterpicturebox->Width = width;
        Lobsterpicturebox->Height = height;
        /*Graphics^ g = pictureBox->CreateGraphics();
        g->InterpolationMode = System::Drawing::Drawing2D::InterpolationMode::HighQualityBicubic;
        g->DrawImage(sprite, pictureBox->ClientRectangle);*/
        speed = InitialSpeed;
        this->form = form;
        form->Controls->Add(Lobsterpicturebox);
        srand(time(0));  // Инициализация генератора случайных чисел
        shootingDelay = rand() % 9 + 2;
    }
    int Lobster::GetEnemycoordX()
    {
        return Lobsterpicturebox->Location.X;
    }

    int Lobster::GetEnemycoordY()
    {
        return Lobsterpicturebox->Location.Y;
    }

    void Lobster::moveSequence() {
        if ((Lobsterpicturebox->Location.Y > 370) && !isCircularMotion) {
            Lobsterpicturebox->Left += speed;
            Lobsterpicturebox->Top -= speed;
        }
        else if (circles < 80) {
            isCircularMotion = true;
            // Выполните движение по окружности
            int centerX = 185;  // Центральная точка по оси X врага
            int centerY = 370; // Центральная точка по оси Y врага
            int radius = 50;  // Радиус окружности

            // Вычисление новых координат на окружности
            int newX = centerX + static_cast<int>(radius * -cos(speed * 3.14 / 180));
            int newY = centerY + static_cast<int>(radius * -sin(speed * 3.14 / 180));

            // Установка новых координат
            Lobsterpicturebox->Left = newX;
            Lobsterpicturebox->Top = newY;

            // Увеличение угла движения
            speed += 10;  // Увеличьте или уменьшите значение, чтобы изменить скорость вращения
            circles++;
        }
        else {
            if (Lobsterpicturebox->Top > 140 && Lobsterpicturebox->Left < 440 && CountGoriz < 370) {
                speed = 7;
                Lobsterpicturebox->Top -= speed;
                Lobsterpicturebox->Left += speed - 6;
            }
            else if (CountGoriz < 470) {
                atdelay();
                speed = 5;
                for (int i = Lobsters->Count - 1; i >= 0; i--) {
                    Lobster^ otherLobster = Lobsters[i];
                    if (otherLobster != this) {
                        if (Lobsterpicturebox->Bounds.IntersectsWith(otherLobster->GetLobsterPictureBox()->Bounds)) {
                            if (moveleft) {
                                Lobsterpicturebox->Left = otherLobster->GetLobsterPictureBox()->Right + 1;
                            }
                            else {
                                Lobsterpicturebox->Left = otherLobster->GetLobsterPictureBox()->Left - Lobsterpicturebox->Width - 1;
                            }
                            break;
                        }
                    }
                }
                if (moveleft) {
                    if (Lobsterpicturebox->Left > 50) {
                        Lobsterpicturebox->Left -= speed;
                    }
                    else {
                        moveleft = false;
                    }
                }
                else {
                    Lobsterpicturebox->Left += speed;
                    if (Lobsterpicturebox->Left > 500) {
                        moveleft = true;
                    }
                }
                CountGoriz++;
            }
            else {
                Lobsterpicturebox->Top += speed - 1;
            }
        }
    }
    bool Lobster::bodydamaging(Player^ obj)
    {
        if (!IsDestroyed && Lobsterpicturebox->Bounds.IntersectsWith(obj->GetPlayerPictureBox()->Bounds))
        {
            form->Controls->Remove(Lobsterpicturebox);
            IsDestroyed = true;
            return true;
        } else return false;
    }
    bool Lobster::die(Player^ obj, Form^ form)
    {
        for (int i = 0; i < obj->bullets.Count; i++)
        {
            Bullet^ bullet = obj->bullets[i];
            if (bullet->GetBulletPictureBox()->Bounds.IntersectsWith(Lobsterpicturebox->Bounds))
            {

                form->Controls->Remove(bullet->GetBulletPictureBox());
                obj->bullets.RemoveAt(i);
                form->Controls->Remove(Lobsterpicturebox);
                return true;
            }
        }
        return false;
    }
}

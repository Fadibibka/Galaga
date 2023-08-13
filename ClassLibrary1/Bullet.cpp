#include "pch.h"
#include "Bullet.h"

namespace ClassLibrary1 {
		Bullet::Bullet(Point location, int width, int height, int Initialspeed, bool enemy)
        {
            if (!enemy) sprite = Image::FromFile("Sprites//PlayerShotSprite.png"); else sprite = Image::FromFile("Sprites//EnemyShotSprite.png");
            bulletpicturebox = gcnew PictureBox();
            bulletpicturebox->Image = sprite;
            bulletpicturebox->SizeMode = PictureBoxSizeMode::Zoom;
            bulletpicturebox->Location = location;
            bulletpicturebox->Width = width;
            bulletpicturebox->Height = height;
            speed = Initialspeed;
        }
        void Bullet::moveenemybullet()
        {
            bulletpicturebox->Top += speed;
        }

        void Bullet::movebullet()
        {
            bulletpicturebox->Top -= speed; // Направление вверх, можно изменить
        }
        bool Bullet::IsOutOfBounds()
        {
            return (bulletpicturebox->Location.Y < 0);
        }
}
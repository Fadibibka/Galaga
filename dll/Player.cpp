#include "pch.h"
#include "Player.h"
#include "Bullet.h"


namespace ClassLibrary1 {

    void Player::MoveLeft()
    {
        if (playerPictureBox->Left > 0) {
            playerPictureBox->Left -= speed;
        }
    }

    void Player::MoveRight()
    {
        if (playerPictureBox->Right < 580) {
            playerPictureBox->Left += speed;
        }
    }
    void Player::shoot()
    {
        if (canShoot)
        {
            Bullet^ bullet = gcnew Bullet(Point(GetPlayerCoordX() + 10, GetPlayerCoordY() - 20), 10, 10, 20, 0);
            form->Controls->Add(bullet->GetBulletPictureBox());
            bullets.Add(bullet);
            canShoot = false;
            shootTimer->Start();
        }
    }
    void Player::PlayerLifeModels(List<Player^>^ playerlifemodels)
    {
        int startX = 460;
        int startY = 580;
        for (int i = 0; i < 5; i++)
        {
            Player^ playerlifemodel = gcnew Player(Point(startX + i * 23, startY), 20, 20, 0, form);
            playerlifemodels->Add(playerlifemodel);
        }
    }
    void Player::UpdatePlayerLifeModels(List<Player^>^ playerlifemodels)
    {
        int i = 0;
        form->Controls->Remove(playerlifemodels[i]->GetPlayerPictureBox());
        playerlifemodels->RemoveAt(i);
        i++;
    }
    void Player::updateBullets()
    {
        for (int i = bullets.Count - 1; i >= 0; i--) {
            Bullet^ bullet = bullets[i];
            bullet->movebullet();
            if (bullet->IsOutOfBounds()) {
                bullets.RemoveAt(i);
                form->Controls->Remove(bullet->GetBulletPictureBox());
            }
        }
    }
    PictureBox^ Player::GetPlayerPictureBox()
    {
        return playerPictureBox;
    }
    int Player::GetPlayerCoordX()
    {
        return playerPictureBox->Location.X;
    }
    int Player::GetPlayerCoordY()
    {
        return playerPictureBox->Location.Y;
    }
    Player::Player(Point location, int width, int height, int initialSpeed, Form^ form) {
        Image^ sprite = Image::FromFile("Sprites//PlayerSprite.png");
        playerPictureBox = gcnew PictureBox();
        playerPictureBox->Image = sprite;
        playerPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        playerPictureBox->Location = location;
        playerPictureBox->Width = width;
        playerPictureBox->Height = height;
        speed = initialSpeed;
        this->form = form;
        form->Controls->Add(playerPictureBox);
        shootTimer = gcnew System::Windows::Forms::Timer();
        shootTimer->Interval = 600;
        shootTimer->Tick += gcnew System::EventHandler(this, &Player::OnShootTimerTick);
    }
    void Player::OnShootTimerTick(System::Object^ sender, System::EventArgs^ e)
    {
        canShoot = true;
    }
}
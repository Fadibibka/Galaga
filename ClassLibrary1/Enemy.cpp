#include "pch.h"
#include "Enemy.h"
#include "Bullet.h"


void ClassLibrary1::Enemy::attack()
{
    Bullet^ bullet = gcnew Bullet(Point(GetEnemycoordX() - 10, GetEnemycoordY() + 20), 8, 8, 7, 1);
    form->Controls->Add(bullet->GetBulletPictureBox());
    enemybullets.Add(bullet);
}

void ClassLibrary1::Enemy::bulletdamaging(Player^ obj, List<Player^>^ playerlifemodels)
{
    for (int i = enemybullets.Count - 1; i >= 0; i--) {
        Bullet^ bullet = enemybullets[i];
        if (bullet->GetBulletPictureBox()->Bounds.IntersectsWith(obj->GetPlayerPictureBox()->Bounds))
        {
            form->Controls->Remove(bullet->GetBulletPictureBox());
            enemybullets.Remove(bullet);
            obj->UpdatePlayerLifeModels(playerlifemodels);
        }
    }
    if (bodydamaging(obj)) {
        obj->UpdatePlayerLifeModels(playerlifemodels);
    }
}

void ClassLibrary1::Enemy::atdelay()
{
    shootingDelay--;
    if (shootingDelay <= 0) {
        attack();
        shootingDelay = rand() % 100 + 10;
    }
}

void ClassLibrary1::Enemy::updateEnemybullets()
{
    for (int i = enemybullets.Count - 1; i >= 0; i--) {
        Bullet^ bullet = enemybullets[i];
        bullet->moveenemybullet();
        if (bullet->IsOutOfBounds()) {
            enemybullets.RemoveAt(i);
            form->Controls->Remove(bullet->GetBulletPictureBox());
        }
    }
}

void ClassLibrary1::Enemy::clearBulletdie()
{
    for (int i = enemybullets.Count - 1; i >= 0; i--) {
        Bullet^ bullet = enemybullets[i];
        form->Controls->Remove(bullet->GetBulletPictureBox());
        enemybullets.Remove(bullet);
    }
}

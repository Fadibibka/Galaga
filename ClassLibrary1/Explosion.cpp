#include "pch.h"
#include "Explosion.h"

ClassLibrary1::Explosion::Explosion(Point location, int width, int height)
{
        array<String^>^ explosionSprites = gcnew array<String^>(5);
        explosionSprites[0] = "Sprites/explosion1.png";
        explosionSprites[1] = "Sprites/explosion2.png";
        explosionSprites[2] = "Sprites/explosion3.png";
        explosionSprites[3] = "Sprites/explosion4.png";
        explosionSprites[4] = "Sprites/explosion5.png";
        explosionPictureBox = gcnew PictureBox();
        explosionPictureBox->Location = location;
        explosionPictureBox->Width = width;
        explosionPictureBox->Height = height;
        explosionPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        frames = gcnew array<Image^>(explosionSprites->Length);
        for (int i = 0; i < explosionSprites->Length; i++) {
            frames[i] = Image::FromFile(explosionSprites[i]);
        }
        currentFrame = 0;
        frameDelay = 1;
        frameCount = 0;
}

bool ClassLibrary1::Explosion::Animate()
{
        frameCount++;
        if (frameCount >= frameDelay) {
            frameCount = 0;
            currentFrame++;
            if (currentFrame >= frames->Length) {
                return true;
            }
            explosionPictureBox->Image = frames[currentFrame];
        }
        return false;
}


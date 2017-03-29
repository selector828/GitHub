#include "Selector.h"

CAMERA Camera;

void Init(void) {
	Camera.fPosX = 0;
	Camera.fPosY = 0;
	Camera.fPosZ = 0;
	Camera.fRotZ = 0;
	Camera.fScaleX = 0;
	Camera.fScaleY = 0;
	Camera.uRed = 255;
	Camera.uGreen = 255;
	Camera.uBlue = 255;
	Camera.uAlpha = 255;
	SetMainCamera(&Camera);
}

void Update(void) {

}

void Debug(void) {

}
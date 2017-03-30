#include "Selector.h"

CAMERA Camera;

void Init(void) {
	Camera.fPosX = 0;
	Camera.fPosY = 0;
	Camera.fPosZ = 0;
	Camera.fRotZ = 0;
	Camera.fScaleX = 1.0;
	Camera.fScaleY = 1.0;
	Camera.uRed = 255;
	Camera.uGreen = 255;
	Camera.uBlue = 255;
	Camera.uAlpha = 255;
	SetMainCamera(&Camera);
	LoadPicture("animations/absorb.png");
}

void Update(void) {
	if (GetKeyUp('P') == 2) Pause();
	SetPicture("animations/absorb.png", 100, 100, 0, 80, 1.0f, 1.0f, 5, 5, 4, 255, 200, 100, 200, true);
}

void OnDebug(void) {

}

void OnPause(void) {
	DrawString("PAUSE", WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT / 2 - 10);
	if (GetKeyUp('P') == 2) Pause();
}

void OnApplicationQuit(void) {
	MessageBox(NULL, "Ç®ÇÌÇ¡ÇøÇ·Ç¡ÇΩÅB", "ÇØÇ¢Ç±Ç≠", MB_OK);
}
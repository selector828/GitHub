#include "Selector.h"

CAMERA Camera;

ANIMATION Anim = {
	"animations/Absorb.png", //pPicture
	5, //uWidth
	5, //uHeight
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, //uPattern
	{ 0, 0, 0 }, //fRelPosX
	{ 0, 0 }, //fRelPosY
	{ 2, 2, 2, 2, 2 }, //fRelPosZ
	{ 0, 0 }, //fRelRotZ
	{ 0, 0 }, //fRelScaleX
	{ 0, 0 }, //fRelScaleY
	{ 0, 0 }, //fRelRed
	{ 0, 0 }, //fRelGreen
	{ 0, 0 }, //fRelBlue
	{ 0, 0 }, //fRelAlpha
	{ 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f }, //fDuration
	1.0f, //fSpeed
	0, //fTime
	0, //uPic
	9 //uMax
};

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
	LoadPicture("animations/Absorb.png");
}

void Update(void) {
	
}

void OnDebug(void) {

}

void OnPause(void) {
	DrawString("PAUSE", WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT / 2 - 10);
	if (GetKeyUp('P') == 2) Pause();
}

void OnApplicationQuit(void) {
	//MessageBox(NULL, "Ç®ÇÌÇ¡ÇøÇ·Ç¡ÇΩÅB", "ÇØÇ¢Ç±Ç≠", MB_OK);
}

void OnClickButton(WPARAM wParam) {
	switch (wParam) {
	case 50:
		Anim.Set(0, 200, 200, 0, 1.0f, 1.0f, 255, 255, 255, 255, true, true);
		break;
	case 51:
		Anim.Set(0, 200, 200, 0, 1.0f, 1.0f, 255, 255, 255, 255, true, false);
		break;
	case 52:
		Anim.Delete(0);
		break;
	}
}
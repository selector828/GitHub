#include "Selector.h"

CAMERA Camera = {
#include"Camera.conf"
};
PICTURE Actor;
PICTURE Skill;
ANIMATION Anim = {
	"Pictures/Absorb.png", //pPicture
	5, //uWidth
	5, //uHeight
	{ 0, 1, 2, 3, 4 }, //uPattern
	{ 0, 0, 0 }, //fRelPosX
	{ 0, 0 }, //fRelPosY
	{ 1, 1, 1, 1, 1 }, //fRelPosZ
	{ 0, 0 }, //fRelRotZ
	{ 0, 0 }, //fRelScaleX
	{ 0, 0 }, //fRelScaleY
	{ 0, 0 }, //fRelRed
	{ 0, 0 }, //fRelGreen
	{ 0, 0 }, //fRelBlue
	{ 0, 0 }, //fRelAlpha
	{ 5.0f, 5.0f, 5.0f, 5.0f, 5.0f }, //fDuration
	1.0f, //fSpeed
	0, //fTime
	0, //uPic
	4 //uMax
};
void Init(void) {
	Actor.Load("Pictures/Actor.png");
	Skill.Load("Pictures/Absorb.png");
	Anim.pPicture = &Skill;
	SetMainCamera(&Camera);
}

void Update(void) {
	Actor.Set(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0, 0.4f, 0.4f, 5, 5, 0, 255, 255, 255, 255, true);
	Anim.Set(0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 0.5f, 0.5f, 255, 255, 255, 255, true, false);
}

void Debug(void) {

}
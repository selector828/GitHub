#include "Selector.h"

CAMERA Camera = {
#include "Camera.conf"
};
PPICTURE Actor;
ANIMATION Anim = {
#include "absorb.anim"
};

void Init(void) {
	
	LoadPicture("Pictures/Actor.png");
	LoadPicture("Pictures/Absorb.png");
	
	SetMainCamera(&Camera);
}

void Update(void) {
	SetPicture( "Pictures/Actor.png", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 1, 0, 1.0f, 1.0f, 9, 6, 0, 255, 255, 255, 255, true);
	Anim.Set(0, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 0, 2.0f, 2.0f, 255, 255, 255, 255, true, false);
}

void OnDebug(void) {

}
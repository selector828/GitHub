//[main.cpp 2017/03/18 - 2017/03/27 Flauzino Vinicius]______________________
#include "main.h"

CAMERA Camera;
PICTURE Picture;
ANIMATION Anim = {
	"Pictures/test3.png", //pPicture
	1, //uWidth
	1, //uHeight
	{ 0, 0, 0 }, //uPattern
	{ 100, 0, 0 }, //fRelPosX
	{ 0, 100 }, //fRelPosY
	{ 10, 9 }, //fRelPosZ
	{ 0, 0 }, //fRelRotZ
	{ 0, 0 }, //fRelScaleX
	{ 0, 0 }, //fRelScaleY
	{ 0, 0 }, //fRelRed
	{ 0, 0 }, //fRelGreen
	{ 0, 0 }, //fRelBlue
	{ 0, 0 }, //fRelAlpha
	{ 8.0f, 8.0f, 8.0f }, //fDuration
	1.0f, //fSpeed
	0, //fTime
	0, //uPic
	2 //uMax
};
float   fPosX = WINDOW_WIDTH / 2, fPosY = WINDOW_HEIGHT / 2, fScale = 1.0f; 
//[èâä˙âª 2017/03/18 - 2017/03/24]__________________________________________
void Init ( void ) {
	Camera.fPosX = 0;
	Camera.fPosY = 0;
	Camera.fPosZ = 0;
	Camera.fRotZ = 90;
	Camera.fScaleX = 1.0f;
	Camera.fScaleY = 1.0f;
	Camera.uRed = 255;
	Camera.uGreen = 255;
	Camera.uBlue = 255;
	Camera.uAlpha = 255;
	SetMainCamera( &Camera );
	Picture.Load("Pictures/test3.png");
	Anim.pPicture = &Picture;
}
//[çXêV 2017/03/18 - 2017/03/27]_____________________________________________________
void Update ( void ) {
	if ( GetKeyUp( 'W' ) ) fPosY -= 1.0f;
	if ( GetKeyUp( 'S' ) ) fPosY += 1.0f;
	if ( GetKeyUp( 'A' ) ) fPosX -= 1.0f;
	if ( GetKeyUp( 'D' ) ) fPosX += 1.0f;
	if ( GetKeyUp( VK_UP ) ) Camera.fPosY -= 1.0f;
	if ( GetKeyUp( VK_DOWN ) ) Camera.fPosY += 1.0f;
	if ( GetKeyUp( VK_LEFT ) ) Camera.fPosX -= 1.0f;
	if ( GetKeyUp( VK_RIGHT ) ) Camera.fPosX += 1.0f;
	if ( GetKeyUp( '8' ) ) fScale -= 0.1f;
	if ( GetKeyUp( '9' ) ) fScale += 0.1f;
	Picture.Set(fPosX, fPosY, 3, 0, fScale, fScale, 1, 1, 0, 255, 255, 255, 100, false);
	Picture.Set(200, 200, 1, 0, 1.0f, 1.0f, 1, 1, 0, 255, 255, 255, 255, true);
	if (GetKeyUp('7')) Anim.Set(0,200, 200, 90, 1.0f, 1.0f, 255, 255, 255, 255, false, true);
	if (GetKeyUp('6')) Anim.Delete(0);
}

void Debug( void ) {
	char cText[ CHAR_MAX ];
	sprintf( cText, "A:%d W:%d S:%d D:%d", GetKeyUp( 'A' ), GetKeyUp( 'W' ), GetKeyUp( 'S' ), GetKeyUp( 'D' ) );
	DrawString( cText, 200, 0 );
}
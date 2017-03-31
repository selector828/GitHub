//[main.h 2017/03/18 - 2017/03/18 Flauzino Vinicius]_________________
#ifndef _SELECTOR_H_
#define _SELECTOR_H_
//[�C���N���[�h�t�@�C�� 2017/03/18 - 2017/03/18]_____________________
#include <windows.h>
#include <d3dx9.h>
#include <stdio.h>
#include <time.h>
//[���C�u�����[�t�@�C�� 2017/03/18 - 2017/03/18]_____________________
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )
#pragma comment( lib, "ws2_32.lib" )
//[�x�� 2017/03/18 - 2017/03/18]______________________________________
#pragma warning( disable: 4996 )
//[�萔��` 2017/03/18 - 2017/03/28]_________________________________
#define WINDOW_WIDTH  ( 800 )
#define WINDOW_HEIGHT ( 600	)
#define WINDOW_TITLE  "�E�B���h�E�^�C�g��"
#define PI ( 3.14159265359f / 360.0f )
#define PIC_MAX      ( 9999 )
#define KEY_NUM      (  256 )
#define PIC_NUM      ( 9999 )
#define ANIM_NUM     ( 9999 )
#define ANIM_PIC_NUM (  999 )
//[�\���̐錾 2017/03/18 - 2017/03/28]________________________________
typedef struct {
	float fPosX;
	float fPosY;
	float fRotZ;
	float fPosZ;
	float fScaleX;
	float fScaleY;
	UINT  uRed;
	UINT  uGreen;
	UINT  uBlue;
	UINT  uAlpha;
} CAMERA, *PCAMERA;
typedef struct {
	/*�ϐ�*/
	char               cFileName[CHAR_MAX];
	LPDIRECT3DTEXTURE9 pTexture;
	LPD3DXSPRITE       pSprite;
	float              Width;
	float              Height;
	/*�֐��v���g�^�C�v*/
	void Load(char cFileName[]);
	void Set(float fPosX, float fPosY, float fPosZ, float fRotZ, float fScaleX, float fScaleY, UINT uWidth, UINT uHeight, UINT uPattern, UINT uRed, UINT uGreen, UINT uBlue, UINT uAlpha, bool bApplyCamera);
} PICTURE, *PPICTURE;
typedef struct {
	/*�ϐ�*/
	PPICTURE           pPicture;
	float              fPosX;
	float              fPosY;
	float              fRotZ;
	float              fScaleX;
	float              fScaleY;
	UINT               uWidth;
	UINT               uHeight;
	UINT               uPattern;
	UINT               uRed;
	UINT               uGreen;
	UINT               uBlue;
	UINT               uAlpha;
	bool               bApplyCamera;
	/*�֐��v���g�^�C�v*/
	void Draw(void);
	void Release(void);
} PIC;
typedef struct {
	/*�ϐ�*/
	char     cFileName[CHAR_MAX];
	UINT     uWidth;
	UINT     uHeight;
	UINT     uPattern[ANIM_PIC_NUM];
	float    fPosX[ANIM_PIC_NUM];
	float    fPosY[ANIM_PIC_NUM];
	float    fPosZ[ANIM_PIC_NUM];
	float    fRotZ[ANIM_PIC_NUM];
	float    fScaleX[ANIM_PIC_NUM];
	float    fScaleY[ANIM_PIC_NUM];
	UINT     uRed[ANIM_PIC_NUM];
	UINT     uGreen[ANIM_PIC_NUM];
	UINT     uBlue[ANIM_PIC_NUM];
	UINT     uAlpha[ANIM_PIC_NUM];
	float    fDuration[ANIM_PIC_NUM];
	float    fSpeed;
	float    fTime;
	UINT     uPic;
	UINT     uMax;
	PPICTURE pPicture;
	/*�֐��v���g�^�C�v*/
	void Set( UINT uAnim, float fPosX, float fPosY, float fRotZ, float fScaleX, float fScaleY, UINT uRed, UINT uGreen, UINT uBlue, UINT uAlpha, bool bApplyCamera, bool bLoop);
	void Delete(UINT uAnim);
} ANIMATION, *PANIMATION;
typedef struct {
	/*�ϐ�*/
	PANIMATION pAnimation;
	float      fPosX;
	float      fPosY;
	float      fRotZ;
	float      fScaleX;
	float      fScaleY;
	UINT       uRed;
	UINT       uGreen;
	UINT       uBlue;
	UINT       uAlpha;
	bool       bApplyCamera;
	bool       bLoop;
	/*�֐��v���g�^�C�v*/
	void Draw(void);
	void Release(void);
} ANIM;
typedef struct {
	PICTURE   Pictures[PIC_NUM];
	ANIMATION Animations[ANIM_NUM];
} DATABASE;
//[�}�N����` 2017/03/18 - 2017/03/18]_______________________________
#define SAFE_RELEASE( p ) { if( p ) { ( p )->Release(); ( p ) = NULL; } }
//[�֐��v���g�^�C�v 2017/03/18 - 2017/03/28]_________________________
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT InitD3d(HWND);
void FreeDx(void);
void Init(void);
void Update(void);
void Draw(void);
void Debug(void);
void OnDebug(void);
void Pause(void);
void OnPause(void);
void OnApplicationQuit(void);
void DrawString(char cText[], int nX, int nY);
int  GetKeyUp( WPARAM wParam );
int  GetKeyDown( WPARAM wParam );
void ResetKeyDown( WPARAM wParam );
void ShowFPS(void);
void SetMainCamera(CAMERA * Camera);
PPICTURE LoadPicture(char cFileName[]);
PPICTURE SearchPicture( char cFileName[]);
void SetPicture(char cFileName[], float fPosX, float fPosY, float fPosZ, float fRotZ, float fScaleX, float fScaleY, UINT uWidth, UINT uHeight, UINT uPattern, UINT uRed, UINT uGreen, UINT uBlue, UINT uAlpha, bool bApplyCamera);
void OnClickButton(WPARAM wParam);
//[END]______________________________________________________________
#endif
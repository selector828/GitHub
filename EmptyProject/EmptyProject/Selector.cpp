//[main.cpp 2017/03/18 - 2017/03/27]___________________________________
#include "Selector.h"
//[グローバル変数宣言 2017/03/18 - 2017/03/27]________________________
LPDIRECT3D9        pD3d;
LPDIRECT3DDEVICE9  pDevice;
LPD3DXFONT         pFont;
PCAMERA            pMainCamera;
NETWORK            NetWork;
PIC                Pictures[PIC_NUM];
ANIM               Animations[ANIM_NUM];
char               cKeys[ KEY_NUM ];
bool               bKeys[ KEY_NUM ];
int                nKeys[ KEY_NUM ];
int                iKeys[ KEY_NUM ];
//[メイン関数 2017/03/18 - 2017/03/27]_________________________________
int WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, int CmdShow ) {
	HWND hWnd = NULL;

	WNDCLASSEX wndClass;
	wndClass.cbSize        = sizeof( wndClass );
	wndClass.style         = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc   = WndProc;
	wndClass.cbClsExtra    = 0;
	wndClass.cbWndExtra    = 0;
	wndClass.hInstance     = hInst;
	wndClass.hIcon         = LoadIcon( NULL, IDI_APPLICATION );
	wndClass.hCursor       = LoadCursor( NULL, IDC_ARROW );
	wndClass.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
	wndClass.lpszMenuName  = NULL;
	wndClass.lpszClassName = WINDOW_TITLE;
	wndClass.hIconSm       = NULL;

	RegisterClassEx( &wndClass );

	hWnd = CreateWindow( WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInst, NULL );
	ShowWindow( hWnd, SW_SHOW );
	UpdateWindow( hWnd );

	InitD3d( hWnd );

	MSG  msg;
	ZeroMemory( &msg, sizeof( msg ) );
	while( msg.message != WM_QUIT ) {
		if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) {
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} else {
			pDevice->BeginScene();
			pDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 30, 30, 30 ), 1.0f, 0 );
			Update();
			Draw();
			#ifdef _DEBUG
				Debug();
			#endif
			for( int nCnt = 0; nCnt < KEY_NUM; nCnt++ ) {
				( bKeys[ nCnt ] ) ? nKeys[ nCnt ]++ : nKeys[ nCnt ] = 0;
			}
			for( int nCnt = 0; nCnt < KEY_NUM; nCnt++ ) {
				if ( iKeys[ nCnt ] >= 0 ) { 
					iKeys[ nCnt ]++;
				} else {
					if( nKeys[ nCnt ] ) iKeys[ nCnt ] = 0;
				}
			}
			pDevice->EndScene();
			pDevice->Present( NULL, NULL, NULL, NULL );
			ShowFPS();
		}
	}
	FreeDx();
	return ( int )msg.wParam;
}
//[WndPrc関数 2017/03/18 - 2017/03/27]_________________________________
LRESULT CALLBACK WndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) {
	switch( uMsg ) {
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	case WM_KEYDOWN:
		cKeys[ wParam ] = '1';
		bKeys[ wParam ] = true;
		switch( ( char )wParam ) {
		case VK_ESCAPE:
			PostQuitMessage( 0 );
			break;
		}
		break;
	case WM_KEYUP:
		cKeys[ wParam ] = '0';
		bKeys[ wParam ] = false;
		break;
	}
	return DefWindowProc( hWnd, uMsg, wParam, lParam );
}
//[ユーザー関数 2017/03/18 - 2017/03/27]_______________________________
HRESULT InitD3d( HWND hWnd ) {
	if( NULL == ( pD3d = Direct3DCreate9( D3D_SDK_VERSION ) ) ) {
		MessageBox( 0, "Direct3Dの作成に失敗しました", "", MB_OK );
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;

	pD3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice );

	D3DXCreateFont( pDevice , 20 , 10 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , "MS ゴシック" , &pFont );

	for ( int nCnt = 0; nCnt < KEY_NUM; nCnt++ ) {
		ResetKeyDown( nCnt );
	}

	Init();

	return S_OK;
}
void PICTURE::Load(char cFileName[]) {
	D3DXCreateTextureFromFileEx( pDevice, cFileName, D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_DEFAULT, 0xff000000, 0, 0, &this->pTexture );
	D3DXCreateSprite( pDevice, &this->pSprite );
	IDirect3DSurface9 * pSurface;
	this->pTexture->GetSurfaceLevel( 0, &pSurface );
	D3DSURFACE_DESC SurfaceInfo;
	pSurface->GetDesc( &SurfaceInfo );
	this->Width = ( float )SurfaceInfo.Width + ( 16 - ( SurfaceInfo.Width % 16 ) ) % 16;
	this->Height = ( float )SurfaceInfo.Height + ( 16 - ( SurfaceInfo.Height % 16 ) ) % 16;
	SAFE_RELEASE( pSurface );
}
void PICTURE::Set(float fPosX, float fPosY, float fPosZ, float fRotZ, float fScaleX, float fScaleY, UINT uWidth, UINT uHeight, UINT uPattern, UINT uRed, UINT uGreen, UINT uBlue, UINT uAlpha, bool bApplyCamera) {
	Pictures[(UINT)fPosZ].fPosX = fPosX;
	Pictures[(UINT)fPosZ].fPosY = fPosY;
	Pictures[(UINT)fPosZ].fRotZ = fRotZ;
	Pictures[(UINT)fPosZ].fScaleX = fScaleX;
	Pictures[(UINT)fPosZ].fScaleY = fScaleY;
	Pictures[(UINT)fPosZ].uWidth = uWidth;
	Pictures[(UINT)fPosZ].uHeight = uHeight;
	Pictures[(UINT)fPosZ].uPattern = uPattern;
	Pictures[(UINT)fPosZ].uRed = uRed;
	Pictures[(UINT)fPosZ].uGreen = uGreen;
	Pictures[(UINT)fPosZ].uBlue = uBlue;
	Pictures[(UINT)fPosZ].uAlpha = uAlpha;
	Pictures[(UINT)fPosZ].bApplyCamera = bApplyCamera;
	Pictures[(UINT)fPosZ].pPicture = this;
}
void PIC::Draw(void) {
	if (this->pPicture != NULL) {
		RECT rect = { (LONG)this->pPicture->Width / this->uWidth * (this->uPattern % this->uWidth),
			(LONG)this->pPicture->Height / this->uHeight * (this->uPattern / this->uWidth),
			(LONG)this->pPicture->Width / uWidth * (this->uPattern % this->uWidth) + (LONG)this->pPicture->Width / this->uWidth,
			(LONG)this->pPicture->Height / this->uHeight * (this->uPattern / this->uWidth) + (LONG)this->pPicture->Height / this->uHeight };
		D3DXVECTOR3 vec3Center(this->fPosX + this->pPicture->Width / 2, this->fPosY + this->pPicture->Height / 2, 0);
		D3DXVECTOR3 vec3Position(this->fPosX, this->fPosY, 0);
		D3DXVECTOR3 vec3Scale(this->fScaleX, this->fScaleY, 1.0f);
		D3DXMATRIX matWorld, matScale, matRotationZ, matTranslation;
		if (bApplyCamera) {
			vec3Position.x -= pMainCamera->fPosX;
			vec3Position.y -= pMainCamera->fPosY;
			vec3Scale.x -= pMainCamera->fScaleX - 1.0f;
			vec3Scale.y -= pMainCamera->fScaleY - 1.0f;
			this->fRotZ -= pMainCamera->fRotZ;
			this->uRed -= pMainCamera->uRed - 255;
			this->uGreen -= pMainCamera->uGreen - 255;
			this->uBlue -= pMainCamera->uBlue - 255;
			this->uAlpha -= pMainCamera->uAlpha - 255;
		}
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, vec3Scale.x, vec3Scale.y, vec3Scale.z);
		D3DXMatrixTranslation(&matTranslation, this->fPosX, this->fPosY, 0);
		D3DXMatrixRotationZ(&matRotationZ, this->fRotZ * PI);
		matWorld = matScale * matRotationZ * matTranslation;
		this->pPicture->pSprite->SetTransform(&matWorld);
		this->pPicture->pSprite->Begin(D3DXSPRITE_ALPHABLEND);
		this->pPicture->pSprite->Draw(this->pPicture->pTexture, &rect, &vec3Center, &vec3Position, D3DCOLOR_ARGB(uAlpha, uRed, uGreen, uBlue));
		this->pPicture->pSprite->End();
		this->Release();
	}
}
void PIC::Release(void) {
	this->pPicture = NULL;
}
void ANIMATION::Set( UINT uAnim, float fPosX, float fPosY, float fRotZ, float fScaleX, float fScaleY, UINT uRed, UINT uGreen, UINT uBlue, UINT uAlpha, bool bApplyCamera, bool bLoop ) {
	if (Animations[uAnim].pAnimation == NULL) {
		Animations[uAnim].fPosX = fPosX;
		Animations[uAnim].fPosY = fPosY;
		Animations[uAnim].fRotZ = fRotZ;
		Animations[uAnim].fScaleX = fScaleX;
		Animations[uAnim].fScaleY = fScaleY;
		Animations[uAnim].uRed = uRed;
		Animations[uAnim].uGreen = uGreen;
		Animations[uAnim].uBlue = uBlue;
		Animations[uAnim].uAlpha = uAlpha;
		Animations[uAnim].bApplyCamera = bApplyCamera;
		Animations[uAnim].bLoop = bLoop;
		Animations[uAnim].pAnimation = this;
		Animations[uAnim].pAnimation->uPic = 0;
	}
}
void ANIMATION::Delete( UINT uAnim ) {
	Animations[uAnim].pAnimation = NULL;
}
void ANIM::Draw(void) {
	if (this->pAnimation != NULL) {
		this->pAnimation->pPicture->Set( this->fPosX + this->pAnimation->fPosX[this->pAnimation->uPic], this->fPosY + this->pAnimation->fPosY[this->pAnimation->uPic], this->pAnimation->fPosZ[this->pAnimation->uPic], this->fRotZ + this->pAnimation->fRotZ[this->pAnimation->uPic], this->fScaleX + this->pAnimation->fScaleX[this->pAnimation->uPic], this->fScaleY + this->pAnimation->fScaleY[this->pAnimation->uPic], this->pAnimation->uWidth, this->pAnimation->uHeight, this->pAnimation->uPattern[this->pAnimation->uPic], this->uRed + this->pAnimation->uRed[this->pAnimation->uPic], this->uGreen + this->pAnimation->uGreen[this->pAnimation->uPic], this->uBlue + this->pAnimation->uBlue[this->pAnimation->uPic], this->uAlpha + this->pAnimation->uAlpha[this->pAnimation->uPic], bApplyCamera );
		this->pAnimation->fTime += this->pAnimation->fSpeed;
		if (this->pAnimation->fTime > this->pAnimation->fDuration[this->pAnimation->uPic]) this->pAnimation->uPic++, this->pAnimation->fTime = 0;
		if (this->pAnimation->uPic > this->pAnimation->uMax || this->pAnimation->uPic > ANIM_PIC_NUM) {
			this->pAnimation->uPic = 0;
			if (!this->bLoop) this->Release();
		}
	}
}
void ANIM::Release(void) {
	this->pAnimation = NULL;
}
void NETWORK::Init( void ) {
	WSADATA wsaData;
	SOCKET  sock;
	struct  sockaddr_in addr;
	struct  sockaddr_in client;
	struct  sockaddr_in server;

	int     nLen;
	int     nErr;
	char    cJoinMessage[ CHAR_MAX ];
	char    cMessage[ CHAR_MAX ];

	nErr = WSAStartup( MAKEWORD( 2, 0 ), &wsaData );

	if ( nErr != 0 ) {
		switch ( nErr ) {
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY\n");
			break;
		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED\n");
			break;
		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS\n");
			break;
		case WSAEPROCLIM:
			printf("WSAEPROCLIM\n");
			break;
		case WSAEFAULT:
			printf("WSAEFAULT\n");
			break;
		}
		exit(0);
	}

	sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( sock == INVALID_SOCKET ) exit(0);

	if ( this->nType == 1 ) {
		addr.sin_family = AF_INET;
		addr.sin_port = htons( 12345 );
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		bind( sock, ( struct sockaddr * )&addr, sizeof( addr ) );

		listen( sock, 1 );

		nLen = sizeof( client );
		printf( "Client待ち,,,\n" );
		this->sock = accept( sock, ( struct sockaddr * )&client, &nLen );
		sprintf( cMessage, "ルームに入場しました。\n" );
		send( this->sock, cMessage, strlen( cMessage ), 0 );
		memset( cJoinMessage, 0, sizeof( cJoinMessage ) );
		recv( this->sock, cJoinMessage, sizeof( cJoinMessage ), 0 );
		printf( "%s", cJoinMessage );
	} else if ( this->nType == 2 ) {
		server.sin_family = AF_INET;
		server.sin_port = htons( 12345 );
		server.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1" );
		connect( sock, ( struct sockaddr * )&server, sizeof( server ) );
		memset( cJoinMessage, 0, sizeof( cJoinMessage ) );
		if ( recv( sock, cJoinMessage, sizeof( cJoinMessage ), 0 ) == - 1 ) exit( 0 );
		send( sock, cMessage, strlen( cMessage ), 0 );
		this->sock = sock;
	}
}
void NETWORK::Update( void ) {

}
void Draw(void) {
	for (UINT n = 0; n < ANIM_NUM; n++) {
		Animations[n].Draw();
	}
	for (UINT n = (UINT)pMainCamera->fPosZ; n < PIC_NUM; n++) {
		Pictures[n].Draw();
	}
}
void DrawString( char cText[], int nX, int nY ) {
	RECT rc;
	rc.left   = nX;
	rc.top    = nY;
	rc.right  = WINDOW_WIDTH;
	rc.bottom = WINDOW_HEIGHT;
	pFont->DrawText( NULL , cText , -1 , &rc , NULL , 0xFF88FF88 );
}
void FreeDx( void ) {
	SAFE_RELEASE( pDevice );
	SAFE_RELEASE( pD3d );
	SAFE_RELEASE(pFont);
}
void ShowFPS ( void ) {
	static int nFrameCount = 0;
	static int nStartTime = 0;
	static float fFPS = 0;
	static int nNow = 0;
	char c[ CHAR_MAX ] = {};
	nNow = clock();
	if ( nNow - nStartTime > 1000 ) {
		fFPS = nFrameCount / ( ( nNow - nStartTime ) / 1000.0f );
		nStartTime = nNow;
		nFrameCount = 0;
		sprintf( c, "【FPS:%3.1f】", fFPS );
		SetWindowText( GetActiveWindow(), c );
	}
	nFrameCount++;
}
int GetKeyUp( WPARAM wParam ) {
	return nKeys[ wParam ];
}
int GetKeyDown( WPARAM wParam ) {

	return iKeys[ wParam ];
}
void ResetKeyDown( WPARAM wParam ) {
	iKeys[ wParam ] = -1;
}
void SetMainCamera( CAMERA * Camera ) {
	pMainCamera = Camera;
}
//[END]________________________________________________________________

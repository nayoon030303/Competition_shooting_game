#pragma once


#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) 
#include <strsafe.h>
#pragma warning( default : 4996 )

#include "TextureManager.h"
#include "InputManager.h"
#include "StageManager.h"
#include "GameSystem.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PLAYER 1000
#define TITLE 2000
#define BACKGROUND1 3000
#define BACKGROUND2 4000
#define PLAYERBULLET1 5000
#define PLAYERBULLET2 6000
#define ENEMYA 7000
#define ENEMYB 8000
#define ENEMYBOSS 9000
#define EENMYBOSSF 9900
#define HP 1100
#define ITEM 2200

#define LEVEL2 200
#define LEVEL3 500
#define LEVEL4 800
#define LEVEL5 1200



extern HWND hWnd;
extern LPDIRECT3D9         g_pD3D ;
extern LPDIRECT3DDEVICE9   g_pd3dDevice;
extern float deltatime;
extern ID3DXFont* g_pFont;

extern TextureManager textureManager;
extern InputMananger inputManager;
extern StageManager stageManager;
extern GameSystem gameSystem;


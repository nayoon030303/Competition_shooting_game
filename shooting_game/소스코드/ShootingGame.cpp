// ShootingGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "ShootingGame.h"
#include "global.h"


#define MAX_LOADSTRING 100


HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                  
WCHAR szWindowClass[MAX_LOADSTRING];            

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


HRESULT InitD3D(HWND hWnd);

HWND hWnd;
LPDIRECT3D9         g_pD3D = NULL;
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL;

ID3DXFont*	 g_pFont = NULL;


TextureManager textureManager;
InputMananger inputManager;
StageManager stageManager; 
GameSystem gameSystem;

float deltatime = 0.03;
DWORD pre;

void InitMyobject()
{
	textureManager.LoadTexture(L"player.png", PLAYER);
	textureManager.LoadTexture(L"title.png", TITLE);
	textureManager.LoadTexture(L"background1.png", BACKGROUND1);
	textureManager.LoadTexture(L"background2.png", BACKGROUND2);
	textureManager.LoadTexture(L"playerBullet1.png", PLAYERBULLET1);
	textureManager.LoadTexture(L"playerBullet2.png", PLAYERBULLET2);
	textureManager.LoadTexture(L"11B.png", ENEMYBOSS);
	textureManager.LoadTexture(L"enemyA.png", ENEMYA);
	textureManager.LoadTexture(L"enemyB.png", ENEMYB);
	textureManager.LoadTexture(L"hp.png", HP);
	textureManager.LoadTexture(L"Item.png", ITEM);
	textureManager.LoadTexture(L"11B.png", EENMYBOSSF);

	pre = GetTickCount();
}

void Render()
{
	
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		stageManager.Render();


		g_pd3dDevice->EndScene();
	}
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

}

void Update()
{
	DWORD cur = GetTickCount();
	float diff = pre - cur;
	diff = diff / 1000.0f;

	if (diff>0.016) 
	{
		diff = 0.016;
	}

	pre = cur;

	stageManager.Update();
	inputManager.Update();

}
void GameLoop()
{
	Render();
	Update();

}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

   
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTINGGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

   
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHOOTINGGAME));

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			GameLoop();
		}
			
	}

    return (int) msg.wParam;
}




ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTINGGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   InitD3D(hWnd);
   InitMyobject();

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_KEYDOWN:
		inputManager.key[wParam] = 1;
		break;
	case WM_KEYUP:
		inputManager.key[wParam] = 0;
		break;
	case WM_LBUTTONDOWN:
		inputManager.key[VK_LBUTTON]=1;
		break;
	case WM_LBUTTONUP:
		inputManager.key[VK_LBUTTON] = 0;
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


HRESULT InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	/*d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;*/

	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = WINDOW_WIDTH;
	d3dpp.BackBufferHeight = WINDOW_HEIGHT;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn on ambient lighting 
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);




	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	TCHAR g_strFont[LF_FACESIZE];
	int  g_nFontSize = 15;

	int nHeight = -g_nFontSize * nLogPixelsY / 72;
	D3DXCreateFont(g_pd3dDevice,            // D3D device
		nHeight,               // Height
		0,                     // Width
		FW_BOLD,               // Weight
		1,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		g_strFont,              // pFaceName
		&g_pFont);              // ppFont



	return S_OK;
}


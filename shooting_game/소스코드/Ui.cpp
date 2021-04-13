#include "stdafx.h"
#include "Ui.h"
#include "global.h"

Ui::Ui()
{


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


}

void Render()
{

}

void Update()
{

}

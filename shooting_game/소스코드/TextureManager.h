#pragma once

#include <d3dx9.h>
#include <vector>

using namespace std;

class TextureElement
{
public:
	int id;
	LPDIRECT3DTEXTURE9  g_pTexture;
	ID3DXSprite* g_Sprite;

};

class TextureManager
{
public:
	void LoadTexture(const TCHAR* name, int id);
	TextureElement* GetTexture(int id);
	vector<TextureElement*> elements;
};
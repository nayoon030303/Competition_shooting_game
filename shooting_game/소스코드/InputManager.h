#pragma once

class InputMananger
{
public:
	char key[256];
	char prevKey[256];
	void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			prevKey[i] = key[i];
		}
	}
};
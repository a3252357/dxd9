#include "TextureManager.h"

#define MAKEUS(a, b)    ((unsigned short) ( ((unsigned short)(a))<<8 | ((unsigned short)(b)) ))
#define MAKEUI(a,b,c,d) ((unsigned int) ( ((unsigned int)(a)) << 24 | ((unsigned int)(b)) << 16 | ((unsigned int)(c)) << 8 | ((unsigned int)(d)) ))

#define M_DATA  0x00
#define M_SOF0  0xc0
#define M_DHT   0xc4
#define M_SOI   0xd8
#define M_EOI   0xd9
#define M_SOS   0xda
#define M_DQT   0xdb
#define M_DNL   0xdc
#define M_DRI   0xdd
#define M_APP0  0xe0
#define M_APPF  0xef
#define M_COM   0xfe
int GetPNGWidthHeight(const char* path, unsigned int* punWidth, unsigned int* punHeight)
{
	int Finished = 0;
	unsigned char uc[4];
	FILE *pfRead;

	*punWidth = 0;
	*punHeight = 0;

	if (fopen_s(&pfRead, path, "rb") != 0)
	{
		printf("[GetPNGWidthHeight]:can't open file:%s\n", path);
		return -1;
	}

	for (int i = 0; i < 4; i++)
		fread(&uc[i], sizeof(unsigned char), 1, pfRead);
	if (MAKEUI(uc[0], uc[1], uc[2], uc[3]) != 0x89504e47)
		printf("[GetPNGWidthHeight]:png format error\n", path);
	for (int i = 0; i < 4; i++)
		fread(&uc[i], sizeof(unsigned char), 1, pfRead);
	if (MAKEUI(uc[0], uc[1], uc[2], uc[3]) != 0x0d0a1a0a)
		printf("[GetPNGWidthHeight]:png format error\n", path);

	fseek(pfRead, 16, SEEK_SET);
	for (int i = 0; i < 4; i++)
		fread(&uc[i], sizeof(unsigned char), 1, pfRead);
	*punWidth = MAKEUI(uc[0], uc[1], uc[2], uc[3]);
	for (int i = 0; i < 4; i++)
		fread(&uc[i], sizeof(unsigned char), 1, pfRead);
	*punHeight = MAKEUI(uc[0], uc[1], uc[2], uc[3]);
	fclose(pfRead);

}

int GetJPEGWidthHeight(const char* path, unsigned int *punWidth, unsigned int *punHeight)
{
	int Finished = 0;
	unsigned char id, ucHigh, ucLow;
	FILE *pfRead;

	*punWidth = 0;
	*punHeight = 0;

	if (fopen_s(&pfRead, path, "rb") != 0)
	{
		printf("[GetJPEGWidthHeight]:can't open file:%s\n", path);
		return -1;
	}

	while (!Finished)
	{
		if (!fread(&id, sizeof(char), 1, pfRead) || id != 0xff || !fread(&id, sizeof(char), 1, pfRead))
		{
			Finished = -2;
			break;
		}

		if (id >= M_APP0 && id <= M_APPF)
		{
			fread(&ucHigh, sizeof(char), 1, pfRead);
			fread(&ucLow, sizeof(char), 1, pfRead);
			fseek(pfRead, (long)(MAKEUS(ucHigh, ucLow) - 2), SEEK_CUR);
			continue;
		}

		switch (id)
		{
		case M_SOI:
			break;

		case M_COM:
		case M_DQT:
		case M_DHT:
		case M_DNL:
		case M_DRI:
			fread(&ucHigh, sizeof(char), 1, pfRead);
			fread(&ucLow, sizeof(char), 1, pfRead);
			fseek(pfRead, (long)(MAKEUS(ucHigh, ucLow) - 2), SEEK_CUR);
			break;

		case M_SOF0:
			fseek(pfRead, 3L, SEEK_CUR);
			fread(&ucHigh, sizeof(char), 1, pfRead);
			fread(&ucLow, sizeof(char), 1, pfRead);
			*punHeight = (unsigned int)MAKEUS(ucHigh, ucLow);
			fread(&ucHigh, sizeof(char), 1, pfRead);
			fread(&ucLow, sizeof(char), 1, pfRead);
			*punWidth = (unsigned int)MAKEUS(ucHigh, ucLow);
			return 0;

		case M_SOS:
		case M_EOI:
		case M_DATA:
			Finished = -1;
			break;

		default:
			fread(&ucHigh, sizeof(char), 1, pfRead);
			fread(&ucLow, sizeof(char), 1, pfRead);
			printf("[GetJPEGWidthHeight]:unknown id: 0x%x ;  length=%hd\n", id, MAKEUS(ucHigh, ucLow));
			if (fseek(pfRead, (long)(MAKEUS(ucHigh, ucLow) - 2), SEEK_CUR) != 0)
				Finished = -2;
			break;
		}
	}

	if (Finished == -1)
		printf("[GetJPEGWidthHeight]:can't find SOF0!\n");
	else if (Finished == -2)
		printf("[GetJPEGWidthHeight]:jpeg format error!\n");
	fclose(pfRead);
	return -1;
}

void GetPicWidthHeight(const char* path, unsigned int *punWidth, unsigned int *punHeight)
{
	int len = strlen(path);
	if (len <= 4)
		printf("[GetPicWidthHeight]:picture name is too short\n");
	if (!strncmp(path + len - 3, "jpg", 3))
		GetJPEGWidthHeight(path, punWidth, punHeight);
	else if (!strncmp(path + len - 3, "png", 3))
		GetPNGWidthHeight(path, punWidth, punHeight);
	else
		printf("[GetPicWidthHeight]:only support jpg and png\n");
}

TEXTURE_MAP TextureManager::TextureMap;
LPDIRECT3DTEXTURE9 TextureManager::ptexture9;

Texture2d * TextureManager::getTexture(LPCWSTR path, int x, int y, int w, int h)
{
	TEXTURE_MAP::reverse_iterator iter;

	for (iter = TextureMap.rbegin(); iter != TextureMap.rend(); iter++)
	{
		if (lstrcmpW(iter->first, path) == 0)
			return new Texture2d(iter->second, x, y, w, h);
	}
	unsigned int ws = 0, hs = 0;
	GetPicWidthHeight(StringUtil::wstr2str(path).c_str(), &ws, &hs);
	HRESULT hr = D3DXCreateTextureFromFileEx(D3DUtil::getD3DDev(),
		path,
		ws,
		hs,
		D3DX_DEFAULT,
		0,
		D3DFMT_A1R5G5B5,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE,
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0, 0, 0, 255),
		NULL,
		NULL,
		&ptexture9);
	if (hr == S_OK) {
		TextureMap.insert(TEXTURE_MAP::value_type(path, ptexture9));
		return new Texture2d(ptexture9, x, y, w, h);
	}
	else {
		return NULL;
	}
}
	

Texture2d * TextureManager::getTexture(LPCWSTR path)
{
	TEXTURE_MAP::reverse_iterator iter;
	D3DSURFACE_DESC desc;
	for (iter = TextureMap.rbegin(); iter != TextureMap.rend(); iter++)
	{
		if (lstrcmpW(iter->first, path) == 0)
		{
			iter->second->GetLevelDesc(0, &desc);
			return new Texture2d(iter->second, 0, 0, desc.Width, desc.Height);
		}
	}
	unsigned int ws = 0, hs = 0;
	GetPicWidthHeight(StringUtil::wstr2str(path).c_str(), &ws, &hs);
	HRESULT hr = D3DXCreateTextureFromFileEx(D3DUtil::getD3DDev(),
		path,
		ws,
		hs,
		D3DX_DEFAULT,
		0,
		D3DFMT_A1R5G5B5,
		D3DPOOL_MANAGED,
		D3DX_FILTER_TRIANGLE,
		D3DX_FILTER_TRIANGLE,
		D3DCOLOR_RGBA(0, 0, 0, 255),
		NULL,
		NULL,
		&ptexture9);
	if (hr == S_OK) {
		TextureMap.insert(TEXTURE_MAP::value_type(path, ptexture9));
		ptexture9->GetLevelDesc(0, &desc);
		return new Texture2d(ptexture9, 0, 0, desc.Width, desc.Height);
	}
	else {
		return NULL;
	}
}



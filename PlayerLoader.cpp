#include "PlayerLoader.h"


PlayerLoader::PlayerLoader()
{
	vector<vector<Texture2d *>> array(6);
	for (int i = 0; i < 6; i++) {
		array[i].resize(9);
		for (int j = 0; j < 9; j++) {
			Texture2d* t = D3DUtil::getTexture(L"img/Actor1_1.png", j * 64, i * 64, 64, 64);
			array[i][j] = t;
		}
	}
	playeranimations.resize(18);
	for (int i = 0; i < 18; i++) {
		playeranimations[i] = new AnimationFrame();
	}
	for (int i = 0; i < 54; i++) {
		int m = i / 9;
		int n = i % 9;
		Texture2d* t = array[m][n];
		playeranimations[i/3]->Add_AnimationSprite(array[m][n], 0, 0, 0,0.5,0.5,1000);
	}
	//AnimationFrame::Start(playeranimations[1]);
	playeranimations[1]->Start();
}


PlayerLoader::~PlayerLoader()
{
}

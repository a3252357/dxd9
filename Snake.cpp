#include "Snake.h"
#include "UserTileLayer.h"
#include <stdio.h>
#include <spine/spine.h>
#include <spine/Debug.h>
Snake::Snake()
{
	DEBUG__LOG("1111");
}

Snake::~Snake()
{
}

HRESULT Snake::Update()
{
	//spritesManager->Update();
	//maps->userTileLayer->Update();
	a->update(1);
	return S_OK;
}
void callback(AnimationState* state, EventType type, TrackEntry* entry, spine::Event* event);
HRESULT Snake::Render()
{
	a->Update();
	//maps->userTileLayer->Render();
	//spritesManager->Render();
	return S_OK;
}
void loadBinary(const spine::String &binaryFile, const spine::String &atlasFile, Atlas *&atlas, SkeletonData *&skeletonData,
	AnimationStateData *&stateData, Skeleton *&skeleton, AnimationState *&state) {
	atlas = new(__FILE__, __LINE__) Atlas(atlasFile, &HuangTextureLoader());
	assert(atlas != NULL);

	SkeletonBinary binary(atlas);
	skeletonData = binary.readSkeletonDataFile(binaryFile);
	assert(skeletonData);

	//skeleton = new(__FILE__, __LINE__) Skeleton(skeletonData);
	//assert(skeleton != NULL);

	//stateData = new(__FILE__, __LINE__) AnimationStateData(skeletonData);
	//assert(stateData != NULL);
	//stateData->setDefaultMix(0.4f);

	//state = new(__FILE__, __LINE__) AnimationState(stateData);
}

void loadJson(const spine::String &jsonFile, const spine::String &atlasFile, Atlas *&atlas, SkeletonData *&skeletonData,
	AnimationStateData *&stateData, Skeleton *&skeleton, AnimationState *&state) {
	atlas = new(__FILE__, __LINE__) Atlas(atlasFile,  &HuangTextureLoader());
	assert(atlas != NULL);

	SkeletonJson json(atlas);
	skeletonData = json.readSkeletonDataFile(jsonFile);
	assert(skeletonData);

	skeleton = new(__FILE__, __LINE__) Skeleton(skeletonData);
	assert(skeleton != NULL);

	stateData = new(__FILE__, __LINE__) AnimationStateData(skeletonData);
	assert(stateData != NULL);
	stateData->setDefaultMix(0.4f);

	state = new(__FILE__, __LINE__) AnimationState(stateData);
}

void dispose(Atlas *atlas, SkeletonData *skeletonData, AnimationStateData *stateData, Skeleton *skeleton,
	AnimationState *state) {
	delete skeleton;
	delete state;
	delete stateData;
	delete skeletonData;
	delete atlas;
}

struct TestData {
	TestData(const spine::String &jsonSkeleton, const spine::String &binarySkeleton, const spine::String &atlas) : _jsonSkeleton(
		jsonSkeleton), _binarySkeleton(binarySkeleton), _atlas(atlas) {}

	spine::String _jsonSkeleton;
	spine::String _binarySkeleton;
	spine::String _atlas;
};
HRESULT Snake::Init()
{
	Vector<TestData> testData;
	testData.add(TestData("C:/Users/musi/Desktop/39.105.4.19/ConsoleApplication1/x64/Debug/coin/export/coin-pro.json", "C:/Users/musi/Desktop/39.105.4.19/ConsoleApplication1/x64/Debug/coin/export/coin-pro.skel", "C:/Users/musi/Desktop/39.105.4.19/ConsoleApplication1/x64/Debug/coin/export/coin.atlas"));
	/*testData.add(TestData("testdata/goblins/goblins-pro.json", "testdata/goblins/goblins-pro.skel",
							  "testdata/goblins/goblins.atlas"));
		testData.add(TestData("testdata/raptor/raptor-pro.json", "testdata/raptor/raptor-pro.skel",
							  "testdata/raptor/raptor.atlas"));
		testData.add(TestData("testdata/spineboy/spineboy-pro.json", "testdata/spineboy/spineboy-pro.skel",
							  "testdata/spineboy/spineboy.atlas"));
		testData.add(TestData("testdata/stretchyman/stretchyman-pro.json", "testdata/stretchyman/stretchyman-pro.skel",
							  "testdata/stretchyman/stretchyman.atlas"));
		testData.add(TestData("testdata/tank/tank-pro.json", "testdata/tank/tank-pro.skel", "testdata/tank/tank.atlas"));*/

	for (size_t i = 0; i < 1; i++) {
		TestData &data = testData[i];
		Atlas *atlas = NULL;
		SkeletonData *skeletonData = NULL;
		AnimationStateData *stateData = NULL;
		Skeleton *skeleton = NULL;
		AnimationState *state = NULL;

		printf("Loading %s\n", data._jsonSkeleton.buffer());
		loadJson(data._jsonSkeleton, data._atlas, atlas, skeletonData, stateData, skeleton, state);
	//	dispose(atlas, skeletonData, stateData, skeleton, state);

		printf("Loading %s\n", data._binarySkeleton.buffer());
		loadBinary(data._binarySkeleton, data._atlas, atlas, skeletonData, stateData, skeleton, state);
	//	dispose(atlas, skeletonData, stateData, skeleton, state);
		a = new SkeletonDrawable(skeletonData, stateData);
		Skeleton* skeleto1 = a->skeleton;
		skeleto1->setToSetupPose();
		skeleto1->setPosition(320, 590);
		skeleto1->updateWorldTransform();
	//	a->state->setListener(callback);
		a->state->addAnimation(0, "rotate", true,0);
		a->update(1);
		Slot* headSlot = skeleton->findSlot("head");
	}
	maps = new MapLoader();
	snakeBody = make_shared<SnakeBody>();
	spritesManager =make_shared<Sprites>();
	g_pTexturewall = D3DUtil::getTexture(L"img\wall\brick.png");
	D3DMATERIAL9 mtrl;
	::ZeroMemory(&mtrl, sizeof(mtrl));
	mtrl.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.7f, 1.0f);
	mtrl.Diffuse = D3DXCOLOR(0.6f, 0.6f, 0.6f, 1.0f);
	mtrl.Specular = D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.3f);
	mtrl.Emissive = D3DXCOLOR(0.3f, 0.0f, 0.1f, 1.0f);
	int z = -1;
	int j = 0;
	D3DUtil::getD3DDev()->SetMaterial(&mtrl);
	for (int i = 0; i < wallnum;) {
		if (z+1 < SCREEN_WIDTH / BOX_WIDTH)
		{
			z++;
		}
		else {
			j++;z = 0;
		}
		if (z == 0 || j == 0 || (z + 1) >= SCREEN_WIDTH / BOX_WIDTH || (j + 1) >= SCREEN_HEIGHT / BOX_WIDTH)
		{
			shared_ptr<Sprite> wall = make_shared<Sprite>();
			wall->Sprite_Init(L"img/wall/brick.png", z*BOX_WIDTH, j * BOX_WIDTH, 0,0,0, BOX_WIDTH, BOX_WIDTH);
			spritesManager->AddSprite(wall);
			i++;
		}
	}
	for (int i = 0; i < snakenum; i++) {
		shared_ptr<Sprite> snake = make_shared<Sprite>();
		snake->Sprite_Init(L"img/wall/brick.png", BOX_WIDTH*(5 - i), BOX_WIDTH * 5, 0, 0, 0, BOX_WIDTH, BOX_WIDTH);
		snakeBody->Add(snake);
	}
	spritesManager->AddSprite(snakeBody);
//	snakeBody->start(100,1,10);
	CallBackTimer<SnakeBody>* snaketimer = new CallBackTimer<SnakeBody>(snakeBody,&SnakeBody::snake);
	snaketimer->start(100, 1, 10);
	// 创建并初始化地形  
	//g_pTerrain = new TerrainClass();
	//g_pTerrain->getTerrain(64*100, L"img/wall/brick.png");      //从文件加载高度图和纹理  
	//g_pTerrain->InitTerrain(64, 100, 10.0f, 1.0f);  //四个值分别是顶点行数，顶点列数，顶点间间距，缩放系数  
	//三步曲之一，开启Alpha融合  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	//三步曲之二，设置融合因子  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//三步曲之三，设置融合运算方式  
	D3DUtil::getD3DDev()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);  //这句设置运算方式为D3DBLENDOP_ADD的代码Direct3D默认为我们写了，所以注释掉这句也没大碍 
	lastTime = timeGetTime()*0.01f; //将当前时间currentTime赋给持续时间lastTime，作为下一秒的基准时间
	return S_OK;
}

void callback(AnimationState* state, EventType type, TrackEntry* entry, spine::Event* event) {
	const spine::String& animationName = (entry && entry->getAnimation()) ? entry->getAnimation()->getName() : spine::String("");

	switch (type) {
	case EventType_Start:
		printf("%d start: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case EventType_Interrupt:
		printf("%d interrupt: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case EventType_End:
		printf("%d end: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case EventType_Complete:
		printf("%d complete: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case EventType_Dispose:
		printf("%d dispose: %s\n", entry->getTrackIndex(), animationName.buffer());
		break;
	case EventType_Event:
		printf("%d event: %s, %s: %d, %f, %s %f %f\n", entry->getTrackIndex(), animationName.buffer(), event->getData().getName().buffer(), event->getIntValue(), event->getFloatValue(),
			event->getStringValue().buffer(), event->getVolume(), event->getBalance());
		break;
	}
	fflush(stdout);
}
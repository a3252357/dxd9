#include "UserObejectLayer.h"



UserObejectLayer::UserObejectLayer(const tmx::Map& map, std::size_t layerIdx)
{
	const auto& layers = map.getLayers();

	if (layerIdx >= layers.size() || (layers[layerIdx]->getType() != tmx::Layer::Type::Object))
	{
		std::cout << "Invalid layer index or layer type, layer will be empty" << std::endl;
		return;
	}
	const auto layer = dynamic_cast<const tmx::ObjectGroup*>(layers[layerIdx].get());
	vector<tmx::Property> propertys= layer->getProperties();
	vector<tmx::Object> objects = layer->getObjects();
	for (int i = 0;i < propertys.size();i++) {
		tmx::Property a = propertys[i];
		if (a.getName() == "type"&&a.getType()== tmx::Property::Type::String&&a.getStringValue()=="box layer") {
			
		}
	}
	for (int i = 0;i < objects.size();i++) {
		tmx::Object a = objects[i];
//		t
		string str=a.getName();
	}


}


UserObejectLayer::~UserObejectLayer()
{
}

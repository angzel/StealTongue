#pragma once

#include "Resource.hpp"

class LoadLayer : public Layer
{
public:
	LoadLayer(std::function<void()> onOK)
	{
		auto bg = new ColoredRect;
		this->addNode(bg);
		bg->setPosition(Res::W()/2, Res::H()/4);
		bg->setAnchor(0.5f, 0.5f);
		bg->setRectSize({400, 20});
		bg->setColor(eColor::White);

		auto ice = new Sprite;
		this->addNode(ice);

		ice->setTexture(Textures::Get()->getTexture("img/ice.png"));
		ice->setPosition(Res::W()/2, Res::H()/4 + 50);
		ice->setAnchor({0.5, 0.5});
		
		this->runAction(ActionCall::Create([onOK](float)->bool {
			onOK();
			return false;
		}, 1, 2));
	}
};

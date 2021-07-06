#pragma once

#include "Resource.hpp"

class PopLayer : public Layer
{
public:
	PopLayer(std::string s)
	{
		auto rect = new ColoredRect;
		rect->setRectSize({Res::W(), Res::H()/2});
		rect->setPosition(Res::W()/2, Res::H()/2);
		rect->setAnchor({0.5, 0.5});
		rect->setColor(Color(0x88));
		this->addNode(rect);

		auto text = new Label;
		text->setText(s);
		text->setFont(Res::GetTextFont());
		text->setFontSize(30);
		text->setMaxWidthInPixels(Res::W()*0.75);
		text->setPosition(Res::W()/2, Res::H()/2);
		text->setAnchor({0.5, 0.5});
		this->addNode(text);
	}
};

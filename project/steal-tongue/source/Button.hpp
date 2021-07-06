#pragma once

#include "Resource.hpp"

class Button : public Layer
{
protected:
	Sprite * mBG;
	Label * mLabel;
	Size2 mSize;
public:
	Button()
	{
		#if 0
		auto r = new ColoredRect;
		r->setAnchor(0.5, 0.5);
		r->setRectSize({100, 100});
		r->setPosition(0, 0);
		this->addNode(r);
		#endif
		
		mBG = new Sprite;
		mBG->setTexture(Textures::Get()->getTexture("img/button.png"));
		mBG->setAnchor({0.5, 0.5});
		this->addNode(mBG);
//		mBG->setRotation(0.2);
		mSize = mBG->getContentSize();

		mLabel = new Label;
		mLabel->setFont(Res::GetTextFont());
		mLabel->setAnchor({0.5, 0.5});
		mLabel->setFontSize(32);
		mLabel->setColor(Color(0x333333ff));
		mLabel->setUnderlineInPixels(1);
		mLabel->setBGAlpha(0);
		this->addNode(mLabel);
	}
	void setText(std::string const & text)
	{
		mLabel->setText(text);
		auto lbsize = mLabel->getContentSize();
		auto bgsize = mBG->getContentSize();
		lbsize.w += 20;
		if(lbsize.w > bgsize.w)
		{
			mBG->setScale({lbsize.w / bgsize.w, 1});
		}
		else
		{
			mBG->setScale({1, 1});
		}
	}
	void onTouch()
	{
		this->stopAllActions();
		this->setScale(1, 1);
		auto s1 = ActionScale2d::Create(this, 0.2, {0.3, 0.3}, {0, 0});
		auto s2 = ActionScale2d::Create(this, 0.2, {-0.3, -0.3}, {0, 0});
		auto c = ActionCall::Create([this](float) {
			this->setScale(1, 1);
			return false;
		}, 1);
		this->runAction(ActionSequence::Create({s1, s2, c}));
	}
//	void setPosition(Point2 p)
//	{
//		mBG->setPosition(p);
//		mLabel->setPosition(p.x, p.y);
//	}
	bool containPoint(Point2 p)
	{
//		return Res::IsPointIn(p, mBG);
		auto pos = this->getPosition();
		auto dx = fabsf(p.x - pos.x);
		auto dy = fabsf(p.y - pos.y);
		return (dx < mSize.w/2 && dy < mSize.h/2);
	}
};

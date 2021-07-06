#pragma once

#include "Resource.hpp"
#include "Drum.hpp"
#include "Button.hpp"

class MainPlayer : public Layer
{
public:
	Pt2 size;
	Drum * mDrum;
	Button* mSetting = nullptr;
	//	std::shared_ptr<Button> mUpgrade = nullptr;
	
	Label * mTrialTips = nullptr;
public:
	MainPlayer()
	{
		mDrum = new Drum(true, 1);
		this->addNode(mDrum);
		mDrum->setScale(0.9);
		mDrum->setPosition(Res::W()/2, Res::H()/2);
		
		mSetting = new Button;
		mSetting->setText(Res::local.getText("setting"));
		mSetting->setPosition({84, Res::H() - 52});
		this->addNode(mSetting);
		/*
		 
		 
		 mUpgrade = MakeShared(new Button);
		 mUpgrade->setText(Res::local.getText(Res::IsPro()?"about":"upgrade"));
		 mUpgrade->setPosition(Pt2(Res::W() - 84, Res::H() - 52));
		 mUpgrade->addTo(mView);
		 
		 if(!Res::IsPro())
		 {
		 auto lb = Label::Create();
		 lb->setFont(Res::GetTextFont());
		 lb->setText(Res::local.getText("this-is-a-trial")); //"这是一个试用版，升级以获取全部功能!"
		 lb->setFontSize(28);
		 lb->setMaskColor(Color(0x222222ff));
		 lb->setAnchor({0.5, 0.5});
		 lb->setPosition({Res::W()/2, 40});
		 mView->addChild(lb);
		 mTrialTips = lb;
		 }
		 */
	}
	
	void refresh();
	
	void onPro()
	{
		if(!mTrialTips) return;
		
		mTrialTips->remove();
		mTrialTips = nullptr;
		//		mUpgrade->setText(Res::local.getText("about"));
	}
	void addParticle(Point2 p);
	
	virtual Node * onTouchDown(AppTouch const & touch) override
	{
		auto p = Point2{touch.x * Res::W(), touch.y * Res::H()};
		
		auto i = mDrum->isTouchOn(p);
		printf("%d\n", i);
		if(i != -1)
		{
			Res::Play(i);
			this->addParticle(p);
			return this;
		}
		if(mSetting->containPoint(p))
		{
			mSetting->onTouch();
			this->onSetting();
		}
		return this;
		
		/*
		 if(mSetting->containPoint(p))
		 {
		 MainScene::Get()->showSetting();
		 return;
		 }
		 if(mUpgrade->containPoint(p))
		 {
		 if(!Res::IsPro())
		 {
		 Res::SetPro();
		 MainScene::Get()->onProGot();
		 }
		 else
		 {
		 MainScene::Get()->showPop(Res::local.getText("version"));
		 }
		 return;
		 }
		 */
	}
	void onSetting();
};

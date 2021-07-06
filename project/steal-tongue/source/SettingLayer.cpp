	//
	//  SettingLayer.cpp
	//  drum-chinese
	//
	//  Created by lover on 2019/8/1.
	//  Copyright © 2019 lover. All rights reserved.
	//

#include "SettingLayer.hpp"
#include "MainScene.hpp"

static inline float _GSX(int index, int count)
{
	return Res::W()/2 - 256 + (index + 0.5f) * 512.f / count;
}

SettingLayer::SettingLayer()
{

	auto bg = new Sprite;
	bg->setPosition({0, 0});
	bg->setFixedSize({Res::W(), Res::H()});
	bg->setColor(eColor::Black);
	bg->setAlpha(0.3f);
	bg->setAnchor(0, 0);
	this->addNode(bg);

	int set_x[Res::sSettingCount] = {
		Res::sDefaultConfig.padStyle,
		Res::sDefaultConfig.voiceStyle,
		Res::sDefaultConfig.tongueStyle,
		Res::sDefaultConfig.drumStyle,
		Res::sDefaultConfig.themeStyle,
	};
	for(int i = 0; i < Res::sSettingCount; ++i)
	{
		auto pos = Point2{ Res::W()/2, 150.f + 128 * i };
		auto & src = Res::sSettings[i];
		
		auto sp = new Sprite;
		sp->setTexture(Textures::Get()->getTexture(src.image));
		sp->setPosition(pos);
		sp->setAnchor({0.5, 0.5});
		this->addNode(sp);

		auto se = new Sprite;
		se->setTexture(Textures::Get()->getTexture("img/setting_i.png"));
		se->setPosition(_GSX(set_x[i], src.options_count), pos.y);
		se->setAnchor({0.5, 0.5});
		se->setScale(4.f/src.options_count, 1);
		this->addNode(se);

		auto lb = new Label;
		lb->setFont(Res::GetTextFont());
		lb->setText(Res::local.getText(src.name));
		lb->setPosition(pos.x - 250, pos.y + 64);
		lb->setAnchor({0.5, 0.5});
		lb->setColor(Color(0x333333ff));
		lb->setFontSize(30);
		this->addNode(lb);

		mSettings.push_back(sp);
		mSelector.push_back(se);
	}

	mDrum = new Drum(true, true);
	mDrum->setPosition(Res::W()/2, 1100);
	mDrum->setScale(0.6);
	
					   this->addNode(mDrum)
;
	if(!Res::IsPro())
	{
		auto tips = new Label;
		tips->setText(Res::local.getText("no-save"));
		tips->setFontSize(32);
		tips->setFont(Res::GetTextFont());
		tips->setAnchor({0.5, 0.5f});
		tips->setPosition(Res::W()/2, 40);
		tips->setColor(Color(0x333333ff));
		this->addNode(tips);
		mTrialTips = tips;
	}

	auto name = new Label;
	name->setFontSize(45);
	name->setFont(Res::GetTextFont());
	name->setPosition(Res::W() - 10, Res::H() - 50);
	name->setRotation(-0.2);
	name->setAnchor({1, 0.5});
	name->setText(Res::local.getText("setting"));
	this->addNode(name);

	mBack = new Button;
	mBack->setText(Res::local.getText("back"));
	mBack->setPosition(84, Res::H() - 52);
	
		this->addNode(mBack);

	mCustom = new Button;
	mCustom->setText(Res::local.getText("custom"));
	mCustom->setPosition({512, 80});
	this->addNode(mCustom);

	mPlaying = new Sprite;
	mPlaying->setTexture(Textures::Get()->getTexture("img/playing.png"));
	mPlaying->setPosition(mDrum->getPosition());
	mPlaying->setAnchor({0.5, 0.5});
	mPlaying->setVisible(false);
	mPlaying->setAlpha(0.5f);
	this->addNode(mPlaying);

	this->moveCustomButton();
}

void SettingLayer::moveCustomButton()
{
	if(Res::sDefaultConfig.padStyle < 2)
	{
		mCustom->setVisible(false);
	}
	else
	{
		mCustom->setPosition(mSelector.front()->getPosition().x, 80);
		mCustom->setVisible(true);
	}
}

Node * SettingLayer::onTouchDown(AppTouch const & touch)
{
	auto tp = Point2{touch.x * Res::W(), touch.y * Res::H()};
	if(mBack->containPoint(tp))
	{
		Res::sMainScene->showMain(mIsChange);
		mIsChange = false;
		this->remove();
		return this;
	}
	if(Vector2Distance2(Vector2Make(mDrum->getPosition()), Vector2Make(tp)) < 230*230)
	{
		switchPlayDemo();
		return this;
	}
	if(Res::sDefaultConfig.padStyle >= 2 && mCustom->containPoint(tp))
	{
		Res::sMainScene->showCustom();
		this->remove();
		return this;
	}

	for(int i = 0; i < Res::sSettingCount; ++i)
	{
		auto sp = mSettings[i];
		if(Res::IsPointIn(tp, sp->getPosition(), sp->getContentSize()))
		{
			this->changeSetting(i, tp.x - (Res::W()/2 - 256));
			return this;
		}
	}
	return this;
}
void SettingLayer::changeSetting(int setting, float x)
{
	auto & src = Res::sSettings[setting];
	int index = x / (512 / src.options_count);
	if(index < 0 || index >= src.options_count) return;

	auto sr = mSelector[setting];
	sr->setPosition(_GSX(index, src.options_count), sr->getPosition().y);

	if(setting == 0) // pad
	{
		if(Res::sDefaultConfig.padStyle == index) return;

		Res::sDefaultConfig.padStyle = index;
		mDrum->resetPadStyle(index);
		this->moveCustomButton();
	}
	else if(setting == 1) // sounds
	{
		if(Res::sDefaultConfig.voiceStyle == index) return;
		Res::sDefaultConfig.voiceStyle = index;
		Res::PlayTune(0, index);
	}
	else if(setting == 2) //
	{
		if(Res::sDefaultConfig.tongueStyle == index) return;
		Res::sDefaultConfig.tongueStyle = index;
		mDrum->resetTongue(index);
	}
	else if(setting == 3)
	{
		if(Res::sDefaultConfig.drumStyle == index) return;
		Res::sDefaultConfig.drumStyle = index;
		mDrum->resetDrum(index);
	}
	else if(setting == 4)
	{
		if(Res::sDefaultConfig.themeStyle == index) return;
		Res::sDefaultConfig.themeStyle = index;
		Res::sMainScene->resetTheme();
	}
	mIsChange = true;

	Res::SaveConfig();
	if(Res::IsPro())
	{
		
	}
}

void SettingLayer::stopPlayDemo()
{
	if(mPlayingSchedule == nullptr) return;

	this->stopAction(mPlayingSchedule);
	mPlayingSchedule = nullptr;
	
	mPlaying->setVisible(false);
}

static int play_index = 0;
static const int demo_tunes_count = 8;
static const int demo_tunes[demo_tunes_count] = { 0, 1, 3, 4, 5, 7, 8, 10,};

void SettingLayer::switchPlayDemo()
{
	if(mPlayingSchedule)
	{
		stopPlayDemo();
		return;
	}

	play_index = 0;
	mPlaying->setVisible(true);
	mPlaying->setScale({1, 1});

	mPlayingSchedule = ActionCall::Create([this](float) {
		if(play_index >= demo_tunes_count)
		{
			this->stopPlayDemo();
			return false;
		}
		if(play_index%2)
		{
			mPlaying->setScale({2, 2});
		}
		else{
			mPlaying->setScale({1, 1});

		}
		Res::PlayTune(demo_tunes[play_index], Res::sDefaultConfig.voiceStyle);
		++play_index;
		return true;
	}, -1, 0, 0.5f);
}

void SettingLayer::refresh()
{
	mDrum->resetPadStyle(Res::sDefaultConfig.padStyle);
	mIsChange = true;
}

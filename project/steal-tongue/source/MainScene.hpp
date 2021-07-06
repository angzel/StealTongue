#pragma once

#include "Resource.hpp"
#include "SettingLayer.hpp"
#include "CustomLayer.hpp"
#include "LoadLayer.hpp"
#include "MainPlayer.hpp"
#include "PopLayer.hpp"

class MainScene : public Scene2d
{
	Sprite * mBG = nullptr;
	MainPlayer * mMain = nullptr;
public:
	MainScene()
	: Scene2d(Res::W(), Res::H())
	{
		Res::sMainScene = this;
		this->addNode(new LoadLayer([this]() {
			this->removeAllNodes();
			this->initMain();
		}));
	}
	void initMain()
	{
		mBG = new Sprite;
		mBG->setFixedSize({Res::W(), Res::H()});
		this->addNode(mBG);
		this->addNode(mMain = new MainPlayer);
		resetTheme();
	}
	
	void resetTheme()
	{
		mBG->setTexture(Res::GetMainBG(Res::sDefaultConfig.themeStyle));
	}
	void showSetting(bool refresh = false)
	{
		auto s = new SettingLayer;
		this->addNode(s);
		
		mMain->setVisible(false);
	}

	void showCustom()
	{
		auto c = new CustomLayer;
		this->addNode(c);
	}

	void showMain(bool refresh = false)
	{
		mMain->setVisible(true);
		if(refresh) mMain->refresh();
	}
	void showPop(std::string const & s)
	{
		auto p = new PopLayer(s);
//		mPopLayer->addTo(mRoot);
		this->addNode(p);
	}
	void onProGot()
	{
//		mMainPlayer->onPro();
//		mSettingLayer->onPro();
	}
};

class MainDelegate : public Zen::Vap::RootDelegate
{
public:
	virtual void onLaunch() override
	{
		Zen::App::Get()->setFramesPerSecond(20);
		Zen::App::Get()->setRotatable(false);
		Zen::App::Get()->setMultiTouch(true);
		auto real = Root::Get()->getRealViewSize();
		auto ratio = real.w / real.h;
		float w = 900;
		float h = 1600;

		if(ratio < 9/16.f) w = h * ratio;
		else h = w / ratio;
		
		Res::SetViewSize(w, h);
		Res::LoadResource();
		Res::LoadConfig();
		
//		AudioPlayer::Get()->

		Root::Get()->replaceRootNode(new MainScene);
		Zen::LogV("%s ok", __func__);
	}
};

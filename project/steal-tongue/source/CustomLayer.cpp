//
//  CustomLayer.cpp
//  drum-chinese
//
//  Created by lover on 2019/8/1.
//  Copyright © 2019 lover. All rights reserved.
//

#include "CustomLayer.hpp"
#include "MainScene.hpp"

static const int KeysPerRow = 6;
static const int KeysRow = 3;

CustomLayer::CustomLayer()
{
	//	auto bg = Rectangle::Create();
	//	bg->setPosition({0, 0});
	//	bg->setSize(Pt2(Res::W(), Res::H()));
	//	bg->setMaskColor(EColor::Black);
	//	bg->setAlpha(0.4f);
	//	mView->addChild(bg);
	
	float h = Res::H() * 0.6;
	
	mDrum = new Drum(true, false);
	mDrum->setScale(h/1100);
	mDrum->setPosition(Res::W()/2, h/2 + 50);
	
	this->addNode(mDrum);
	
	auto pad = new Sprite;
	pad->setTexture(Textures::Get()->getTexture("img/keys-bg.png"));
	pad->setPosition(Res::W()/2, (Res::H() + h)/2);
	pad->setAnchor({0.5, 0.5});
	this->addNode(pad);
	auto size = pad->getContentSize();
	auto pos = pad->getPosition();
	mKeysArea = pad;
	
	mKeyDiss = {size.w / KeysPerRow, size.h / KeysRow};
	mKeyPos0 = { pos.x - mKeyDiss.x*2.5f, pos.y - mKeyDiss.y };
	
	mSelector =  new Sprite;
	mSelector->setTexture(Textures::Get()->getTexture("img/key-select.png"));
	mSelector->setPosition(pad->getPosition());
	mSelector->setAnchor({0.5, 0.5});
	this->addNode(mSelector);
	
	this->selectKey(-1);
	
	for(int i = 0; i < Res::sAudioCount; ++i)
	{
		//		auto src = Res::sAudios[i];
		auto name = Res::GetTuneName(i);
		
		auto text = new Label;
		text->setFont(Res::GetTuneNameFont());
		text->setFontSize(30);
		text->setLinesSpacingInPixels(-15);
		text->setTextAlignment(0.5f);
		text->setText(name);
		text->setPosition(mKeyPos0.x + mKeyDiss.x * (i%KeysPerRow), mKeyPos0.y + mKeyDiss.y * (i/KeysPerRow));
		text->setAnchor({0.5, 0.5});
		text->setColor(eColor::Black);
		this->addNode(text);
	}
	
	mOK = new Button;
	mOK->setText(Res::local.getText("ok"));
	mOK->setPosition(84, Res::H() - 52);
	this->addNode(mOK);
	
	auto name = new Label;
	name->setFontSize(45);
	name->setFont(Res::GetTextFont());
	name->setPosition(Res::W() - 10, Res::H() - 50);
	name->setRotation(-0.2);
	name->setAnchor({1, 0.5});
	name->setText(Res::local.getText("custom"));
	this->addNode(name);
	auto tips = new Label;
	tips->setText(Res::local.getText("custom-help"));
	tips->setFontSize(32);
	tips->setFont(Res::GetTextFont());
	tips->setAnchor({0.5, 0.5f});
	tips->setPosition(Res::W()/2, 40);
	tips->setColor(Color(0x333333ff));
	this->addNode(tips);
	
}

void CustomLayer::selectKey(int index)
{
	mSelectedKeyIndex = index;
	if(index == -1)
	{
		mSelector->setVisible(false);
	}
	else
	{
		if(mSelectedKeyIndex < Res::sAudioCount)
		{
			Res::PlayTune(mSelectedKeyIndex, Res::sDefaultConfig.voiceStyle);
		}
		mSelector->setVisible(true);
	}
}
void CustomLayer::resetPad()
{
	mDrum->resetTongue(Res::sDefaultConfig.tongueStyle);
	mDrum->resetDrum(Res::sDefaultConfig.drumStyle);
	mDrum->resetPadStyle(Res::sDefaultConfig.padStyle);
}

Node* CustomLayer::onTouchDown(AppTouch const & touch)
{
	auto pt = Point2{touch.x * Res::W(), touch.y * Res::H()};
	
	if(mOK->containPoint(pt))
	{
		if(mIsChange) Res::SaveCustomKeys();
		
		mIsChange = false;

		Res::sMainScene->showSetting();
		this->remove();
		return nullptr;
	}
	if(Res::IsPointIn(pt, mKeysArea->getPosition(), mKeysArea->getContentSize()))
	{
		auto xi = (pt.x - mKeyPos0.x + mKeyDiss.x / 2) / mKeyDiss.x;
		auto yi = (pt.y - mKeyPos0.y + mKeyDiss.y / 2) / mKeyDiss.y;
		auto i = (int)yi * KeysPerRow + (int)xi;
		
		mSelector->setPosition(mKeyPos0.x + mKeyDiss.x * (int)xi, mKeyPos0.y + mKeyDiss.y * (int)yi);
		this->selectKey(i);
		return this;
	}
	if(mSelectedKeyIndex == -1) return this;
	
	auto index = mDrum->isTouchOn(pt);
	if(index == -1) return this;
	
	Res::SetCustomKey(index, mSelectedKeyIndex);
	mDrum->refreshName(index);
	if(mSelectedKeyIndex < Res::sAudioCount)
	{
		Res::PlayTune(mSelectedKeyIndex, Res::sDefaultConfig.voiceStyle);
		this->selectKey(-1);
	}
	mIsChange = true;
	return this;
}

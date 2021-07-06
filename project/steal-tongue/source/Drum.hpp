#pragma once

#include "Resource.hpp"

class Drum : public Layer
{
protected:
	std::vector<Sprite*> mTongues;
	Sprite * mDrum;
	Layer * mTonguesView;
	std::vector<Label*> mTuneNames;
	int mDrumStyle = 0;
	int mTongueStyle = 0;
	int mPadStyle = 0;
	bool mHasTuneName = false;
	bool mHideNoname = false;
public:
	Drum(bool show_tune_name, bool hide_noname)
	{
		mHasTuneName = show_tune_name;
		mHideNoname = hide_noname;

		mDrumStyle = Res::sDefaultConfig.drumStyle;
		mTongueStyle = Res::sDefaultConfig.tongueStyle;
		mPadStyle = Res::sDefaultConfig.padStyle;

		mDrum = new Sprite;
		mDrum->setTexture(Res::GetDrumBG(mDrumStyle));
		mDrum->setPosition({0, 0});
		mDrum->setAnchor({0.5, 0.5});
		mDrum->setScale({1.f, 1.f});
		this->addNode(mDrum);

		mTonguesView = new Layer;
		this->addNode(mTonguesView); //->addChild(mTonguesView);

		_resetTongues();
		if(mHasTuneName) refreshNames();

	}
	void resetDrum(int index)
	{
		if(index == mDrumStyle) return;
		mDrumStyle = index;
		mDrum->setTexture(Res::GetDrumBG(mDrumStyle));
	}
	void resetTongue(int index)
	{
		if(index == mTongueStyle) return;
		mTongueStyle = index;
		for(auto i : mTongues)
		{
			i->setTexture(Res::GetTongueImage(mTongueStyle));
		}
	}
	void resetPadStyle(int index)
	{
		if(mPadStyle == index && index < 2) return;
		mPadStyle = index;
		_resetTongues();
		if(mHasTuneName) refreshNames();

	}
	void _resetTongues()
	{
		int count = Res::GetKeyCount(mPadStyle);
		if(mTongues.size() == count) return;

		float dis = 380;
		Color color(40, 40, 40, 0xff);
		color.setGrey(0xff);

		mTonguesView->removeAllNodes();
		mTongues.clear();
		if(mHasTuneName) mTuneNames.clear();

		if(count == 9)
		{
			float scale = 1.1f;
			float d = dis * 0.9f;
			for(int i = 0; i < 9; ++i)
			{
				auto s = new Sprite;
				s->setTexture(Res::GetTongueImage(mTongueStyle));
				float rad = ZEN_F_PI4 * i - ZEN_F_PI;
				s->setRotation(rad);
				float rada = rad + ZEN_F_PI2;
				float x = d * cos(rada);
				float y = d * sin(rada);
				s->setPosition(x, y);
				s->setAnchor({0.5, 0.5});
				s->setScale(scale, scale);
				s->setColor(color);

				mTonguesView->addNode(s);
				mTongues.push_back(s);
			}
			auto s = mTongues.back();
			s->setPosition({0, 0});
			scale *= 1.1f;
			s->setScale(scale, scale);
		}
		else
		{
			float er = ZEN_F_PI / 6;
			float scale = 0.9f;
			float d1 = dis;
			float d2 = dis * 0.8f;
			for(int i = 0; i < 13; ++i)
			{
				auto s = new Sprite;
				s->setTexture(Res::GetTongueImage(mTongueStyle));
				float rad = er * i - ZEN_F_PI;
				s->setRotation(rad);
				float rada = rad + ZEN_F_PI2;
				float d = (i % 2)?d2:d1;
				float x = d * cos(rada);
				float y = d * sin(rada);
				s->setAnchor({0.5, 0.5});
				s->setPosition(x, y);
				mTonguesView->addNode(s);
				mTongues.push_back(s);
				s->setColor(color);
				s->setScale(scale, scale);

			}
			auto s = mTongues.back();
			s->setPosition({0, 0});
			scale *= 1.1f;
			s->setScale(scale, scale);
		}
		if(mHasTuneName)
		{
			for(size_t i = 0; i < mTongues.size(); ++i)
			{
				auto ton = mTongues[i];
				
				auto name = new Label;
				name->setFont(Res::GetTuneNameFont());
				name->setFontSize(30);
				name->setPosition(ton->getPosition());
				name->setColor(Zen::Color(0x444444ff));
				name->setAnchor(ton->getAnchor());
				name->setTextAlignment(0.5f);
				name->setLinesSpacingInPixels(-15);
				mTonguesView->addNode(name);
				mTuneNames.push_back(name);
			}
		}
	}
	void refreshName(int index)
	{
		auto name_node = mTuneNames[index];
		auto tune = Res::GetTuneIndex((int)index, mPadStyle);
		name_node->setText(Res::GetTuneName(tune));
	}
	void refreshNames()
	{
		if(!mHasTuneName) return;
		
		for(size_t i = 0; i < mTuneNames.size(); ++i)
		{
			auto name_node = mTuneNames[i];
			auto tune = Res::GetTuneIndex((int)i, mPadStyle);
			if(tune == -1)
			{
				if(mHideNoname)
				{
					name_node->setVisible(false);
					mTongues[i]->setVisible(false);
				}
				else
				{
					name_node->setText("");
				}
			}
			else
			{
				name_node->setText(Res::GetTuneName(tune));
				name_node->setVisible(true);
				mTongues[i]->setVisible(true);
			}
		}
	}
	void setScale(float s)
	{
		View2d::setScale(s, s);
	}
	int isTouchOn(Point2 touch)
	{
		auto mp = this->getPosition();
		auto s = this->getScale();
		auto p = Vector2Make((touch.x - mp.x) / s.x, (touch.y - mp.y) / s.y);
		float dis = (mTongues.size() == 8 ? 130.f : 100.f);
		for(size_t i = 0; i < mTongues.size(); ++i)
		{
			auto ip = mTongues[i]->getPosition();
			if(Vector2Distance(Vector2Make(ip), p) < dis)
			{
				touchAction(i);
				return (int)i;
			}
		}
		return -1;
	}
	
	void touchAction(size_t i)
	{
		mTongues[i]->stopAllActions();
		mTongues[i]->setAlpha(1.f);
		mTongues[i]->runAction(ActionCall::Create([this, i](float) {
			auto a = mTongues[i]->getAlpha();
			mTongues[i]->setAlpha(a>0.99f?0.5f:1.f);
			return true;
		}, 6, 0, 0.05f));
	}
	
};

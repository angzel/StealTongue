//
//  MainPlayer.cpp
//  drum-chinese
//
//  Created by lover on 2019/7/31.
//  Copyright © 2019 lover. All rights reserved.
//

#include "MainPlayer.hpp"
#include "MainScene.hpp"

void MainPlayer::refresh()
{
	mDrum->resetPadStyle(Res::sDefaultConfig.padStyle);
	mDrum->resetTongue(Res::sDefaultConfig.tongueStyle);
	mDrum->resetDrum(Res::sDefaultConfig.drumStyle);
}
void MainPlayer::onSetting()
{
	Res::sMainScene->showSetting();
}
void MainPlayer::addParticle(Point2 pos)
{
	auto p = new ParticleGravity;
	p->setTexture(Textures::Get()->getParticleTexture());
	
	p->setPosition(pos.x, pos.y);
	p->setParticleStartColors(Zen::eColor::White);
	p->setParticleStartSize(10);
	p->setParticleStartSizeVarying(10);
	p->setParticleEndSize(0);
	p->setParticleEndSizeVarying(3);
	p->setParticleGravityValue(0);
	p->setParticleEmitSpeed(450);
	p->setParticleEmitDirectVarying(ZEN_F_PI);
	p->setParticleLife(0.5);
	p->setParticleLifeVarying(0.25);
	//		p->setOrder(10);
	p->setEmitterLife(0.f);
	p->start();
	this->addNode(p);
	
	auto call = ActionCall::Create([p](float){
		p->remove();
		return true;
	}, 1, 2.f);
	p->runAction(call);
}

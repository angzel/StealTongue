	//
	//  delegate.cpp
	//  application_test
	//
	//  Created by lover on 2019/7/18.
	//  Copyright © 2019 lex.sdk. All rights reserved.
	//

#include "MainScene.hpp"
#include "zen_app.h"

int ZenAppMain(int argc, const char ** argv)
{
	Zen::LogV("%s", __FUNCTION__ );
	auto root = Zen::Vap::Root::Get();
	Zen::LogV("%s", __FUNCTION__ );

	root->run(std::shared_ptr<RootDelegate>(new MainDelegate));
	Zen::LogV("%s1", __FUNCTION__ );

	Zen::App::Get()->setRotatable(true);
	Zen::LogV("%s2", __FUNCTION__ );

	Zen::App::Get()->setBGUpdate(true);
	return 0;
}

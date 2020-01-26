#pragma once
#include "App.h"

class Title : public App::Scene
{
public:
	Title(const InitData& initData) :
		IScene(initData),
		menuCursor(0),
		seSelect(U"./assets/select.mp3"),
		hakaseTexture(U"./assets/hakase-mini.png"),
		titleFont(120)
	{
		int32 boxWidth = 0;

		menuBoxes.resize(menuTexts.size());

		for (const auto& text : menuTexts) {
			boxWidth = Max(boxWidth, FontAsset(U"Menu")(text).region().w);
		}

		for (int i = 0; i < menuBoxes.size(); ++i) {
			menuBoxes[i].set(
				Window::ClientWidth() * 1 / 8,
				(Window::ClientHeight() - menuBoxes.size() * 80) / 2 + i * 80,
				boxWidth + 80,
				60
			);
		}

		Scene::SetBackground(Color(255, 255, 255));
	}

	void update() override
	{
		if (KeyUp.down()) {
			menuCursor = (menuCursor - 1 + menuBoxes.size()) % menuBoxes.size();
			seSelect.playOneShot();
		}
		else if(KeyDown.down()) {
			menuCursor = (menuCursor + 1) % menuBoxes.size();
			seSelect.playOneShot();
		}

		if (KeyEnter.down()) {
			switch (menuCursor) {
			case 0:
				getData().mode = GameInfo::GameMode::Time;
				changeScene(U"Game");
				break;
			case 1:
				getData().mode = GameInfo::GameMode::ManyShot;
				changeScene(U"Game");
				break;
			case 2:
				getData().mode = GameInfo::GameMode::OneShot;
				changeScene(U"Game");
				break;
			case 3:
				changeScene(U"Ranking");
				break;
			case 4:
				System::Exit();
				break;
			}
		}
	}

	void draw() const override
	{
		for (auto i : step(menuBoxes.size())) {
			if (i == menuCursor) {
				const int vx = 40;
				menuBoxes[i].movedBy(vx, 0).shearedX(20).draw(Color(128, 191, 63));
				FontAsset(U"Menu")(menuTexts[i]).drawAt(
					menuBoxes[i].center().x + vx,
					menuBoxes[i].center().y,
					Color(40)
				);
			}
			else {
				menuBoxes[i].shearedX(20).draw();
				FontAsset(U"Menu")(menuTexts[i]).drawAt(menuBoxes[i].center(), Color(40));
			}
		}

		// Under Label
		Rect(
			0,
			Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT,
			Window::ClientWidth(),
			GameInfo::BOTTOM_LABEL_HEIGHT
		).draw(Color(84, 103, 122));

		// Title
		{
			const Rect titleFontRegion = titleFont(GameInfo::TITLE).region();
			titleFont(GameInfo::TITLE).draw(
				(Window::ClientWidth() - titleFontRegion.w) / 2,
				(Window::ClientHeight() - titleFontRegion.h) / 2,
				Color(40)
			);
		}

		// Hakase
		hakaseTexture.draw(
			Window::ClientWidth() * 9 / 10 - hakaseTexture.width(),
			Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT - hakaseTexture.height()
		);
	}
private:
	int menuCursor;
	Array<Rect> menuBoxes;
	Array<String> menuTexts = {
		/*
		GameInfo::MENU_SINGLE_PLAY,
		GameInfo::MENU_MULTI_PLAY,
		GameInfo::MENU_SCORE,
		*/
		GameInfo::MENU_TIME,
		GameInfo::MENU_MANY_SHOT,
		GameInfo::MENU_ONE_SHOT,
		GameInfo::MENU_RANKING,
		GameInfo::MENU_EXIT,
	};
	Audio seSelect;
	Texture hakaseTexture;
	Font titleFont;
};

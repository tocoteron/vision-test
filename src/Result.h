#pragma once
#include "App.h"

#include "ScoreManager.h"

class Result : public App::Scene
{
public:
	Result(const InitData& initData) :
		IScene(initData),
		time(0),
		nowScore(0),
		lastScore(getData().lastScore),
		font(60),
		scoreFont(240),
		seDrum(U"./assets/se_drum.mp3"),
		seYeah(U"./assets/se_yeah.mp3"),
		hasPlayedSeDrum(false),
		hasPlayedSeYeah(false)
	{
		ScoreManager::save(lastScore);
		Scene::SetBackground(Color(255, 255, 255));
	}

	void update() override
	{
		if (nowScore < lastScore) {
			nowScore = std::min(
				nowScore + lastScore / (2 * GameInfo::FPS),
				lastScore
			);
		}

		if (time == 0) {
			seDrum.playOneShot();
			hasPlayedSeDrum = true;
		}

		if (time > (seDrum.lengthSec() - 0.4) * GameInfo::FPS && !hasPlayedSeYeah) {
			seYeah.playOneShot();
			hasPlayedSeYeah = true;
		}
		
		if (time > (seDrum.lengthSec() + seYeah.lengthSec() + 1) * GameInfo::FPS && hasPlayedSeYeah) {
			changeScene(U"Title");
		}

		++time;
	}

	void draw() const override
	{
		const Rect fontRegion = font(U"スコア").region();
		const Rect scoreFontRegion = scoreFont(nowScore).region();

		font(U"スコア").draw(
			(Window::ClientWidth() - fontRegion.w) / 2,
			(Window::ClientHeight() - scoreFontRegion.h) / 2 - fontRegion.h - 10,
			Color(40)
		);

		scoreFont(nowScore).draw(
			(Window::ClientWidth() - scoreFontRegion.w) / 2,
			(Window::ClientHeight() - scoreFontRegion.h) / 2,
			Color(40)
		);

		// Under Label
		Rect(
			0,
			Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT,
			Window::ClientWidth(),
			GameInfo::BOTTOM_LABEL_HEIGHT
		).draw(Color(84, 103, 122));
	}

	void saveScore()
	{

	}
private:
	int time;
	int nowScore;
	int lastScore;
	Font font;
	Font scoreFont;
	Font desciptionFont;
	Audio seDrum;
	Audio seYeah;
	bool hasPlayedSeDrum;
	bool hasPlayedSeYeah;
};

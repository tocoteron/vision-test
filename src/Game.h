#pragma once
#include "App.h"

#include "TestCircle.h"
#include "HandButton.h"
#include "EffectTexture.h"

#include <algorithm>

class Game : public App::Scene
{
public:
	Game(const InitData& initData) :
		IScene(initData),
		mode(getData().mode),
		score(0),
		successChain(0),
		failureChain(0),
		remainingTimeForTimeMode(30 * GameInfo::FPS),
		remainingCountForManyShotMode(mode == GameInfo::GameMode::ManyShot ? 30 : 1),
		remainingFailureForOneShotMode(1),
		hasClear(true),
		seSuccess(U"./assets/answer.mp3"),
		seFailure(U"./assets/wrong.mp3"),
		womanTexture(U"./assets/woman-mini.png"),
		font(30),
		scoreFont(60)
	{
		// Buttons
		{
			const int buttonSize = 100;
			const int buttonMarginX = 10;
			const int buttonSizeWithMarginX = buttonSize + buttonMarginX * 2;
			const int buttonBaseX = Window::ClientWidth() * 2 / 5 - (buttonSize * 2 + buttonMarginX * 3);
			const int buttonY = Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT + (GameInfo::BOTTOM_LABEL_HEIGHT - buttonSize) / 2;

			buttons.push_back(HandButton(KeyLeft, HandButton::HandType::LEFT, buttonBaseX + buttonSizeWithMarginX * 0, buttonY, buttonSize));
			buttons.push_back(HandButton(KeyRight, HandButton::HandType::RIGHT, buttonBaseX + buttonSizeWithMarginX * 1, buttonY, buttonSize));
			buttons.push_back(HandButton(KeyUp, HandButton::HandType::TOP, buttonBaseX + buttonSizeWithMarginX * 2, buttonY, buttonSize));
			buttons.push_back(HandButton(KeyDown, HandButton::HandType::BOTTOM, buttonBaseX + buttonSizeWithMarginX * 3, buttonY, buttonSize));
		}

		directionKeys.push_back(KeyLeft);
		directionKeys.push_back(KeyRight);
		directionKeys.push_back(KeyUp);
		directionKeys.push_back(KeyDown);

		successEffects.push_back(Texture(U"./assets/answer_effect_0-mini.png"));

		failureEffects.push_back(Texture(U"./assets/wrong_effect_0-mini.png"));
		failureEffects.push_back(Texture(U"./assets/wrong_effect_1-mini.png"));
		failureEffects.push_back(Texture(U"./assets/wrong_effect_2-mini.png"));
		failureEffects.push_back(Texture(U"./assets/wrong_effect_3-mini.png"));

		//Window::SetTitle(U"VISION TEST");
		Scene::SetBackground(Color(255, 255, 255));
	}

	void update() override
	{
		if (KeyEscape.down()) {
			changeScene(U"Title");
		}

		switch (mode) {
		case GameInfo::GameMode::Time:
			if (remainingTimeForTimeMode < 0) {
				getData().lastScore = score;
				changeScene(U"Result");
			}
			break;
		case GameInfo::GameMode::ManyShot:
			if (remainingCountForManyShotMode <= 0) {
				getData().lastScore = score;
				changeScene(U"Result");
			}
			break;
		case GameInfo::GameMode::OneShot:
			if (remainingFailureForOneShotMode <= 0) {
				getData().lastScore = score;
				changeScene(U"Result");
			}
			break;
		}

		if (hasClear) {
			testCircle = TestCircle::getRandomTestCircle(
				Window::ClientWidth() * 2 / 5,
				(Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT) / 2
			);
			remainingTime = MAX_RAMAINING_TIME * GameInfo::FPS;
			--remainingCountForManyShotMode;
			hasClear = false;
		}

		if (remainingTime < 0) {
			failure();
		}

		if (womanEffectTexture && womanEffectTexture->isEnd()) {
			womanEffectTexture.reset();
		}

		for(auto button : buttons) {
			if (button.leftClicked()) {
				if (judge(button, testCircle)) {
					success();
				}
				else {
					failure();
					--remainingFailureForOneShotMode;
				}
			}
		}

		--remainingTime;
		--remainingTimeForTimeMode;
	}

	void draw() const override
	{
		testCircle.draw();

		// Under Label
		Rect(
			0,
			Window::ClientHeight() - GameInfo::BOTTOM_LABEL_HEIGHT,
			Window::ClientWidth(),
			GameInfo::BOTTOM_LABEL_HEIGHT
		).draw(Color(84, 103, 122));

		// Label Position
		const int labelY = buttons[0].getY();
		const int rightButtonsX = buttons.back().getX() + buttons.back().getSize();

		// Time Label
		{
			font(U"時間").draw(
				rightButtonsX + 40,
				labelY,
				Color(255, 255, 255)
			);
			scoreFont((remainingTime + (GameInfo::FPS - 1)) / GameInfo::FPS).draw(
				rightButtonsX + 60,
				labelY + 30,
				Color(
					255,
					255 * (double)remainingTime / (MAX_RAMAINING_TIME * GameInfo::FPS),
					255 * (double)remainingTime / (MAX_RAMAINING_TIME * GameInfo::FPS)
				)
			);
		}

		// Score Label
		{
			font(U"スコア").draw(
				rightButtonsX + 200,
				labelY,
				Color(255, 255, 255)
			);
			scoreFont(score).draw(
				rightButtonsX + 220,
				labelY + 30,
				Color(255, 255, 255)
			);
		}

		// Rule Label
		{
			const int ruleLabelX = rightButtonsX + 500;

			switch (mode) {
			case GameInfo::GameMode::Time:
				font(U"残り時間").draw(
					ruleLabelX,
					labelY,
					Color(255, 255, 255)
				);
				scoreFont(remainingTimeForTimeMode / GameInfo::FPS).draw(
					ruleLabelX + 20,
					labelY + 30,
					Color(255, 255, 255)
				);
				break;
			case GameInfo::GameMode::ManyShot:
				font(U"残り回数").draw(
					ruleLabelX,
					labelY,
					Color(255, 255, 255)
				);
				scoreFont(remainingCountForManyShotMode).draw(
					ruleLabelX + 20,
					labelY + 30,
					Color(255, 255, 255)
				);
				break;
			case GameInfo::GameMode::OneShot:
				font(U"一発勝負！").draw(
					ruleLabelX,
					labelY + GameInfo::BOTTOM_LABEL_HEIGHT / 5,
					Color(255, 31, 31)
				);
				break;
			}
		}

		// Woman
		{
			const int womanX = Window::ClientWidth() - womanTexture.width() - GameInfo::BOTTOM_LABEL_HEIGHT;
			const int womanY = Window::ClientHeight() - womanTexture.height() - GameInfo::BOTTOM_LABEL_HEIGHT;

			womanTexture.draw(womanX, womanY);

			if (womanEffectTexture) {
				womanEffectTexture->draw(
					womanX + womanTexture.width() * 3 / 5,
					womanY - womanTexture.height() / 6
				);
			}
		}

		// Buttons
		for (auto button : buttons) {
			button.draw();
		}
	}

	void success()
	{
		// Performances
		seSuccess.playOneShot();

		womanEffectTexture.reset(new EffectTexture(
			successEffects[std::min((size_t)successChain, successEffects.size() - 1)],
			GameInfo::FPS * 0.5
		));

		// Calc
		++successChain;
		failureChain = 0;
		score = std::min(MAX_SCORE, score + calcScore(successChain));
		hasClear = true;
	}

	void failure()
	{
		//Performances
		seFailure.playOneShot();

		womanEffectTexture.reset(new EffectTexture(
			failureEffects[std::min((size_t)failureChain, failureEffects.size() - 1)],
			GameInfo::FPS * 0.5
		));

		// Calc
		successChain = 0;
		++failureChain;
		score = std::max(0, score - calcScore(failureChain));
		hasClear = true;
	}

	bool judge(HandButton &button, TestCircle &circle)
	{
		HandButton::HandType handType = button.getHandType();
		TestCircle::HolePos holePos = circle.getHolePos();

        return (handType == HandButton::HandType::LEFT && holePos == TestCircle::HolePos::LEFT)
            || (handType == HandButton::HandType::RIGHT && holePos == TestCircle::HolePos::RIGHT)
            || (handType == HandButton::HandType::TOP && holePos == TestCircle::HolePos::TOP)
            || (handType == HandButton::HandType::BOTTOM && holePos == TestCircle::HolePos::BOTTOM);
	}

	int calcScore(int chain)
	{
		static const int base_score = 10;
		int difficulty = 9 - TestCircle::sizeToIndex(testCircle.getSize());

		return static_cast<double>(remainingTime) / (GameInfo::FPS * MAX_RAMAINING_TIME) * chain * base_score * difficulty;
	}
private:
	GameInfo::GameMode mode;
	int score;
	unsigned int successChain;
	unsigned int failureChain;
	int remainingTime = 0; // Frame base
	int remainingTimeForTimeMode;
	int remainingCountForManyShotMode;
	int remainingFailureForOneShotMode;
	bool hasClear;
	TestCircle testCircle;
	std::vector<HandButton> buttons;
	std::vector<s3d::Key> directionKeys;
	Audio seSuccess;
	Audio seFailure;
	Texture womanTexture;
	std::vector<Texture> successEffects;
	std::vector<Texture> failureEffects;
	std::unique_ptr<EffectTexture> womanEffectTexture;
	Font font;
	Font scoreFont;
	const int MAX_SCORE = 999999;
	const int MAX_RAMAINING_TIME = 5; // Second base
};

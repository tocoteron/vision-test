#pragma once
#include <Siv3D.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

class HandButton
{
public:
	enum class HandType
	{
		LEFT,	
		RIGHT,
		TOP,
		BOTTOM	
	};

	HandButton(s3d::Key shortcutKey, HandType handType, int x, int y, int size) :
		shortcutKey(shortcutKey),
		handType(handType),
		texture(Emoji(U"👆"), TextureDesc::Mipped),
		rect(x, y, size, size, size / 5),
		backRect(x, y + size / 6, size, size, size / 5)
	{}

	void draw() const
	{
		int my;

		if (!leftPressed()) {
			backRect.draw(Color(0, 191, 63));
			rect.draw(Color(128, 191, 63));
			my = 0;
		}
		else {
			backRect.draw(Color(0, 151, 23));
			my = rect.h / 6;
		}

		switch (handType) {
		case HandType::LEFT:
			texture
				.resized(rect.w * 4 / 5)
				.rotated(M_PI * 3.0 / 2.0)
				.draw(rect.x + rect.w / 10, rect.y + rect.h / 10 + my);
			break;
		case HandType::RIGHT:
			texture
				.resized(rect.w * 4 / 5)
				.rotated(M_PI * 1.0 / 2.0)
				.draw(rect.x + rect.w / 10, rect.y + rect.h / 10 + my);
			break;
		case HandType::TOP:
			texture
				.resized(rect.w * 4 / 5)
				.rotated(M_PI * 0.0 / 2.0)
				.draw(rect.x + rect.w / 10, rect.y + rect.h / 10 + my);
			break;
		case HandType::BOTTOM:
			texture
				.resized(rect.w * 4 / 5)
				.rotated(M_PI * 2.0 / 2.0)
				.draw(rect.x + rect.w / 10, rect.y + rect.h / 10 + my);
			break;
		}
	}

	HandType getHandType()
	{
		return handType;
	}

	int getX() const
	{
		return rect.x;
	}

	int getY() const
	{
		return rect.y;
	}

	int getSize() const
	{
		return rect.w;
	}

	bool leftClicked() const
	{
		return rect.leftClicked() || shortcutKey.down();
	}

	bool leftPressed() const
	{
		return rect.leftPressed() || shortcutKey.pressed();
	}

	bool leftReleased() const
	{
		return rect.leftReleased() || shortcutKey.up();
	}

private:
	HandType handType;
	Texture texture;
	RoundRect rect;
	RoundRect backRect;
	s3d::Key shortcutKey;
};
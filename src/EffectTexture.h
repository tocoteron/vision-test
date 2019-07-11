#pragma once
#include <Siv3D.hpp>

class EffectTexture
{
public:
	EffectTexture() {};

	EffectTexture(Texture texture, int time) :
		texture(texture),
		time(time)
	{};

	void draw(int x, int y)
	{
		--time;
		texture.draw(x, y);
	}

	bool isEnd()
	{
		return time <= 0;
	}
private:
	Texture texture;
	int time;
};
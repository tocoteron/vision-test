#pragma once
#include "App.h"

struct Score
{
	Date date;
	String name;
	int32 score;

	Score(Date date, String name, int32 score) :
		date(date),
		name(name),
		score(score)
	{}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(date, name, score);
	}
};
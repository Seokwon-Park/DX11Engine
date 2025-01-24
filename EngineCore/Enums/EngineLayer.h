#pragma once

enum class ESortingLayer
{
	BackgroundTilemap = -10,
	GroundTilemap = -5,
	Default = 0,
	UI = 1000,
};

enum ECollisionLayer
{
	Player = 0x00000001,
	Enemy = 0x00000002,
	Ground = 0x00000004,
};


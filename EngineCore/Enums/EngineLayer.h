#pragma once

enum class ESortingLayer
{
	Default = 0,
	UI = 1000,
};

enum ECollisionLayer
{
	Player = 0x00000001,
	Enemy = 0x00000002,
	UI = 0x00000004,
};
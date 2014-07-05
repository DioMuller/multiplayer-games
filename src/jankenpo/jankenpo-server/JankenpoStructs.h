#pragma once

enum RPSValue
{
	ROCK = 1,
	PAPER = 2,
	SCISSORS = 3
};

enum DuelResult
{
	WIN = 1,
	LOSE = 2,
	DRAW = 3
};

enum MessageType
{
	MESSAGE_AUTH_REQUEST,
	MESSAGE_AUTH_RESPONSE
};

struct MessageHeader
{
	MessageType type;
};

struct MessageAuthRequest
{
	MessageHeader header;
	RPSValue value;
};

struct MessageAuthResponse
{
	MessageHeader header;
	bool winner;
};
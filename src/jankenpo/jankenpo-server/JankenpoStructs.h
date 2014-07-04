#pragma once

enum RPSValue
{
	ROCK,
	PAPER,
	SCISSORS
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
#pragma once

#define MESSAGE_SIZE 512

enum RPSValue
{
	NONE = -1,
	ROCK = 0,
	PAPER = 1,
	SCISSORS = 2
};

enum DuelResult
{
	WIN = 1,
	LOSE = 2,
	DRAW = 3
};

enum MessageType
{
	MESSAGE_RPS_CONNECT = 0,
	MESSAGE_RPS_REQUEST = 1,
	MESSAGE_RPS_PLAY = 2,
	MESSAGE_RPS_RESULT = 3
};

struct MessageRPSConnect
{
	MessageType type = MessageType::MESSAGE_RPS_CONNECT;
};

struct MessageRPSRequest
{
	MessageType type = MessageType::MESSAGE_RPS_REQUEST;
};

struct MessageRPSPlay
{
	MessageType type = MessageType::MESSAGE_RPS_PLAY;
	RPSValue value;
};

struct MessageRPSResult
{
	MessageType type = MessageType::MESSAGE_RPS_RESULT;
	DuelResult winner;
};
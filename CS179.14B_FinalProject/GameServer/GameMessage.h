#pragma once
#include <cstdlib>
#include <cstdint>

typedef uint32_t ID;

enum class MessageType : uint8_t {
	Connect = 0, Disconnect = 1, Reconnect = 2, Position = 3, Ping = 4, Pong = 5
};


#pragma pack(push, 1)
struct Message {
	MessageType type;
	uint16_t size;
	uint8_t data[];
};

struct Position {
	float x, y;
};

struct PositionMessage {
	ID id;
	uint32_t order;
	Position pos;
};
#pragma pack(pop)

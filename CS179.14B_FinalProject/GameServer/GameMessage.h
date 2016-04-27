#pragma once
#include <cstdlib>
#include <cstdint>

typedef uint32_t ID;

enum class MessageType : uint8_t {
	Connect = 0, Disconnect = 1, Reconnect = 2, Status = 3, Ping = 4, Pong = 5
};


enum Face : uint8_t {
	UP = 0, FRONT = 1, LEFT = 2, RIGHT = 3, NONE = 4
};

#pragma pack(push, 1)
struct Message {
	MessageType type;
	uint16_t size;
	uint8_t data[];
};

struct Status {
	float px, py;
	float vx, vy;
	Face face;
	int hp;
};

struct StatusMessage {
	ID id;
	uint32_t order;
	Status stat;
};
#pragma pack(pop)
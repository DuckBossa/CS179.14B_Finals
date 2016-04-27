#include <string>
#include <system_error>
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <chrono>
#include <array>
#include <functional>
#include <algorithm>
#include <unordered_map>
#include <atomic>
#include <boost/asio.hpp>


using namespace std;

typedef chrono::steady_clock Clock;

enum class MessageType : uint8_t {
	Connect = 0, Disconnect = 1, Reconnect = 2, Position = 3, Ping = 4, Pong = 5
};

typedef uint32_t ID;

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


struct Client{
	ID client_id;
	boost::asio::ip::udp::endpoint endpoint;
	boost::asio::ip::udp::socket &socket;
	chrono::time_point<Clock> last_packet;
	std::vector<uint8_t> send_buf;

	void send(MessageType type, const void *data, size_t length) {
		send_buf.resize(sizeof(Message) + length);
		auto p = reinterpret_cast<Message*>(send_buf.data());
		p->type = type;
		p->size = length;
		memcpy(p->data, data, length);
		cout << "Sending data of total size: " << send_buf.size() << endl;
		socket.async_send_to(boost::asio::buffer(send_buf), endpoint, [this](auto error, auto size) {
			cout << "Send success\n";
		});
	}
};

atomic<ID> id_counter = 0;
unordered_map<ID, Client> clients;

int main(int argc, char **argv) {
	int port = 8080;
	
	if (argc > 1) {
		port = strtoul(argv[1], 0, 10);
	}
	std::array<uint8_t, 1024> recv_buffer;
	try {
		boost::asio::io_service service;
		boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::udp::v6(),port);
		boost::asio::ip::udp::socket socket(service, endpoint);/*server stuff*/
		boost::asio::ip::udp::endpoint source; /*server's endpoint*/

		std::function<void(boost::system::error_code, size_t)> handler = [&](boost::system::error_code err, size_t length) {
			auto msg = reinterpret_cast<const Message*>(recv_buffer.data());
			switch (msg->type) {
			case MessageType::Connect:{
				ID id = id_counter++;
				auto result = clients.emplace(id, Client{ id,source,socket,Clock::now() });
				result.first->second.send(MessageType::Connect, &id, sizeof(id));
				break;
			}
			case MessageType::Disconnect:
				if (msg->size == sizeof(ID)) {
					auto id = *reinterpret_cast<const ID*>(msg->data);
					auto it = clients.find(id);
					clients.erase(it);
				}
				break;
			case MessageType::Position: {
				if (msg->size < sizeof(PositionMessage)) {
					cerr << "error" << endl;
				}
				else {
					auto pm = reinterpret_cast<const PositionMessage*> (msg->data);
					for (auto &client : clients) {
						if (client.first != pm->id) {
							client.second.send(MessageType::Position, msg->data, msg->size);
						}
						else {
							client.second.last_packet = Clock::now();
							client.second.endpoint = source;
						}
					}
				}
				}
				break;
			}
			socket.async_receive_from(boost::asio::buffer(recv_buffer.data(), recv_buffer.size()), source, handler);
		};

		socket.async_receive_from(boost::asio::buffer(recv_buffer.data(), recv_buffer.size()), source, handler);

	}
	catch (exception e) {
		cerr << e.what() << endl;
	}

	return 0;
}
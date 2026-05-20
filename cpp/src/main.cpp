#include <iostream>
#include <string>

#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

#include <nlohmann/json.hpp>

using tcp = boost::asio::ip::tcp;
namespace websocket = boost::beast::websocket;

int main() {
    try {
        boost::asio::io_context ioc;

        tcp::resolver resolver{ioc};
        websocket::stream<tcp::socket> ws{ioc};

        auto const results = resolver.resolve("127.0.0.1", "2014");

        boost::asio::connect(ws.next_layer(), results.begin(), results.end());

        ws.handshake("127.0.0.1", "/");

        std::cout << "Connected\n";

        while (true) {
            boost::beast::flat_buffer buffer;

            ws.read(buffer);

            std::string message =
                boost::beast::buffers_to_string(buffer.data());

            auto data = nlohmann::json::parse(message);

            std::cout << "RIGHT: " << data["right"] << std::endl;
            std::cout << "LEFT : " << data["left"] << std::endl;
            std::cout << "BODY : " << data["body"] << std::endl;
        }
    }
    catch (std::exception const& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
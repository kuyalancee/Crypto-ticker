#include <iostream>
#include <string>
#include <limits>
#include <ixwebsocket/IXNetSystem.h>
#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXUserAgent.h>
#include <nlohmann/json.hpp>
#include "TradeUtils.h"

using json = nlohmann::json;

int main() {
    ix::initNetSystem();

    ix::WebSocket webSocket;
    std::string url = "wss://ws-feed.exchange.coinbase.com";
    webSocket.setUrl(url);

    std::string ticker;
    std::cout << "Enter ticker to track (e.g., BTC-USD): ";
    std::cin >> ticker;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    
    std::cout << "Connecting to Coinbase..." << std::endl;

    json subscribeMsg = {
        {"type", "subscribe"},
        {"product_ids", {ticker}}, 
        {"channels", {"ticker"}}
    };

    webSocket.setOnMessageCallback([&webSocket, subscribeMsg](const ix::WebSocketMessagePtr& msg) {
        if (msg->type == ix::WebSocketMessageType::Message) {
            auto trade = parse_trade_message(msg->str);
            if (trade) {
                std::cout << "[" << trade->product_id << "] " << trade->side << " @ $" << trade->price << std::endl;
            }
        } 
        else if (msg->type == ix::WebSocketMessageType::Open) {
            std::cout << "Connection Established. Sending subscription..." << std::endl;
            webSocket.send(subscribeMsg.dump());
        } 
        else if (msg->type == ix::WebSocketMessageType::Error) {
            std::cout << "Connection Error: " << msg->errorInfo.reason << std::endl;
        }
    });

    webSocket.start();

    // Keep running
    std::cout << "Listening for trades. Press Enter to exit..." << std::endl;
    std::cin.get();

    webSocket.stop();
    return 0;
}
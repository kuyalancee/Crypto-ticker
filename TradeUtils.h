#pragma once
#include <string>
#include <optional>
#include <nlohmann/json.hpp>

struct TradeData {
    std::string product_id;
    std::string price;
    std::string side;
};
std::optional<TradeData> parse_trade_message(const std::string& raw_message);

#include "TradeUtils.h"

using json = nlohmann::json;

std::optional<TradeData> parse_trade_message(const std::string& raw_message) {
    try {
        auto data = json::parse(raw_message);
        if (data.contains("price") && data.contains("product_id")) {
            TradeData trade;
            trade.product_id = data["product_id"];
            trade.price = data["price"];
            trade.side = data.value("side", "neutral");
            return trade;
        }
    } catch (...) {
        return std::nullopt;
    }
    return std::nullopt;
}

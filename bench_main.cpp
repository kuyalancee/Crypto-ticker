#include <benchmark/benchmark.h>
#include "TradeUtils.h"

//  ex format
const std::string sample_msg = R"({
    "type": "ticker",
    "sequence": 1234567890,
    "product_id": "BTC-USD",
    "price": "45000.50",
    "open_24h": "44000.00",
    "volume_24h": "15000.00",
    "low_24h": "43500.00",
    "high_24h": "46000.00",
    "volume_30d": "500000.00",
    "best_bid": "45000.00",
    "best_ask": "45000.50",
    "side": "buy",
    "time": "2023-10-27T10:00:00.000000Z",
    "trade_id": 987654321,
    "last_size": "0.01234567"
})";

static void BM_ParseTrade(benchmark::State& state) {
    auto test_trade = parse_trade_message(sample_msg);
    if (!test_trade) {
        state.SkipWithError("FIX ME");
        return;
    }

    for (auto _ : state) {
        auto trade = parse_trade_message(sample_msg);
        benchmark::DoNotOptimize(trade);
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BM_ParseTrade);

BENCHMARK_MAIN();

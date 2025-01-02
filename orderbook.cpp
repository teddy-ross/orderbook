#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <variant>
#include <optional>
#include <tuple>
#include <format>

enum class OrderType{
    GoodTilCancel,
    FillAndKill
};

enum class Side{
    Buy,
    Sell
};

using Price = int32_t;
using Quantity = uint32_t;
using OrderId = uint64_t;

struct LevelInfo{
    Price price_;
    Quantity quantity_;
};

using LevelInfos = std::vector<LevelInfos>;

class OrderbookLevelInfos{

public:
    OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
        : bids_{ bids }
        , asks_{ asks }
    { }

    const LevelInfos& GetBidTrade() const { return bids_; }
    const LevelInfos& GetAskTrade() const { return asks_; }

private:
    LevelInfos bids_;
    LevelInfos asks_;
};



int main(){


    return 0;
}

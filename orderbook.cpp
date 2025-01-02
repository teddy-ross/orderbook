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

//class that contains the information and read methods for our bids and asks
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

class Order{

public:

    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
        : orderType_{orderType}
        , orderId_{orderId}
        , side_{side}
        , price_{price}
        , initialQuantity_{quantity} //need two different types of quantity to describe filled quanitity, initial order and remaining lots
        , remainingQuantity_{quantity}
    { }

    OrderId GetOrderId() const { return orderId_; }
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    OrderType GetOrderType() const {return orderType_;}
    Quantity GetInitialQuantity() const {return initialQuantity_;}
    Quantity GetRemainingQuantity() const {return remainingQuantity_;}
    Quantity GetFilledQuantity() const {return GetInitialQuantity() - GetRemainingQuantity();}

    void Fill(Quantity quantity){

        if (quantity > GetRemainingQuantity()){
            throw std::logic_error("Order cannot be filled for more than its remaining quantity.");
        }
        remainingQuantity_ -= quantity;
};
private:

    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_;
    Quantity remainingQuantity_;
};

int main(){


    return 0;
};

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

//class defining an order
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
    bool IsFilled() const {return GetRemainingQuantity() == 0;}
    
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

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

//Class to modify orders, uses shared pointer to update information
class OrderModify{
public:
    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
        : orderId_{orderId}
        , side_{side}
        , price_{price}
        , quantity_{quantity}
    {}

    OrderId GetOrderId() const { return orderId_; }
    Side GetSide() const {return side_;}
    Price GetPrice() const {return price_;}
    Quantity GetQuantity() const {return quantity_;}

    OrderPointer ToOrderPointer(OrderType type) const{
        return std::make_shared<Order>(type, GetOrderId(), GetSide(),GetPrice, GetQuantity());
    };
private:
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity quantity_;
};

struct TradeInfo{
    OrderId orderId_;
    Price price_;
    Quantity quantity_;
};

// encapsulates trades
class Trade{

public:
    Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade)
        : bidTrade_{bidTrade}
        , askTrade_{ askTrade }
        {}

    const TradeInfo& GetBidTrade() const {return bidTrade_; }
    const TradeInfo& GetAskTrade() const {return askTrade_; }

private:

    TradeInfo bidTrade_;
    TradeInfo askTrade_;

};

using Trades = std::vector<Trade>;

//orderbook class
class Orderbook{
private:

    struct OrderEntry{
        OrderPointer order_{nullptr};
        OrderPointers::iterator location_;

    };

    std::map<Price, OrderPointers, std::greater<Price>> bids_; //maps to define bids and asks, easy O(1) access based on OrderId
    std::map<Price, OrderPointers, std::less<Price>> asks_;
    std::unordered_map<OrderId, OrderEntry> orders_;

    bool CanMatch(Side side, Price price) const{ //checks if we can match our asks or bids with the price
        if (side == Side::Buy) {

            if (asks_.empty()) {
            return false;
        }

        const auto& [bestAsk, _] = *asks_.begin();
        return price >= bestAsk;

    } else { // Matching for Side::Sell
        if (bids_.empty()) {
            return false;
        }

        const auto& [bestBid, _] = *bids_.begin();
        return price <= bestBid;
    }
}


    Trades MatchOrders(){
        Trades trades;

        trades.reserve(orders_.size());

        while(true){
            if(bids_.empty() || asks_.empty()){
                break;
            }
            auto& [bidPrice, bids] = *bids_.begin();
            auto& [askPrice, asks] = *asks_.begin();

            if (bidPrice < askPrice){
                break;
            }

            while (bids.size() && asks.size()){ //go ahead and match bids and asks!
                auto& bid = bids.front(); //best time price priority
                auto& ask = asks.front();

                Quantity quantity = std::min(bid->GetRemainingQuantity(), ask -> GetRemainingQuantity());

                bid->Fill(quantity);
                ask->Fill(quantity);

                if(bid)
            }
        }
    }

};


int main(){


    return 0;
};

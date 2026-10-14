#ifndef ORDERBOOK_MATCHING_ENGINE_HPP
#define ORDERBOOK_MATCHING_ENGINE_HPP

#include "orderbook/order_book.hpp"

#include <vector>

namespace orderbook {

struct Trade {
    OrderId buyer_id;
    OrderId seller_id;
    Price price;
    Quantity quantity;
};

class MatchingEngine {
public:
    void submit_order(const Order& order);

    const OrderBook& order_book() const noexcept;
    const std::vector<Trade>& trades() const noexcept;

private:
    OrderBook order_book_;
    std::vector<Trade> trades_;
};

} // namespace orderbook

#endif

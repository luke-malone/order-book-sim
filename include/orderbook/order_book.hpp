#ifndef ORDERBOOK_ORDER_BOOK_HPP
#define ORDERBOOK_ORDER_BOOK_HPP

#include "orderbook/order.hpp"

#include <cstddef>
#include <vector>

namespace orderbook {

class OrderBook {
public:
    void add_order(const Order& order);

    const std::vector<Order>& bids() const noexcept;
    const std::vector<Order>& asks() const noexcept;

    void remove_bid(std::size_t index);
    void remove_ask(std::size_t index);

    void reduce_bid_quantity(std::size_t index, Quantity quantity);
    void reduce_ask_quantity(std::size_t index, Quantity quantity);

private:
    std::vector<Order> bids_;
    std::vector<Order> asks_;
};

} // namespace orderbook

#endif

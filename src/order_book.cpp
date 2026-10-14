#include "orderbook/order_book.hpp"

#include <algorithm>
#include <stdexcept>

namespace orderbook {

void OrderBook::add_order(const Order& order) {
    if (order.side() == Side::Buy) {
        bids_.push_back(order);
        std::stable_sort(bids_.begin(), bids_.end(),
            [](const Order& a, const Order& b) {
                return a.price() > b.price();
            });
    } else {
        asks_.push_back(order);
        std::stable_sort(asks_.begin(), asks_.end(),
            [](const Order& a, const Order& b) {
                return a.price() < b.price();
            });
    }
}

const std::vector<Order>& OrderBook::bids() const noexcept {
    return bids_;
}

const std::vector<Order>& OrderBook::asks() const noexcept {
    return asks_;
}

void OrderBook::remove_bid(std::size_t index) {
    if (index >= bids_.size()) {
        throw std::out_of_range("Bid index out of range");
    }
    bids_.erase(bids_.begin() + static_cast<std::ptrdiff_t>(index));
}

void OrderBook::remove_ask(std::size_t index) {
    if (index >= asks_.size()) {
        throw std::out_of_range("Ask index out of range");
    }
    asks_.erase(asks_.begin() + static_cast<std::ptrdiff_t>(index));
}

void OrderBook::reduce_bid_quantity(std::size_t index, Quantity quantity) {
    if (index >= bids_.size()) {
        throw std::out_of_range("Bid index out of range");
    }

    const Order& order = bids_[index];
    if (quantity == 0 || quantity >= order.quantity()) {
        throw std::invalid_argument("Invalid bid quantity reduction");
    }

    bids_[index] = Order(order.id(), order.side(), order.price(),
                         order.quantity() - quantity);
}

void OrderBook::reduce_ask_quantity(std::size_t index, Quantity quantity) {
    if (index >= asks_.size()) {
        throw std::out_of_range("Ask index out of range");
    }

    const Order& order = asks_[index];
    if (quantity == 0 || quantity >= order.quantity()) {
        throw std::invalid_argument("Invalid ask quantity reduction");
    }

    asks_[index] = Order(order.id(), order.side(), order.price(),
                         order.quantity() - quantity);
}

} // namespace orderbook

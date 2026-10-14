#include "orderbook/matching_engine.hpp"

#include <algorithm>

namespace orderbook {

void MatchingEngine::submit_order(const Order& order) {
    Quantity remaining = order.quantity();

    if (order.side() == Side::Buy) {
        while (remaining > 0 && !order_book_.asks().empty()) {
            const Order best_ask = order_book_.asks().front();

            if (order.price() < best_ask.price()) {
                break;
            }

            const Quantity executed = std::min(remaining, best_ask.quantity());

            trades_.push_back(Trade{
                order.id(), best_ask.id(), best_ask.price(), executed
            });

            remaining -= executed;

            if (executed == best_ask.quantity()) {
                order_book_.remove_ask(0);
            } else {
                order_book_.reduce_ask_quantity(0, executed);
            }
        }
    } else {
        while (remaining > 0 && !order_book_.bids().empty()) {
            const Order best_bid = order_book_.bids().front();

            if (order.price() > best_bid.price()) {
                break;
            }

            const Quantity executed = std::min(remaining, best_bid.quantity());

            trades_.push_back(Trade{
                best_bid.id(), order.id(), best_bid.price(), executed
            });

            remaining -= executed;

            if (executed == best_bid.quantity()) {
                order_book_.remove_bid(0);
            } else {
                order_book_.reduce_bid_quantity(0, executed);
            }
        }
    }

    if (remaining > 0) {
        order_book_.add_order(
            Order(order.id(), order.side(), order.price(), remaining)
        );
    }
}

const OrderBook& MatchingEngine::order_book() const noexcept {
    return order_book_;
}

const std::vector<Trade>& MatchingEngine::trades() const noexcept {
    return trades_;
}

} // namespace orderbook

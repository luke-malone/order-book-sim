#include "orderbook/order.hpp"

#include <stdexcept>

namespace orderbook {

Order::Order(OrderId id, Side side, Price price, Quantity quantity)
    : id_(id),
      side_(side),
      price_(price),
      quantity_(quantity) {
    if (price <= 0) {
        throw std::invalid_argument("Order price must be positive");
    }

    if (quantity == 0) {
        throw std::invalid_argument("Order quantity must be positive");
    }
}

OrderId Order::id() const noexcept {
    return id_;
}

Side Order::side() const noexcept {
    return side_;
}

Price Order::price() const noexcept {
    return price_;
}

Quantity Order::quantity() const noexcept {
    return quantity_;
}

} // namespace orderbook

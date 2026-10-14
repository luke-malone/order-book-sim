
#ifndef ORDERBOOK_ORDER_HPP
#define ORDERBOOK_ORDER_HPP

#include <cstdint>

namespace orderbook {

enum class Side {
    Buy,
    Sell
};

using OrderId = std::uint64_t;
using Price = std::int64_t;
using Quantity = std::uint64_t;

class Order {
public:
    Order(OrderId id, Side side, Price price, Quantity quantity);

    OrderId id() const noexcept;
    Side side() const noexcept;
    Price price() const noexcept;
    Quantity quantity() const noexcept;

private:
    OrderId id_;
    Side side_;
    Price price_;
    Quantity quantity_;
};

} // namespace orderbook

#endif // ORDERBOOK_ORDER_HPP

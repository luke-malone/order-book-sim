#include "orderbook/order.hpp"

#include <cassert>
#include <stdexcept>

using namespace orderbook;

int main() {
    const Order buy_order(1, Side::Buy, 10000, 10);

    assert(buy_order.id() == 1);
    assert(buy_order.side() == Side::Buy);
    assert(buy_order.price() == 10000);
    assert(buy_order.quantity() == 10);

    bool rejected = false;

    try {
        const Order invalid_order(2, Side::Sell, 0, 5);
    } catch (const std::invalid_argument&) {
        rejected = true;
    }

    assert(rejected);

    return 0;
}

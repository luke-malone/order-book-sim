#include "orderbook/matching_engine.hpp"

#include <cassert>

using namespace orderbook;

int main() {
    MatchingEngine engine;

    // A sell order rests in the book.
    engine.submit_order(Order(1, Side::Sell, 100, 10));

    // A buy order partially fills the resting sell order.
    engine.submit_order(Order(2, Side::Buy, 105, 4));

    assert(engine.trades().size() == 1);
    assert(engine.trades()[0].buyer_id == 2);
    assert(engine.trades()[0].seller_id == 1);
    assert(engine.trades()[0].price == 100);
    assert(engine.trades()[0].quantity == 4);

    assert(engine.order_book().asks().size() == 1);
    assert(engine.order_book().asks()[0].quantity() == 6);

    // A second buy order fills the remaining quantity.
    engine.submit_order(Order(3, Side::Buy, 100, 6));

    assert(engine.trades().size() == 2);
    assert(engine.trades()[1].quantity == 6);
    assert(engine.order_book().asks().empty());

    // Non-crossing orders should remain in the book.
    engine.submit_order(Order(4, Side::Buy, 90, 3));
    engine.submit_order(Order(5, Side::Sell, 110, 2));

    assert(engine.order_book().bids().size() == 1);
    assert(engine.order_book().asks().size() == 1);

    return 0;
}

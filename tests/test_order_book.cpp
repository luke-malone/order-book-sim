#include "orderbook/order_book.hpp"

#include <cassert>

using namespace orderbook;

int main() {
    OrderBook book;

    // Add bids in a deliberately unsorted order.
    book.add_order(Order(1, Side::Buy, 100, 5));
    book.add_order(Order(2, Side::Buy, 105, 3));
    book.add_order(Order(3, Side::Buy, 100, 2));

    // Highest bid must come first.
    assert(book.bids().size() == 3);
    assert(book.bids()[0].id() == 2);
    assert(book.bids()[1].id() == 1);
    assert(book.bids()[2].id() == 3);

    // Add asks in a deliberately unsorted order.
    book.add_order(Order(4, Side::Sell, 110, 4));
    book.add_order(Order(5, Side::Sell, 108, 2));
    book.add_order(Order(6, Side::Sell, 110, 1));

    // Lowest ask must come first.
    assert(book.asks().size() == 3);
    assert(book.asks()[0].id() == 5);
    assert(book.asks()[1].id() == 4);
    assert(book.asks()[2].id() == 6);

    return 0;
}

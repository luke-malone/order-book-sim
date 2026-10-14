add_executable(test_order
    test_order.cpp
    ../src/order.cpp
)
target_include_directories(test_order PRIVATE ../include)
add_test(NAME OrderTest COMMAND test_order)

add_executable(test_order_book
    test_order_book.cpp
    ../src/order.cpp
    ../src/order_book.cpp
)
target_include_directories(test_order_book PRIVATE ../include)
add_test(NAME OrderBookTest COMMAND test_order_book)

add_executable(test_matching_engine
    test_matching_engine.cpp
    ../src/order.cpp
    ../src/order_book.cpp
    ../src/matching_engine.cpp
)
target_include_directories(test_matching_engine PRIVATE ../include)
add_test(NAME MatchingEngineTest COMMAND test_matching_engine)

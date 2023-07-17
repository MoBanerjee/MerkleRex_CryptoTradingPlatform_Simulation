#include "OrderBookEntry.h"
OrderBookEntry::OrderBookEntry(string timestamp, string product, OrderType ordertype, double price, double amount,string username) : timestamp(timestamp),
                                                                                                                     product(product),
                                                                                                                     ordertype(ordertype),
                                                                                                                     price(price),
                                                                                                                     amount(amount),
                                                                                                                     username(username){};
OrderType OrderBookEntry::sToOT(string s)
{
    if(s=="ask")return OrderType::ask;
    if(s=="bid")
        return OrderType::bid;
    return OrderType::unknown;
};
bool OrderBookEntry::comparator(OrderBookEntry o1, OrderBookEntry o2){
    return o1.timestamp < o2.timestamp;
};
bool OrderBookEntry::compasc(OrderBookEntry o1, OrderBookEntry o2)
{
    return o1.price < o2.price;
};
bool OrderBookEntry::compdesc(OrderBookEntry o1, OrderBookEntry o2)
{
    return o1.price > o2.price;
};
#pragma once
#include <bits/stdc++.h>

using namespace std;
enum class OrderType
{
    ask,
    bid,
    unknown,
    asksale,
    bidsale
};
class OrderBookEntry
{
public:
/**Constructs OBE time,prod,ot,price,am */
    OrderBookEntry(string timestamp, string product, OrderType ordertype, double price, double amount,string username="Dataset");
    string timestamp;
    string product;
    OrderType ordertype;
    double price;
    double amount;
    string username;
    static OrderType sToOT(string s);
    static bool comparator(OrderBookEntry o1, OrderBookEntry o2);
    static bool compasc(OrderBookEntry o1, OrderBookEntry o2);
    static bool compdesc(OrderBookEntry o1, OrderBookEntry o2);
};

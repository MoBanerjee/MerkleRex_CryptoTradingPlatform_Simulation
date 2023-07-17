#pragma once
#include "CSVReader.h"
class OrderBook{
    public:
    OrderBook(string filen);
    static vector<string> getProduct(const vector<OrderBookEntry>& o);
    vector<OrderBookEntry> getOrders(string time, OrderType oty, string pr);
    static double getMin(vector<OrderBookEntry> ui);
    static double getMax(const std::vector<OrderBookEntry>& ui);
    vector<OrderBookEntry> orders;
    string getEarliestTime();
    string getNextTime(string nowtime);
    static double bidaskspread(const vector<OrderBookEntry> &li, const vector<OrderBookEntry> &lj);
   void inserter(OrderBookEntry newo);
   vector<OrderBookEntry> matchingengine(string timestp, string prodt);
};

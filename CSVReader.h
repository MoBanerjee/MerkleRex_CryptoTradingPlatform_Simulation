#pragma once
#include "OrderBookEntry.h"
class CSVReader{
    public:
    CSVReader();
    static vector<OrderBookEntry> read_CSV(string file);
    static vector<string> tokenise(string csvLine,char sep);
    static OrderBookEntry sToOBE(string time,string products,OrderType otyp,string price, string amnt);

private:
   
    static OrderBookEntry sToOBE(const vector<string> &e);
};
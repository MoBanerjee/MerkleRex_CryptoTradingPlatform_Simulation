#pragma once
#include "OrderBook.h"
class Wallet{
    public:
    void insertcurrency(string curr,double amnt);
    bool remcurrency(string curr, double amnt);
    bool containscurrency(string curr, double amnt);
    string toString();
    friend ostream &operator<<(ostream &o, Wallet wall);
    bool canfulfillorder(OrderBookEntry ob){
        if(ob.ordertype==OrderType::ask){
            string pdt = CSVReader::tokenise(ob.product, '/')[0];
            return containscurrency(pdt, ob.amount);
        }
        else{
            string pdt = CSVReader::tokenise(ob.product, '/')[1];
            return containscurrency(pdt, ob.amount*ob.price);
        }
    }
    void processSale(OrderBookEntry t);

    map<string, double> userwallet;
};
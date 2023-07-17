#include "OrderBook.h"
OrderBook::OrderBook(string filen){
    orders = CSVReader::read_CSV(filen);
};
vector<string> OrderBook::getProduct(const vector<OrderBookEntry> &o){
    map<string,bool> prmap;
    vector<string> prlist;
    for (const auto &t : o)
    {
        prmap[t.product] = true;
    }
    for(const pair<string,bool>& y:prmap){
        prlist.push_back(y.first);
    };
    return prlist;
};
vector<OrderBookEntry> OrderBook::getOrders(string time, OrderType oty, string pr){
      vector<OrderBookEntry> filtered;
      for(const auto& h:orders){
          if(h.timestamp==time && h.ordertype==oty && h.product==pr)
              filtered.push_back(h);
      }
      return filtered;
};
double OrderBook::getMin(vector<OrderBookEntry> ui){
    double min = ui[0].price;
    for (const auto &g : ui)
    {
        if(g.price<min)
            min = g.price;
    }
    return min;
}

double OrderBook::getMax(const std::vector<OrderBookEntry> &ui)
{
    double max = ui[0].price;
    for (const auto &g : ui)
    {
        if (g.price > max)
            max = g.price;
    }
    return max;
}
string OrderBook::getEarliestTime(){
    string timer = orders[0].timestamp;
    for (const auto &r : orders)
    {
        if(r.timestamp<timer)
            timer = r.timestamp;
    }
    return timer;
}
string OrderBook::getNextTime(string nowtime){
    string timer = "";
    for (const auto &r : orders)
    {
        if (r.timestamp > nowtime){
            timer = r.timestamp;
        break;}
    }
    if(timer=="")
        timer = orders[0].timestamp;
    return timer;
}
double OrderBook::bidaskspread(const vector<OrderBookEntry> &li, const vector<OrderBookEntry> &lj)
{
    double hb=getMax(li);
    double la = getMin(lj);
    return hb - la;
}
void OrderBook::inserter(OrderBookEntry newo){
    orders.push_back(newo);
    sort(orders.begin(), orders.end(), OrderBookEntry::comparator);
}
vector<OrderBookEntry> OrderBook::matchingengine(string timestp, string prodt){
    vector<OrderBookEntry> asklist=getOrders(timestp,OrderType::ask,prodt);
    vector<OrderBookEntry> bidlist = getOrders(timestp, OrderType::bid, prodt);
    sort(asklist.begin(),asklist.end(),OrderBookEntry::compasc);
    sort(bidlist.begin(), bidlist.end(), OrderBookEntry::compdesc);
    vector<OrderBookEntry> sales;
    for(OrderBookEntry& a:asklist){
        for(OrderBookEntry& b:bidlist){
            if(b.amount!=0){
            if(b.price>=a.price){
                OrderBookEntry sale{timestp,prodt,OrderType::asksale,a.price,0};
                if(b.username=="simuser"){
                    sale.ordertype = OrderType::bidsale;
                    sale.username = "simuser";
                }
                if (a.username == "simuser")
                {
                    sale.username = "simuser";
                }
                if(b.amount==a.amount){
                    sale.amount=b.amount;
                    sales.push_back(sale);
                    b.amount = 0;
                    break;
                }
                if(b.amount>a.amount){
                    sale.amount=a.amount;
                    sales.push_back(sale);
                    b.amount -= a.amount;
                    break;
                }
                if(b.amount<a.amount){
                    sale.amount=b.amount;
                    sales.push_back(sale);
                    a.amount-=b.amount;
                    b.amount=0;
                    continue;
                }

            }}
        }
    }
    return sales;
}

#include "Wallet.h"
void Wallet::insertcurrency(string curr, double amnt){
    if(amnt<0){
        throw exception{};
    }
    else{
        userwallet[curr] += amnt;
    }
    }

    
bool Wallet::remcurrency(string curr, double amnt){
    if(amnt<0)
    return false;
    if(userwallet.count(curr)==0)
        return false;
    userwallet[curr] -= amnt;
    return true;
};
bool Wallet::containscurrency(string curr, double amnt){
    if(userwallet.count(curr)==1){
        if(userwallet[curr]>=amnt)
            return true;
       
    }
    return false;
};
string Wallet::toString(){
 string s;
 for(const pair<string,double>& p:userwallet){
     string c=p.first;
     double a = p.second;
     s += c + ": " + to_string(a) + "\n";
 }
 return s;
};
ostream &operator<<(ostream &o, Wallet wall){
    o << wall.toString();
    return o;
}
void Wallet::processSale(OrderBookEntry t){
    if (t.ordertype == OrderType::asksale)
    {
        string p1 = CSVReader::tokenise(t.product, '/')[0];
        string p2 = CSVReader::tokenise(t.product, '/')[1];
        insertcurrency(p2,t.price*t.amount);
        remcurrency(p1, t.amount);
    }
    else
    {
        string p1 = CSVReader::tokenise(t.product, '/')[0];
        string p2 = CSVReader::tokenise(t.product, '/')[1];
        insertcurrency(p1,t.amount);
        remcurrency(p2, t.price * t.amount);
    }
}
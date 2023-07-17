#include"CSVReader.h"
vector<OrderBookEntry> CSVReader::read_CSV(string file){
    ifstream reader{file};
    string line;
    vector<OrderBookEntry> entries;
    if (reader.is_open())
    {
       while(getline(reader, line)){
           vector<string> tokenlist=tokenise(line,',');
           try{
           entries.push_back(sToOBE(tokenlist));}catch(const exception&e){
               continue;
           };

       };//end of getline while
       reader.close();
    }//end of readerisopen if
    else{
        cout << "Bad data file! Cannot access!" << endl;
        return entries;
    } //end of topmost else
    return entries;
};
vector<string> CSVReader::tokenise(string csvLine,char sep){
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(sep, 0);
    do
    {
        end = csvLine.find_first_of(sep, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end != std::string::npos);
     return tokens;
};
OrderBookEntry CSVReader::sToOBE(const vector<string> &e){
    double price, amount;
    OrderType ot;
    if (e.size() != 5)
    {
        throw exception{};
    }
try{
price=stod(e[3]);
amount = stod(e[4]);
ot = OrderBookEntry::sToOT(e[2]);}
catch(const exception& exc){
    throw exc;
};
return OrderBookEntry{e[0], e[1], ot, price, amount};
};
OrderBookEntry CSVReader::sToOBE(string time, string products, OrderType otyp,string price, string amnt){
    double p, a;
    try
    {
        p=stod(price);
        a=stod(amnt);

    }
    catch(const exception& e){
        std::cout << "CSVReader::stringsToOBE Bad float! " << price<< std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amnt<< std::endl;
        throw;
    };
    return OrderBookEntry(time, products, otyp, p, a);
};

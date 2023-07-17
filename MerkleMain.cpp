#include "MerkleMain.h"
void MerkleMain::printMenu(){
    std::cout << " 1 : Print help " << std::endl;
    std::cout << " 2: Print exchange stats " << std::endl;
    std::cout << " 3: Place an ask " << std::endl;
    std::cout << " 4: Place a bid " << std::endl;
    std::cout << " 5: Print wallet " << std::endl;
    std::cout << " 6: Continue " << std::endl;
    std::cout << "Type in 1-6" << std::endl;
    cout << currenttime << endl;
};
int MerkleMain::getUserOption(){
int n=0;
string inn;
getline(cin, inn);
try{
n = stoi(inn);}catch(const exception& et){}
std::cout << "You chose: " << inn << std::endl;
return n;
};
void MerkleMain::processUserOption(int userOption){
    if (userOption <1 || userOption>6) // bad input
    {
        std::cout << "Invalid choice. Choose 1-6" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterOffer();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        gotoNextTimeframe();
    }
   
};
void MerkleMain::printHelp(){
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
};
void MerkleMain::enterOffer()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    string input;
    getline(cin,input);
    vector<string> tokens = CSVReader::tokenise(input,',');
    if(tokens.size()!=3)
        cout << "Bad input!" << endl;
    else{
        try{
            OrderBookEntry newentry = CSVReader::sToOBE(currenttime, tokens[0], OrderType::ask, tokens[1], tokens[2]);
            if(purse.canfulfillorder(newentry)){
                cout << "Wallet looks good" << endl;
                newentry.username = "simuser";
                orderbook.inserter(newentry);
            }
            else
            {
                cout << "Wallet has insufficient funds" << endl;
            }
        }catch(const exception& ec){

        }
    }
    cout << "You entered: " << input << endl;

}

void MerkleMain::enterBid(){
    std::cout << "Make a bid - enter the amount: product,price, amount, eg ETH/BTC,200,0.5" << std::endl;
    string input;
    getline(cin, input);
    vector<string> tokens = CSVReader::tokenise(input,',');
    if (tokens.size() != 3)
        cout << "Bad input!" << endl;
    else
    {
        try
        {
            OrderBookEntry newentry = CSVReader::sToOBE(currenttime, tokens[0], OrderType::bid, tokens[1], tokens[2]);
            if(purse.canfulfillorder(newentry)){
                cout << "Wallet looks good" << endl;
                newentry.username = "simuser";
                orderbook.inserter(newentry);
            }
            else{
                cout << "Wallet has insufficient funds" << endl;
            }
        }
        catch (const exception &ec)
        {
        }
    }
    cout << "You entered: " << input << endl;
}

void MerkleMain::printWallet()
{if(purse.userwallet.size()==0)
    std::cout << "Your wallet is empty. " << std::endl;
    else{
        cout << purse;
    }
}

void MerkleMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    vector<OrderBookEntry> finalsale;
     for (const string &pr : OrderBook::getProduct(orderbook.orders))
    {finalsale=orderbook.matchingengine(currenttime,pr);
        std::cout << "matching " << pr << std::endl;
        std::cout << "Sales: " << finalsale.size() << std::endl;
        for(const OrderBookEntry &sl:finalsale){
            if(sl.username=="simuser"){
                purse.processSale(sl);
            }
            cout << "Sale price: " << sl.price << " Amount: " << sl.amount << endl;
        }
    }
    currenttime = orderbook.getNextTime(currenttime);
}
void MerkleMain::printMarketStats(){
    for (const auto &hy : orderbook.getProduct(orderbook.orders)){
        cout<<"Product: "<<hy<<endl;
        vector<OrderBookEntry> temp1 = orderbook.getOrders(currenttime, OrderType::bid, hy);
        vector<OrderBookEntry> temp = orderbook.getOrders(currenttime, OrderType::ask, hy);
       cout << "Asks seen: " << temp.size() << endl;
        cout<<"Max ask: "<<orderbook.getMax(temp)<<endl;
        cout << "Min ask: " << orderbook.getMin(temp) << endl;
        cout << "Bid-Ask Spread: " << orderbook.bidaskspread(temp1, temp) << endl;
    };
}

void MerkleMain::init(){
    currenttime = orderbook.getEarliestTime();
    try{
    purse.insertcurrency("BTC", 10);}catch(const exception& e){
        cout << "Negative amounts invalid!" << endl;
    }
    while (true)
    {

        printMenu();
        processUserOption(getUserOption());

};
};

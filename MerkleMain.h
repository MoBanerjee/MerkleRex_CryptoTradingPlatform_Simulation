#pragma once
#include"OrderBook.h"
#include"Wallet.h"
class MerkleMain{
    public:
    string datafile="Data.csv";
    void init();
    private:
      Wallet purse;
      string currenttime;
      void printMenu();
      static void printHelp();
      void printMarketStats();
      void enterOffer();
      /** enter ur bid */
      void enterBid();
        /** This prints my wallet*/
        void printWallet();
       void gotoNextTimeframe();
        static int getUserOption();
        void processUserOption(int userOption);
        OrderBook orderbook{"Data.csv"};

       
};

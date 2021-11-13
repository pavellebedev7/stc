#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>

#define COMISSION 1.0
#define BANK_FUNDS 9000000
static bool Finished = false;

using namespace std;

class Customer{
public:
    uint32_t id;
    uint32_t deposit;
    mutex m;
    Customer(uint32_t id=0, uint32_t d=0):id(id),deposit(d){}
    virtual ~Customer(){}
};

class Bank{
public:
    uint32_t totalFunds;
    mutex m;
    Bank(uint32_t f=BANK_FUNDS):totalFunds(f){}
    virtual ~Bank(){}
};

void Transaction(Bank &b, Customer &c, uint32_t sum, bool toBank){
    uint32_t sumWithCommission = sum;
    lock(b.m, c.m);
    lock_guard<mutex> lock1(b.m, adopt_lock);
    lock_guard<mutex> lock2(c.m, adopt_lock);
    if(toBank){ // Customer to bank transaction
        sumWithCommission *= 1.0 - COMISSION/100.0;
        b.totalFunds += sum;
        c.deposit += sumWithCommission;
        cout << "Transaction: " << sum
             << " (" << sumWithCommission << ")"
             << " from customer: " << c.id
             << " to bank.\t Total bank funds: " << b.totalFunds
             << "\tCustomer: " << c.id
             << " deposit: " << c.deposit
             << endl;
    }else{ // Bank to customer transaction
        sumWithCommission *= 1.0 + COMISSION/100.0;
        b.totalFunds -= sum;
        c.deposit -= sumWithCommission;
        cout << "Transaction: " << sum
             << " (" << sumWithCommission << ")"
             << " from bank to customer: " << c.id
             << ".\t Total bank funds: " << b.totalFunds
             << "\tCustomer: " << c.id
             << " deposit: " << c.deposit
             << endl;
    }
}

void CustomerSimulation(Bank &b, Customer &c){
    srand(time(NULL));
    while(!Finished){
        uint32_t sum = (2 + rand() % 8)*100;    // Get random sum for transaction
        uint32_t type = rand() % 2;             // Get random type of transaction
        uint32_t time = 100 + rand() % 2000;    // Get random time between transactions
        Transaction(b, c, sum, type);           // Start transaction
        chrono::milliseconds t(time);
        this_thread::sleep_for(t);              // Wait for time between transactions
    }
}

int main()
{
    Bank bank;
    Customer customer1(0, 10000);
    Customer customer2(1, 20000);
    Customer customer3(2, 30000);
    chrono::milliseconds t(500);

    thread t1(CustomerSimulation, ref(bank), ref(customer1));
    this_thread::sleep_for(t);
    thread t2(CustomerSimulation, ref(bank), ref(customer2));
    this_thread::sleep_for(t);
    thread t3(CustomerSimulation, ref(bank), ref(customer3));
    this_thread::sleep_for(t);

    cin.get();
    Finished = true;

    t1.join();
    t2.join();
    t3.join();
    return 0;
}

#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <iomanip>
#include <typeinfo>

class BankAccount {
protected:
    int AccountNumber;
    std::string AccountName;
    double balance;
    std::vector<std::string> transactionHistory;

public:
    BankAccount(int number, std::string name, double bal)
        : AccountNumber(number), AccountName(name), balance(bal) {}

    virtual ~BankAccount() {}

    virtual void addDeposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive.");
        }
        balance += amount;
        std::string transaction = "Deposited: " + std::to_string(amount) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive.");
        }
        if (amount > balance) {
            throw std::invalid_argument("Insufficient funds.");
        }
        balance -= amount;
        std::string transaction = "Withdrew: " + std::to_string(amount) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    virtual void withdraw(double amount, double fee) {
        if (amount <= 0 || fee < 0) {
            throw std::invalid_argument("Withdrawal amount must be positive and fee must be non-negative.");
        }
        if ((amount + fee) > balance) {
            throw std::invalid_argument("Insufficient funds.");
        }
        balance -= (amount + fee);
        std::string transaction = "Withdrew: " + std::to_string(amount) + " with a fee of " + std::to_string(fee) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    virtual void getAccountDetails(const std::string& format = "") const {
        if (format == "detailed") {
            std::cout << "Account Number: " << AccountNumber << std::endl;
        }
        std::cout << "Account Name: " << AccountName << ", Balance: " << balance << std::endl;
    }

    double getBalance() const {
        return balance;
    }
};

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(int number, std::string name, double bal, double rate, int free_withdraw_per_month, double fee_per_withdraw)
        : BankAccount(number, name, bal), rate(rate), free_withdraw_remaining(free_withdraw_per_month), fee_per_withdraw(fee_per_withdraw) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive.");
        }

        if (amount > balance) {
            std::cout << "Savings account has insufficient funds for this withdrawal." << std::endl;
            return;
        }

        if (free_withdraw_remaining > 0) {
            free_withdraw_remaining--;
        } else {
            if (amount + fee_per_withdraw > balance) {
                std::cout << "Savings account has insufficient funds for this withdrawal with fee." << std::endl;
                return;
            }
            balance -= fee_per_withdraw;
        }
        
        balance -= amount;
        std::string transaction = "Withdrew: " + std::to_string(amount) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    void getAccountDetails(const std::string& format = "") const override {
        BankAccount::getAccountDetails(format);
        if (format == "detailed") {
            std::cout << "Interest Rate: " << rate << "%" << std::endl;
            std::cout << "Free Withdrawals Remaining: " << free_withdraw_remaining << std::endl;
            std::cout << "Fee per Extra Withdrawal: " << fee_per_withdraw << std::endl;
        }
    }

private:
    double rate;
    int free_withdraw_remaining;
    double fee_per_withdraw;
};

class CheckingAccount : public BankAccount {
public:
    CheckingAccount(int number, std::string name, double bal, double rate, int free_withdraw_per_month, double fee_per_withdraw)
        : BankAccount(number, name, bal), rate(rate), free_withdraw_remaining(free_withdraw_per_month), fee_per_withdraw(fee_per_withdraw) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive.");
        }

        if (amount > balance) {
            std::cout << "Checking account has insufficient funds for this withdrawal." << std::endl;
            return;
        }

        if (free_withdraw_remaining > 0) {
            free_withdraw_remaining--;
            if (amount + fee_per_withdraw > balance) {
                std::cout << "Checking account has insufficient funds for this withdrawal with fee." << std::endl;
                return;
            }
            balance -= fee_per_withdraw;
        }

        balance -= amount;
        std::string transaction = "Withdrew: " + std::to_string(amount) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    void getAccountDetails(const std::string& format = "") const override {
        BankAccount::getAccountDetails(format);
        if (format == "detailed") {
            std::cout << "Interest Rate: " << rate << "%" << std::endl;
            std::cout << "Free Withdrawals Remaining: " << free_withdraw_remaining << std::endl;
            std::cout << "Fee per Extra Withdrawal: " << fee_per_withdraw << std::endl;
        }
    }

private:
    double rate;
    int free_withdraw_remaining;
    double fee_per_withdraw;
};

class FixedDepositAccount: public BankAccount {
public:
    FixedDepositAccount(int number, std::string name, double bal, double rate, int free_withdraw_per_month, double fee_per_withdraw)
        : BankAccount(number, name, bal), rate(rate), free_withdraw_remaining(free_withdraw_per_month), fee_per_withdraw(fee_per_withdraw) {}

    void withdraw(double amount) override {
        if (amount <= 0) {
            throw std::invalid_argument("Withdrawal amount must be positive.");
        }

        if (amount > balance) {
            std::cout << "Fixed Deposit account has insufficient funds for this withdrawal." << std::endl;
            return;
        }

        if (free_withdraw_remaining > 0) {
            free_withdraw_remaining--;
        } else {
            if (amount + fee_per_withdraw > balance) {
                std::cout << "Fixed Deposit account has insufficient funds for this withdrawal with fee." << std::endl;
                return;
            }
            balance -= fee_per_withdraw;
        }

        balance -= amount;
        std::string transaction = "Withdrew: " + std::to_string(amount) + ". New Balance: " + std::to_string(balance);
        transactionHistory.push_back(transaction);
        std::cout << transaction << std::endl;
    }

    void getAccountDetails(const std::string& format = "") const override {
        BankAccount::getAccountDetails(format);
        if (format == "detailed") {
            std::cout << "Interest Rate: " << rate << "%" << std::endl;
            std::cout << "Free Withdrawals Remaining: " << free_withdraw_remaining << std::endl;
            std::cout << "Fee per Extra Withdrawal: " << fee_per_withdraw << std::endl;
        }
    }

private:
    double rate;
    int free_withdraw_remaining;
    double fee_per_withdraw;
};

double calculateTotalBalance(const std::vector<BankAccount*>& accounts) {
    double total = 0;
    for (const auto& account : accounts) {
        total += account->getBalance();
    }
    return total;
}

int main() {
    std::vector<BankAccount*> accounts;

    accounts.push_back(new SavingsAccount(1, "Savings Account", 1000.0, 1.5, 3, 2.0));
    accounts.push_back(new CheckingAccount(2, "Checking Account", 1500.0, 0.5, 5, 1.0));
    accounts.push_back(new FixedDepositAccount(3, "Fixed Deposit Account", 2000.0, 2.0, 0, 0.0));

    for (const auto& account : accounts) {
        account->getAccountDetails("detailed");
        account->addDeposit(100);
        account->withdraw(50);    
    }

    for (const auto& account : accounts) {
        delete account; 
    }

    return 0;
}

#pragma once

#include "Account.h"

class Checking: public Account {

    private:
        const float minBalance{50.0};

    public:
        using Account::Account;

        void Withdraw(float amount) override;
};
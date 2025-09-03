#include <iostream>
#include "Checking.h"

void Checking::Withdraw(const float amount) {

    std::cout << "CHECKING WITHDRAW" << std::endl;


    // if (m_Balance - amount < minBalance) {
    //     std::cout << "Withdrawal refused" << std::endl;
    //     return;
    // }

   Account::Withdraw(amount);
}
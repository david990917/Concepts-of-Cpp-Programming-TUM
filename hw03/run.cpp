#include "contact_list.h"
#include "hw03.h"

#include <iostream>

namespace contact_list
{

    void test_contact_list()
    {
        storage abook;
        add(abook, "Best Friend", 421234);
        std::cout << to_string(abook);
        add(abook, "False Friend", 10032331);
        add(abook, "False Friend2", 10032332);
        add(abook, "False Friend3", 10032333);
        std::cout << to_string(abook);
    }

} // namespace contact_list

int main()
{
    contact_list::test_contact_list();

    return 0;
}

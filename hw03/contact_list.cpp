#include "contact_list.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <string>

// TODO create implementation here!
namespace contact_list
{
    /**
     * Given a contact storage, create a new contact entry by name and number.
     */
    bool add(storage &contacts, std::string_view name, number_t number)
    {
        std::string sname = std::string(name);
        if (sname.empty() || std::count(contacts.names.begin(), contacts.names.end(), sname) != 0)
        {
            return false;
        }

        contacts.names.push_back(sname);
        contacts.numbers.push_back(number);
        return true;
    }

    /**
     * Given a contact storage, how many contacts are currently stored?
     */
    size_t size(const storage &contacts)
    {
        return contacts.numbers.size();
    }

    /**
     * Fetch a contact number from storage given a name.
     */
    number_t get_number_by_name(storage &contacts, std::string_view name)
    {
        std::string sname = std::string(name);
        for (unsigned i = 0; i < contacts.names.size(); i++)
        {
            if (contacts.names[i] == sname)
            {
                return contacts.numbers[i];
            }
        }
        return -1;
    }

    /**
     * Return a string representing the contact list.
     */
    std::string to_string(const storage &contacts)
    {
        std::string result = "";
        for (unsigned i = 0; i < contacts.names.size(); i++)
        {
            result += (contacts.names[i] + " - " + std::to_string(contacts.numbers[i]) + "\n");
        }
        return result;
    }

    /**
     * Remove a contact by name from the contact list.
     */
    bool remove(storage &contacts, std::string_view name)
    {
        std::string sname = std::string(name);
        for (unsigned i = 0; i < contacts.names.size(); i++)
        {
            if (contacts.names[i] == sname)
            {
                contacts.names.erase(contacts.names.begin() + i);
                contacts.numbers.erase(contacts.numbers.begin() + i);
                return true;
            }
        }
        return false;
    }

    /**
     * Sort the contact list in-place by name.
     */
    void sort(storage &contacts)
    {
        std::vector<std::string> tmp_names = contacts.names;
        std::sort(contacts.names.begin(), contacts.names.end());
        std::vector<number_t> tmp_numbers;
        for (unsigned i = 0; i < contacts.names.size(); i++)
        {
            for (unsigned j = 0; j < contacts.names.size(); j++)
            {
                if (tmp_names[j] == contacts.names[i])
                {
                    tmp_numbers.push_back(contacts.numbers[j]);
                    std::cout << i << " " << j << " " << contacts.names[i] << " " << contacts.numbers[j] << '\n';
                    break;
                }
            }
        }

        contacts.numbers = tmp_numbers;
    }

    /**
     * Fetch a contact name from storage given a number.
     */
    std::string get_name_by_number(storage &contacts, number_t number)
    {
        for (unsigned int i = 0; i < contacts.numbers.size(); i++)
        {
            if (contacts.numbers[i] == number)
            {
                return contacts.names[i];
            }
        }
        return "";
    }
}
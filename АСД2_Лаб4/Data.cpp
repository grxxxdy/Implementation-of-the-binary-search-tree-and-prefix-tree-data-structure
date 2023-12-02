#include <cstdlib>
#include <string>

struct Data
{
    std::string name;
    int rank;
    int expirience;
    int winrate;

    Data()
    {
        name = "Player " + std::to_string(rand() % 10001);
        rank = rand() % 101;
        expirience = rand() % 201;
        winrate = rand() % 101;
    }

    bool operator<(const Data& element) const
    {
        if (this->rank != element.rank)
        {
            return this->rank < element.rank;
        }

        if (this->expirience != element.expirience)
        {
            return this->expirience < element.expirience;
        }

        return this->winrate < element.winrate;
    }

    bool operator>(const Data& element) const
    {
        return element < *this;
    }

    bool operator==(const Data& element) const
    {
        return this->rank == element.rank && this->expirience == element.expirience && this->winrate == element.winrate;
    }
};
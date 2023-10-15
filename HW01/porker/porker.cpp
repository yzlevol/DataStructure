#include <iostream>
#include <vector>
#include <algorithm>
#include <string> 

using namespace std;

struct Card {
    string flower; //»¨É«
    string number; //Êý×Ö

    Card(string f, string n) : flower(f), number(n) {}
};

bool cmp(Card a, Card b) {
    return a.number < b.number;
}

void Append(vector<Card>& cards) {
    string flower, number;
    cin >> flower >> number;

    if ((flower == "Spade" || flower == "Heart" || flower == "Club" || flower == "Diamond") &&
        (number == "A" || number == "2" || number == "3" || number == "4" ||
            number == "5" || number == "6" || number == "7" || number == "8" ||
            number == "9" || number == "10" || number == "J" || number == "Q" ||
            number == "K")) {

        cards.push_back(Card(flower, number));
    }
    else {
        cout << "NULL" << endl;
    }
}

void Extract(vector<Card>& cards) {
    string flower;
    cin >> flower;
    vector<Card> extractedCards;
    for (auto it = cards.begin(); it != cards.end(); ) {
        if (it->flower == flower) {
            extractedCards.push_back(*it);
            it = cards.erase(it);
        }
        else {
            ++it;
        }
    }
    sort(extractedCards.begin(), extractedCards.end(), [](const Card& a, const Card& b) {
        if (a.flower == b.flower) {
            int numA, numB;
            if (a.number == "A") numA = 1;
            else if (a.number == "J") numA = 11;
            else if (a.number == "Q") numA = 12;
            else if (a.number == "K") numA = 13;
            else numA = stoi(a.number);
            if (b.number == "A") numB = 1;
            else if (b.number == "J") numB = 11;
            else if (b.number == "Q") numB = 12;
            else if (b.number == "K") numB = 13;
            else numB = stoi(b.number);
            return numA < numB;
        }
        return a.flower < b.flower;
        });
    cards.insert(cards.begin(), extractedCards.begin(), extractedCards.end());
}

void Revert(vector<Card>& cards) {
    reverse(cards.begin(), cards.end());
}

void Pop(vector<Card>& cards) {
    if (!cards.empty()) {
        cout << cards.front().flower << " " << cards.front().number << endl;
        cards.erase(cards.begin());
    }
    else {
        cout << "NULL" << endl;
    }
}

int main() {
    int n;
    cin >> n;
    vector<Card> cards;
    for (int i = 0; i < n; i++) {
        string cmd;
        cin >> cmd;

        if (cmd == "Append") {
            Append(cards);
        }
        else if (cmd == "Extract") {
            Extract(cards);
        }
        else if (cmd == "Revert") {
            Revert(cards);
        }
        else if (cmd == "Pop") {
            Pop(cards);
        }
    }
    for (const auto& card : cards) {
        cout << card.flower << " " << card.number << endl;
    }
    return 0;
}

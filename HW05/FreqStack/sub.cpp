class FreqStack {
public:
    FreqStack() : maxFreq(0) {}

    void push(int val) {
        freq[val]++;
        maxFreq = max(maxFreq, freq[val]);
        group[freq[val]].push(val);
        elems.push_back(val);
    }
    int pop() {
        int val = group[maxFreq].top();
        group[maxFreq].pop();
        if (group[maxFreq].empty())
            maxFreq--;
        elems.erase(remove(elems.begin(), elems.end(), val), elems.end());

        freq[val]--;
        return val;
    }

private:
    int maxFreq;
    vector<int> elems;
    map<int, int> freq;
    map<int, stack<int>> group;
};

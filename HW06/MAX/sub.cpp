/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
struct {
    bool operator()(string a, string b) const {
        string s1 = a + b;
        string s2 = b + a;
        return s1 > s2;
    }
}cmp;
class Solution {
public:
    std::string largestNumber(std::vector<int>& nums) {
        if (nums.size() == 0) return "";
        vector<string> str;
        for (int i = 0; i < nums.size(); i++) {
            str.push_back(to_string(nums[i]));
        }
        sort(str.begin(), str.end(), cmp);
        string ans = "";
        for (int i = 0; i < str.size(); i++) {
            ans += str[i];
        }
        if (ans[0] == '0') return "0";
        else return ans;
    }
};
/********************************/
/*     ����������Ҫ�ύ�Ĵ���     */
/********************************/
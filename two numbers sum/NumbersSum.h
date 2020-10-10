class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int, int> m;
        vector<int> index;

        for (int i = 0; i < nums.size(); ++i)
        {
            if (m.count(target - nums[i]) != 0)
            {
                index.push_back(m[target - nums[i]]);
                index.push_back(i);
                break;
            }
            m[nums[i]] = i;
        }

        return index;
    }
};


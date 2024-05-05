#include <bits/stdc++.h>
using namespace std;

class SlidingWindow
{

    static SlidingWindow *uniqueInstance;
    string s;
    int k;
    unordered_map<char, int> swCount;
    int swStart, swEnd;

public:
    static SlidingWindow *getInstance()
    {
        if (!uniqueInstance)
        {
            uniqueInstance = new SlidingWindow();
        }
        return uniqueInstance;
    }

    void init(string s, int k)
    {
        this->s = s;
        this->k = k;

        swStart = 0;
        swEnd = 0;
        while (!slidingWindowCondition())
        {
            expandWindow();
        }
    }

    bool expandWindow()
    {
        if (swEnd >= s.length())
            return false;

        swCount[s[swEnd]]++;
        swEnd++;
        return true;
    }

    bool contractWindow()
    {
        if (swStart == swEnd)
            return false;

        swCount[s[swStart]]--;
        swStart++;
        return true;
    }

    char getMaxChar()
    {
        int ans = s[0];
        int ansCount = INT_MIN;
        for (auto p : swCount)
        {
            if (ansCount < p.second)
            {
                ans = p.first;
                ansCount = p.second;
            }
        }

        return ans;
    }

    int getWeirdosCount()
    {
        return (swEnd - swStart) - swCount[getMaxChar()];
    }

    bool slidingWindowCondition()
    {
        return getWeirdosCount() == k;
    }

    bool next()
    {
        int oldStart = swStart;
        int oldEnd = swEnd;
        while (slidingWindowCondition() && expandWindow())
        {
        }
        while (slidingWindowCondition() && contractWindow())
        {
        }

        return (oldStart != swStart) || (oldEnd != swEnd);
    }

    int evaluate()
    {
        cout << swStart << ' ' << swEnd << endl;
        return swEnd - swStart;
    }
};
SlidingWindow *SlidingWindow::uniqueInstance = NULL;

class Solution
{
public:
    // class SlidingWindow;

    int characterReplacement(string s, int k)
    {
        auto sw = SlidingWindow::getInstance();
        sw->init(s, k);
        int ans = sw->evaluate();

        while (sw->next())
        {
            ans = max(ans, sw->evaluate());
        }

        return ans;
    }
};

int main() {
    cout << Solution().characterReplacement("AABABBA", 1) << endl;
}

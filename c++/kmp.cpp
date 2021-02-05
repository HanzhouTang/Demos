vector<int> constructNext(string &p)
{
    vector<int> dp(p.size());
    dp[0] = -1;
    int j = -1;
    for (int i = 1; i < p.size(); i++)
    {
        while (j != -1 && p[j + 1] != p[i])
        {
            j = dp[j];
        }
        if (p[j + 1] == p[i])
        {
            dp[i] = ++j;
        }
        else
        {
            dp[i] = -1;
        }
    }
    return dp;
}
int strStr(string haystack, string needle)
{
    if (needle.empty())
    {
        return 0;
    }
    auto next = constructNext(needle);
    int j = 0;
    int i = 0;
    while (i < haystack.size())
    {
        if (haystack[i] == needle[j])
        {
            j++;
            i++;
            if (j == needle.size())
            {
                return i - j;
            }
        }
        else
        {
            if (j == 0)
            {
                i = i + 1;
            }
            else
            {
                j = next[j - 1] + 1;
            }
        }
    }
    return -1;
}
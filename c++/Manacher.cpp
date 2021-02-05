void manacher_odd(string &s, vector<int> &odd)
{
    int l = 0;
    int r = -1;
    for (int i = 0; i < s.size(); i++)
    {
        if (i > r)
        {
            int len = 0;
            while (i - len >= 0 && i + len < s.size() && s[i - len] == s[i + len])
            {
                len++;
            }
            l = i - len + 1;
            r = i + len - 1;
            odd[i] = len;
        }
        else
        {
            const int t = l + r - i;
            int len = odd[t];
            if (t - len + 1 > l)
            {
                odd[i] = len;
            }
            else
            {
                len = t - l + 1;
                while (i - len >= 0 && i + len < s.size() && s[i - len] == s[i + len])
                {
                    len++;
                }
                l = i - len + 1;
                r = i + len - 1;
                odd[i] = len;
            }
        }
    }
}

void manacher_even(string &s, vector<int> &even)
{
    int l = 0;
    int r = -1;
    for (int i = 0; i < s.size(); i++)
    {
        if (i >= r)
        {
            int len = 0;
            while (i >= len && i + len + 1 < s.size() && s[i - len] == s[i + len + 1])
            {
                len++;
            }
            l = i - len + 1;
            r = i + len;
            even[i] = len;
        }
        else
        {
            const int t = l + r - i - 1;
            int len = even[t];
            if (t - len + 1 > l)
            {
                even[i] = len;
            }
            else
            {
                len = t - l + 1;
                while (i >= len && i + len + 1 < s.size() && s[i - len] == s[i + len + 1])
                {
                    len++;
                }
                l = i - len + 1;
                r = i + len;
                even[i] = len;
            }
        }
    }
}
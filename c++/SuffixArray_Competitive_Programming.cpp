const int N = 510;
int RA[N], RA_TMP[N];
int SA[N], SA_TMP[N];
int C[N];
int LCP[N];
int PLCP[N];
int PHI[N];
void countingSort(int k, int n)
{
    memset(C, 0, sizeof(C));
    const int maxi = max(300, n);
    for (int i = 0; i < n; i++)
    {
        C[i + k >= n ? 0 : RA[i + k]]++;
    }
    int sum = 0;
    for (int i = 0; i < maxi; i++)
    {
        int t = C[i];
        C[i] = sum;
        sum += t;
    }
    for (int i = 0; i < n; i++)
    {
        SA_TMP[C[SA[i] + k >= n ? 0 : RA[SA[i] + k]]++] = SA[i];
    }
    for (int i = 0; i < n; i++)
    {
        SA[i] = SA_TMP[i];
    }
}
void constructSA(string &s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        SA[i] = i;
        RA[i] = s[i];
    }
    for (int k = 1; k < n; k <<= 1)
    {
        countingSort(k, n);
        countingSort(0, n);
        int r = 0;
        RA_TMP[SA[0]] = r;
        for (int i = 1; i < n; i++)
        {
            RA_TMP[SA[i]] = (RA[SA[i - 1]] == RA[SA[i]] && RA[SA[i - 1] + k] == RA[SA[i] + k]) ? r : ++r;
        }
        for (int i = 0; i < n; i++)
        {
            RA[i] = RA_TMP[i];
        }
        if (RA[SA[n - 1]] == n - 1)
        {
            break;
        }
    }
}
void computeLCP(string &s)
{
    int n = s.size();
    int i, L;
    PHI[SA[0]] = -1;
    for (int i = 1; i < n; i++)
    {
        PHI[SA[i]] = SA[i - 1];
    }
    for (i = L = 0; i < n; i++)
    {
        if (PHI[i] == -1)
        {
            PLCP[i] = 0;
            continue;
        }
        while (s[i + L] == s[PHI[i] + L])
            L++;
        PLCP[i] = L;
        L = max(L - 1, 0);
    }
    for (int i = 0; i < n; i++)
    {
        LCP[i] = PLCP[SA[i]];
    }
}

// s.push_back('$');
// constructSA(s);
// computeLCP(s);
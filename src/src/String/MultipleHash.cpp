const int HA = 2;
const int PP[] = {318255569, 66604919, 19260817}, QQ[] = {1010451419, 1011111133, 1033111117};

int pw[HA][N];
void HashInit() {
    for (int h = 0; h < HA; h++) {
        pw[h][0] = 1;
        for (int i = 1; i < N; i++)
            pw[h][i] = (LL)pw[h][i - 1] * PP[h] % QQ[h];
    }
}
struct Hash {
    int hs[HA], len;
    Hash() {
        memset(hs, 0, sizeof hs);
        len = 0;
    }
    Hash(int x) {
        for (int h = 0; h < HA; h++) hs[h] = x;
        len = 1;
    }
    Hash operator + (const int &x)const {
        Hash res;
        res.len = len + 1;
        for (int h = 0; h < HA; h++)
            res.hs[h] = ((LL)hs[h] * PP[h] + x) % QQ[h];
        return res;
    }
    Hash operator - (const Hash &x)const {
        Hash res;
        res.len = len - x.len;
        for (int h = 0; h < HA; h++) {
            res.hs[h] = (hs[h] - (LL)pw[h][res.len] * x.hs[h]) % QQ[h];
            if (res.hs[h] < 0) res.hs[h] += QQ[h];
        }
        return res;
    }
    bool operator == (const Hash &x)const {
        for (int h = 0; h < HA; h++)
            if (hs[h] != x.hs[h]) return false;
        return len == x.len;
    }
    // below : not that frequently used
    Hash operator + (const Hash &x)const {
        Hash res;
        res.len = len + x.len;
        for (int h = 0; h < HA; h++)
            res.hs[h] = ((LL)hs[h] * pw[h][x.len] + x.hs[h]) % QQ[h];
        return res;
    }
} H;
Hash operator + (const int &a, const Hash &b) {
    Hash res;
    res.len = b.len + 1;
    for (int h = 0; h < HA; h++)
        res.hs[h] = ((LL)a * pw[h][b.len] + b.hs[h]) % QQ[h];
    return res;
}

namespace LCT {
    int ch[N][2], f[N], sum[N], val[N], tag[N], dat[N]; // dat 维护的链信息, val 点上信息
    inline void PushUp(int x) {
        dat[x] = dat[ch[x][0]] ^ dat[ch[x][1]] ^ val[x];
    }
    inline void PushRev(int x) {swap(ch[x][0], ch[x][1]); tag[x] ^= 1;}
    inline void PushDown(int x) {
        if (tag[x] == 0) return ;
        PushRev(ch[x][0]); PushRev(ch[x][1]); tag[x] = 0;
    }
    inline bool Get(int x) {return ch[f[x]][1] == x;} // 是父亲的哪个儿子
    inline bool IsRoot(int x) {return (ch[f[x]][1] != x && ch[f[x]][0] != x);} // 是否是当前 Splay 的根
    inline void Rotate(int x) { // Splay 旋转
        int y = f[x], z = f[y], k = Get(x);
        if (!IsRoot(y)) ch[z][Get(y)] = x;
        ch[y][k] = ch[x][k ^ 1]; f[ch[x][k ^ 1]] = y;
        ch[x][k ^ 1] = y; f[y] = x; f[x] = z;
        PushUp(y); PushUp(x);
    }
    void Updata(int x) { // Splay 中从上到下 PushDown
        if (!IsRoot(x)) Updata(f[x]);
        PushDown(x);
    }
    inline void Splay(int x) { // Splay 上把 x 转到根
        Updata(x);
        for (int fa; fa = f[x], !IsRoot(x); Rotate(x)) {
            if (!IsRoot(fa)) Rotate(Get(fa) == Get(x) ? fa : x);
        }
        PushUp(x);
    }
    inline void Access(int x) { // 辅助树上打通 x 到根的路径(即 x 到根变为实链)
        for (int p = 0; x; p = x, x = f[x]) {
            Splay(x); ch[x][1] = p; PushUp(x);
        }
    }
    inline void MakeRoot(int x) { // 钦定 x 为辅助树根
        Access(x); Splay(x); PushRev(x);
    }
    inline int FindRoot(int x) { // 找 x 所在辅助树根
        Access(x); Splay(x);
        while (ch[x][0]) PushDown(x), x = ch[x][0];
        Splay(x); // 不加复杂度会假
        return x;
    }
    inline void Split(int x, int y) { // 把 x 到 y 的路径提出来, 并以 y 为 Splay 根
        MakeRoot(x); Access(y); Splay(y);
    }
    inline bool Link(int x, int y) { // 连接 x,y 两点
        MakeRoot(x);
        if (FindRoot(y) == x) return false;
        f[x] = y;
        return true;
    }
    inline bool Cut(int x, int y) { // x,y 断边
        MakeRoot(x);
        if (FindRoot(y) == x && f[y] == x && !ch[y][0]) {
            f[y] = ch[x][1] = 0; PushUp(x);
            return true;
        }
        return false;
    }
}
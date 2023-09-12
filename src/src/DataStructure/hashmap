typedef long long ll;
const int M = 19260817;
const int MAX_SIZE = 2000000;
struct Hash_map {
    struct data {
        int nxt;
        ll key, value; // (key,value)
    } e[MAX_SIZE];
    int head[M], size;
    inline int f(ll key) { return key % M; }
    ll &operator[](const ll &key) {
        int ky = f(key);
        for (int i = head[ky]; i != -1; i = e[i].nxt)
            if (e[i].key == key) return e[i].value;
        return e[++size] = data{head[ky], key, 0}, head[ky] = size, e[size].value;
    }
    void clear() {
        memset(head, -1, sizeof(head));
        size = 0;
    }
    Hash_map() {clear();}
};
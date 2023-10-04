// x=ai (mod mi)   gcd(m1,m2....mn)=1
ll CRT(int n, ll a[], ll m[]) {
    ll M = 1, x = 0;
    for (int i = 1; i <= n; i++) M *= m[i];
    for (int i = 1; i <= n; i++)
        x = (x + (M / m[i]) * inv(M / m[i], m[i]) % M * a[i] % M) % M;
    return x;
}
// x=ai (mod mi)
ll EXCRT(int n, ll a[], ll m[]) {
    for (int i = 2; i <= n; i++) {
        ll d = gcd(m[i - 1], m[i]), x, y;
        if ((a[i] - a[i - 1]) % d != 0) return -1; // 无解
        exgcd(m[i - 1] / d, m[i] / d, x, y);
        m[i] = m[i] / gcd(m[i], m[i - 1]) * m[i - 1];
        a[i] = (a[i - 1] + mul(mul((a[i] - a[i - 1]) / d, x, m[i]), m[i - 1], m[i])) % m[i];
        a[i] = (a[i] + m[i]) % m[i];
    }
    return a[n];
}
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (!b) {x = 1, y = 0; return a;}
    ll d = exgcd(b, a % b, x, y);
    swap(x, y); y -= a / b * x;
    return d;
}
ll inv(ll a, ll p) {
    ll iv, k;
    exgcd(a, p, iv, k);
    return (iv % p + p) % p;
}
struct lin {
    vec s, e; db k;
    lin(vec _s, vec _e): s(_s), e(_e), k(atan2((e - s).y, (e - s).x)) {}
    il vec operator()() const {return e - s;}
};
vec cross(const lin &l1, const lin &l2) {return l1.s + l1() * crs(l2.s - l1.s, l2()) / crs(l1(), l2());}
bool cmpl(lin a, lin b) { // 极角排序，极角相同靠左优先
    if (cmp(a.k, b.k) == 0) return sign(crs(b.e-a.s, a())) > 0;
    return cmp(a.k, b.k) < 0;
}
bool Onright(lin a, lin b, lin c) { // a,b 交点在 c 右边
    vec p = cross(a, b);
    return sign(crs(c(), p - c.s)) <= 0;
}

void Halfplane(vector<lin> Ls, vector<vec> &res) { // 半平面交
    res.clear();
    sort(Ls.begin(), Ls.end(), cmpl);
    deque<int> q;
    for (int i = 0; i < (int)Ls.size(); ++i) {
        if (i != 0 && cmp(Ls[i].k, Ls[i - 1].k) == 0) continue;
        while (q.size() >= 2 && Onright(Ls[q[q.size() - 2]], Ls[q.back()], Ls[i])) q.pop_back();
        while (q.size() >= 2 && Onright(Ls[q.front()], Ls[q[1]], Ls[i])) q.pop_front();
        q.push_back(i);
    }
    while (q.size() >= 2 && Onright(Ls[q[q.size() - 2]], Ls[q.back()], Ls[q.front()])) q.pop_back();
    while (q.size() >= 2 && Onright(Ls[q[0]], Ls[q[1]], Ls[q.back()])) q.pop_front();
    if (q.size() >= 2) res.push_back(cross(Ls[q.back()], Ls[q.front()]));
    while (q.size() >= 2) {
        res.push_back(cross(Ls[q[0]], Ls[q[1]]));
        q.pop_front();
    }
}
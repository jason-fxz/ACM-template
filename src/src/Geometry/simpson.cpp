db f(db x) { return x * x * x; }
// 辛普森公式  = (r - l) / 6 * (f(l) + f(r) + 4f((l + r) / 2))
db simpson(db l, db r) {
    db mid = (l + r) / 2.0;
    return (r - l) * (f(l) + f(r) + f(mid) * 4.0) / 6.0; }
db simpson(db l, db r, db eps, db ans, int step) {
    db mid = (l + r) / 2.0;
    db fl = simpson(l, mid), fr = simpson(mid, r);
    if (fabs(fl + fr - ans) <= 15.0 * eps && step < 0) return fl + fr + (fl + fr - ans) / 15.0;
    return simpson(l, mid, eps / 2.0, fl, step - 1) + simpson(mid, r, eps / 2.0, fr, step - 1); }
db calc(db l, db r, db eps) { return simpson(l, r, eps, simpson(l, r), 12); }
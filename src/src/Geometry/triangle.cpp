vec incenter(cp a, cp b, cp c) { // 内心
    db p = dis(a, b) + dis(b, c) + dis(c, a);
    return (a * dis(b, c) + b * dis(c, a) + c * dis(a, b)) / p; }
vec circumcenter(cp a, cp b, cp c) { // 外心
    vec p = b - a, q = c - a, s(dot(p, p) / 2, dot(q, q) / 2);
    db d = crs(p, q);
    return a + vec(crs(s, vec(p.y, q.y)), crs(vec(p.x, q.x), s)) / d; }
vec orthocenter(cp a, cp b, cp c) { // 垂心
    return a + b + c - circumcenter(a, b, c) * 2.0; }
vec fermat_point(cp a, cp b, cp c) { // 费马点
    if (a == b) return a;
    if (b == c) return b;
    if (c == a) return c;
    db ab = dis(a, b), bc = dis(b, c), ca = dis(c, a);
    db cosa = dot(b - a, c - a) / ab / ca;
    db cosb = dot(a - b, c - b) / ab / bc;
    db cosc = dot(b - c, a - c) / ca / bc;
    db sq3 = PI / 3.0; vec mid;
    if (sgn(cosa + 0.5) < 0) mid = a;
    else if (sgn(cosb + 0.5) < 0) mid = b;
    else if (sgn(cosc + 0.5) < 0) mid = c;
    else if (sgn(crs(b - a, c - a)) < 0)
        mid = line_intersect(line(a, b + (c - b).rot(sq3)), line(b, c + (a - c).rot(sq3)));
    else
        mid = line_intersect(line(a, c + (b - c).rot(sq3)), line(c, b + (a - b).rot(sq3)));
    return mid; } // minimize(|A-x|+|B-x|+|C-x|)
point incenter (const point &a, const point &b, const point &c) {
	double p = dis (a, b) + dis (b, c) + dis (c, a);
	return (a * dis (b, c) + b * dis (c, a) + c * dis (a, b)) / p; }
point circumcenter (const point &a, const point &b, const point &c) {
	point p = b - a, q = c - a, s (dot (p, p) / 2, dot (q, q) / 2);
	double d = det (p, q);
	return a + point (det (s, point (p.y, q.y)), det (point (p.x, q.x), s)) / d; }
point orthocenter (const point &a, const point &b, const point &c) {
	return a + b + c - circumcenter (a, b, c) * 2.0; }
point fermat_point (const point &a, const point &b, const point &c) {
	if (a == b) return a; if (b == c) return b;
	if (c == a) return c;
	double ab = dis (a, b), bc = dis (b, c), ca = dis (c, a);
	double cosa = dot (b - a, c - a) / ab / ca;
	double cosb = dot (a - b, c - b) / ab / bc;
	double cosc = dot (b - c, a - c) / ca / bc;
	double sq3 = PI / 3.0; point mid;
	if (sgn (cosa + 0.5) < 0) mid = a;
	else if (sgn (cosb + 0.5) < 0) mid = b;
	else if (sgn (cosc + 0.5) < 0) mid = c;
	else if (sgn (det (b - a, c - a)) < 0)
		mid = line_intersect (line (a, b + (c - b).rot (sq3)), line (b, c + (a - c).rot (sq3)));
	else
		mid = line_intersect (line (a, c + (b - c).rot (sq3)), line (c, b + (a - b).rot (sq3)));
	return mid; }
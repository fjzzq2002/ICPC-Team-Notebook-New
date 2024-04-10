/**
 * Author: wxh?
 * Description: Basics of 2D geometry
 */

#include <bits/stdc++.h>
using namespace std;
using ld = long double;
const ld PI = acos(-1);
const ld EPS = 1e-12;
int sgn(ld x) {
	if (x > EPS) return 1;
	if (x < -EPS) return -1;
	return 0;
}
struct point {
	ld x, y;
	point(ld x = 0, ld y = 0) : x(x), y(y) {}
	point operator+(const point& o) const {/*...*/}
	point operator-(const point& o) const {/*...*/}
	point operator*(const ld& o) const {/*...*/}
	point operator/(const ld& o) const {/*...*/}
	ld operator*(const point& o) const {
		return x * o.y - y * o.x;
	}
	ld operator^(const point& o) const {
		return x * o.x + y * o.y;
	}
	point rotate() const { return point(-y, x); }
	point unit() const {
		ld w = abs();
		return point(x / w, y / w);
	}
	int get() const {
		return sgn(y) == 1 || (sgn(y) == 0 && sgn(x) == -1);
	}
	ld abs() const { return sqrt(x * x + y * y); }
};
struct line {
	point p0, p1;
	line(point p0, point p1) : p0(p0), p1(p1) {}
	bool contain(point p) const {
		return sgn((p1 - p0) * (p - p0)) == 1;
	}
	line move(ld d) const {
		point delta = (p1 - p0).rotate().unit() * d;
		return line(p0 + delta, p1 + delta);
	}
};
struct pointID {
	point p;
	int id;
	pointID(point p, int id) : p(p), id(id) {}
	bool operator<(const pointID& o) const {
		return make_pair(p.x, p.y) < make_pair(o.p.x, o.p.y);
	}
};
bool compare_angle(point p0, point p1) {
	return p0.get() < p1.get() || (p0.get() == p1.get() && sgn(p0 * p1) > 0);
}
point line_intersection(point p0, point p1, point p2, point p3) {
	ld foo = (p0 - p2) * (p3 - p2);
	ld bar = (p3 - p2) * (p1 - p2);
	return (p0 * bar + p1 * foo) / (foo + bar);
}
point line_intersection(line l0, line l1) {
	return line_intersection(l0.p0, l0.p1, l1.p0, l1.p1);
}
bool parallel(line l0, line l1) {
	return sgn((l0.p1 - l0.p0) * (l1.p1 - l1.p0)) == 0;
}
bool same_direction(line l0, line l1) {
	return parallel(l0, l1) && sgn((l0.p1 - l0.p0) ^ (l1.p1 - l1.p0)) == 1;
}
bool operator<(const line& l0, const line& l1) {
	if (same_direction(l0, l1))
		return l1.contain(l0.p0);
	else
		return compare_angle(l0.p1 - l0.p0, l1.p1 - l1.p0);
}
bool check(line l0, line l1, line l2) {
	return l2.contain(line_intersection(l0, l1));
}
vector<line> halfplane_intersection(vector<line> l) {
	sort(l.begin(), l.end());
	deque<line> q;
	for (int i = 0; i < (int) l.size(); ++i) {
		if (i && same_direction(l[i], l[i - 1]))
			continue;
		while ((int) q.size() > 1 && !check(q[q.size() - 2], q[q.size() - 1], l[i]))
			q.pop_back();
		while ((int) q.size() > 1 && !check(q[1], q[0], l[i]))
			q.pop_front();
		q.push_back(l[i]);
	}
	while ((int) q.size() > 2 && !check(q[q.size() - 2], q[q.size() - 1], q[0]))
		q.pop_back();
	while ((int) q.size() > 2 && !check(q[1], q[0], q[q.size() - 1]))
		q.pop_front();
	if ((int) q.size() == 2) return vector<line>();
	vector<line> res;
	for (int i = 0; i < (int) q.size(); ++i)
		res.push_back(q[i]);
	return res;
}
vector<pointID> convex_hull(vector<pointID> pts) {
	sort(pts.begin(), pts.end());
	if(pts.size()<=1) return pts;
	vector<pointID> ch;
	for (int rot = 0; rot < 2; ++rot) {
		int lim = ch.size();
		for (pointID p : pts) {
			while ((int) ch.size() > lim + 1 && (ch[ch.size() - 1].p - ch[ch.size() - 2].p) * (p.p - ch[ch.size() - 2].p) <= 0)
				ch.pop_back();
			ch.push_back(p);
		}
		ch.pop_back();
		reverse(pts.begin(), pts.end());
	}
	return ch;
}

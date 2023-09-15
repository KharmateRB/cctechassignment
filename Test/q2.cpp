#include <iostream>
#include <vector>
#include <algorithm>
struct Point {
int x, y;
};
// Cross product of two vectors.
int cross(const Point& O, const
Point& A, const Point& B) {
return (A.x - O.x) * (B.y - O.y) -
(A.y - O.y) * (B.x - O.x);
}
// Compute the convex hull of a
//set of points.
std::vector<Point>
convexHull(std::vector<Point>&
points) {
int n = points.size();
if (n <= 1)
return points;
std::sort(points.begin(),
points.end(), [](const Point& a,
const Point& b) {
return a.x < b.x || (a.x == b.x &&
a.y < b.y);
});
std::vector<Point> hull;
for (int i = 0; i < n; ++i) {
while (hull.size() >= 2 &&
cross(hull[hull.size() - 2],
hull.back(), points[i]) <= 0)
hull.pop_back();
hull.push_back(points[i]);
}
int lower_hull_size = hull.size();
for (int i = n - 2; i >= 0; --i) {
while (hull.size() >
lower_hull_size &&
cross(hull[hull.size() - 2],
hull.back(), points[i]) <= 0)
hull.pop_back();
hull.push_back(points[i]);
}
hull.pop_back(); // The last point is a duplicate of the first point in
//the hull.

return hull;
}
// Calculate the area of the convex polygon.

double calculateArea(const
std::vector<Point>& polygon) {
int n = polygon.size();
double area = 0.0;
for (int i = 0; i < n; ++i) {
int x1 = polygon[i].x;
int y1 = polygon[i].y;
int x2 = polygon[(i + 1) % n].x;
int y2 = polygon[(i + 1) % n].y;
area += (x1 * y2 - x2 * y1);
}
return std::abs(area) / 2.0;
}
int main() {
std::vector<Point> points = {
{0, 0},
{1, 2},
{2, 4},
{3, 1},
{4, 3},
{5, 5}
};
std::vector<Point>
convexPolygon =
convexHull(points);
double largestArea =
calculateArea(convexPolygon);
std::cout << "Largest area of the shape formed by the points: " <<
largestArea << std::endl;
return 0;
}

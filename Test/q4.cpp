#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    int x, y;
};

// Cross product of two vectors.
int cross(const Point& O, const Point& A, const Point& B) {
    return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

// Function to compute the convex hull of a set of points
std::vector<Point> convexHull(std::vector<Point>& points) {
    // Sort points lexicographically by x and y coordinates
    std::sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    int n = points.size();
    std::vector<Point> hull;

    // Build the lower hull
    for (int i = 0; i < n; ++i) {
        while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // Build the upper hull (excluding the last point, which is on the lower hull)
    int upperHullStart = hull.size();
    for (int i = n - 2; i >= 0; --i) {
        while (hull.size() > upperHullStart && cross(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) <= 0) {
            hull.pop_back();
        }
        hull.push_back(points[i]);
    }

    // The last point is the same as the first point, remove it
    hull.pop_back();

    return hull;
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

    std::vector<Point> convexPolygon = convexHull(points);

    std::cout << "Convex Hull Points:" << std::endl;
    for (const Point& p : convexPolygon) {
        std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
    }

    return 0;
}
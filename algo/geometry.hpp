#include <cmath>
#include <vector>

namespace algo {

typedef long double ld;

template <typename T>
constexpr inline int sign(const T& x) {
    return (x < 0 ? -1 : (x > 0 ? 1 : 0));
}

template <typename T>
struct Vec2 {
    T x, y;
    
    constexpr inline T mag2() const {return x * x + y * y;}
    constexpr inline ld mag() const {return std::sqrt(this->mag2());}
};

template <typename T>
constexpr inline Vec2<T> operator-(const Vec2<T>& v) {
    return Vec2<T>{-v.x, -v.y};
}

template <typename T>
constexpr inline Vec2<T> operator+(const Vec2<T>& u, const Vec2<T>& v) {
    return Vec2<T>{u.x + v.x, u.y + v.y};
}

template <typename T>
constexpr inline Vec2<T> operator-(const Vec2<T>& u, const Vec2<T>& v) {
    return Vec2<T>{u.x - v.x, u.y - v.y};
}

template <typename T>
constexpr inline T dot(const Vec2<T>& u, const Vec2<T>& v) {
    return u.x * v.x + u.y * v.y;
}

template <typename T>
constexpr inline T cross(const Vec2<T>& u, const Vec2<T>& v) {
    return u.x * v.y - v.x * u.y;
}

template <typename T, typename U>
constexpr bool intersect(const T&, const U&) {  
    return false;
}

template <typename T, typename U, typename V>
constexpr Vec2<V> intersection(const T&, const U&) {  
    return {};
}

template <typename T>
struct Segment {
    Vec2<T> start, end;
};

template <typename T>
struct Line {
    T a, b, c;
};

template <typename T>
inline bool bounding_box_check(T a, T b, T c, T d) {
    if (a > b) std::swap(a, b);
    if (c > d) std::swap(c, d);
    return std::max(a, c) <= std::min(b, d);
}

template <typename T>
constexpr bool intersect(const Segment<T>& u, const Segment<T>& v) {  
    auto dirU = u.end - u.start;
    auto dirV = v.end - v.start;
    return bounding_box_check(u.start.x, u.end.x, v.start.x, v.end.x)
            && bounding_box_check(u.start.y, u.end.y, v.start.y, v.end.y)
            && sign(cross(v.start - u.start, dirU)) * sign(cross(v.end - u.start, dirU)) <= 0
            && sign(cross(u.start - v.start, dirV)) * sign(cross(u.end - v.start, dirV)) <= 0;
}

template <typename T>
constexpr Vec2<ld> intersection(const Line<T>& l1, const Line<T>& l2) {
    auto k = l1.a * l2.b - l2.a * l1.b; 
    auto x = l1.b * l2.c - l2.b * l1.c;
    auto y = - l1.a * l2.c + l2.a * l1.c;
    return {(ld)x / k, (ld)y / k};
}

template <typename T>
class Polygon {
public:
    Polygon() = default;
    Polygon(const std::vector<Vec2<T>>& _points) : points(_points) {
        if (cross(points[1] - points[0], points[2] - points[0]) < 0) {
            reverse(points.begin(), points.end());
        }   
    }
    
    // inside = -1, on_border = 0, outside = 1
    constexpr int has_point(const Vec2<T>& point) {
        size_t n = points.size();
        auto dir = point - points[0];
        auto side1 = points[1] - points[0];
        auto side2 = points[n - 1] - points[0];
        int sgn1 = sign(cross(side1, dir)); 
        int sgn2 = sign(cross(side2, dir));
        if (sgn1 < 0 || sgn2 > 0) return 1;
        if (sgn1 == 0 && sgn2 == 0) sgn1 = dot(side1, dir) < 0;
        if (sgn1 == 0) return side1.mag2() < dir.mag2();
        if (sgn2 == 0) return side2.mag2() < dir.mag2();
        
        size_t l = 1, r = n - 1; 
        while (l + 1 < r) {
            size_t m = (l + r) >> 1;
            auto res = cross(points[m] - points[0], dir);
            if (res == 0) return sign(dir.mag2() - (points[m] - points[0]).mag2());
            if (res > 0) l = m;
            else r = m;
        }
        return sign(cross(point - points[l], points[r] - points[l]));
    }
        
    constexpr ld area() const {
        T res = cross(points[points.size() - 1], points[0]);
        for (size_t i = 1; i < points.size(); ++i) {
            res += cross(points[i - 1], points[i]); 
        }
        return std::abs(res) * 0.5;
    }

private:
    std::vector<Vec2<T>> points;
};

template <typename T>
Polygon<T> convexHull(std::vector<Vec2<T>> points) {
    sort(points.begin(), points.end());

    std::vector<Vec2<T>> hull;
    hull.reserve(points.size() + 1);

    for (int phase = 0; phase < 2; ++phase) {
        auto start = hull.size();
        for (auto& point : points) {
            while (hull.size() >= start+2 
                    && ccw(point, hull.back(), hull[hull.size()-2]) <= 0) {
                hull.pop_back();
            }
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(begin(points), end(points));
    }

    if (hull.size() == 2 && hull[0] == hull[1]) hull.pop_back();
    return Polygon<T>{hull};
}

}

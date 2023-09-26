#include<iostream>
#include<cmath>
#include<algorithm>
#include<ctime>
#include<cstdlib>
#include <iomanip>
#define M_PI acos(-1)

class Shape
{
public:
	virtual float area() const { return 0.0; } //虚函数
	virtual float volume() const { return 0.0; } //虚函数
	virtual void shapeName() const = 0; //纯虚函数
};
class Point : public Shape // Point是Shape的公用派生类
{
protected:
	float x, y;
public:
	Point(float = 0, float = 0);
	void setPoint(float, float);
	float getX() const { return x; }
	float getY() const { return y; }
	virtual void shapeName() const { std::cout << "Point:"; } // 对纯虚函数进行定义
	friend std::ostream& operator<<(std::ostream&, const Point&);
};
class Circle : public Point // 声明Circle类
{
protected:
	float radius;
	Point points;
public:
	Circle(float x = 0, float y = 0, float r = 0);
	Circle(Point point, float r);
	void setRadius(float);
	float getRadius() const;
	virtual float area() const;
	virtual void shapeName() const { std::cout << "Circle:"; } // 对纯虚函数进行再定义
	friend std::ostream& operator<<(std::ostream&, const Circle&);
};
class Triangle :public Point
{
protected:
	float x1, y1, x2, y2, x3, y3;
	Point point1, point2, point3;
public:
	Triangle(float x1, float y1, float x2, float y2, float x3, float y3);
	Triangle(Point point1, Point point2, Point point3);
	bool IsValid();
	float* getArrayX() { float answer[3] = { x1,x2,x3 }; return answer; }
	float* getArrayY() { float answer[3] = { y1,y2,y3 }; return answer; }
	virtual float area() const;
	virtual void shapeName() const { std::cout << "Triangle:"; } // 对纯虚函数进行再定义
	friend std::ostream& operator<<(std::ostream&, const Triangle&);
};


class Rectangle :public Point
{
protected:
	float x1, y1, x2, y2, x3, y3, x4, y4;
	Point point1, point2, point3, point4;
public:
	Rectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
	Rectangle(Point point1, Point point2, Point point3, Point point4);
	bool IsValid();
	float* getArrayX() { float answer[4] = { x1,x2,x3,x4 }; return answer; }
	float* getArrayY() { float answer[4] = { y1,y2,y3,y4 }; return answer; }
	virtual float area() const;
	virtual void shapeName() const { std::cout << "Rectangle:"; } // 对纯虚函数进行再定义
	friend std::ostream& operator<<(std::ostream&, const Rectangle&);
};



//定义 Point 类函数
void Point::setPoint(float a, float b)
{
	x = a; y = b;
}

Point::Point(float a, float b)
{
	x = a; y = b;
}

std::ostream& operator <<(std::ostream& output, const Point& p)
{
	output << "[" << p.x << "," << p.y << "]";
	return output;
}

//定义 Circle 类成员函数
Circle::Circle(float a, float b, float r) : Point(a, b), radius(r) {}
Circle::Circle(Point point, float r) {
	this->points = point; this->radius = r;
	this->x = point.getX(); this->y = point.getY();
}
//void Circle::setRadius(float r) : radius(r) {}
void Circle::setRadius(float r) { this->radius = r; }

float Circle::getRadius() const {
	return radius;
}
float Circle::area() const {
	return  M_PI * radius * radius;
}
std::ostream& operator <<(std::ostream& output, const Circle& c)
{
	output << "[" << c.x << "," << c.y << "],r=" << c.radius;
	return output;

}

//定义 Triangle 类成员函数
Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3) {
	this->x1 = x1; this->x2 = x2; this->x3 = x3; this->y1 = y1; this->y2 = y2; this->y3 = y3;
	point1.setPoint(x1, y1); point2.setPoint(x2, y2); point3.setPoint(x3, y3);
}
Triangle::Triangle(Point point1, Point point2, Point point3)
{
	this->point1 = point1; this->point2 = point2; this->point3 = point3;
	this->x1 = point1.getX(); this->y1 = point1.getY(); this->x2 = point2.getX(); this->y2 = point2.getY(); this->x3 = point3.getX(); this->y3 = point3.getY();
}
float Triangle::area()const {
	return 0.5 * abs(this->x1 * this->y2 + this->x2 * this->y3 + this->x3 * this->y1 - this->x1 * this->y3 - this->x2 * this->y1 - this->x3 * this->y2);
}
std::ostream& operator <<(std::ostream& output, const Triangle& tri)
{
	output << "[" << tri.x1 << "," << tri.y1 << "]" << " " << "[" << tri.x2 << "," << tri.y2 << "]" << " " << "[" << tri.x3 << "," << tri.y3 << "]";
	return output;
}
bool Triangle::IsValid()
{
	Triangle tri = *this;
	float x[3] = { 0 }; x[0] = tri.getArrayX()[0]; x[1] = tri.getArrayX()[1]; x[2] = tri.getArrayX()[2]; float y[3] = { 0 }; y[0] = tri.getArrayY()[0]; y[1] = tri.getArrayY()[1]; y[2] = tri.getArrayY()[2];
	float eps = 1e-6;
	float a = sqrt((x[0] - x[1]) * (x[0] - x[1]) + (y[0] - y[1]) * (y[0] - y[1]));
	float b = sqrt((x[1] - x[2]) * (x[1] - x[2]) + (y[1] - y[2]) * (y[1] - y[2]));
	float c = sqrt((x[0] - x[2]) * (x[0] - x[2]) + (y[0] - y[2]) * (y[0] - y[2]));
	if (a + b - c <= eps || a + c - b <= eps || b + c - a <= eps) { return false; }
	else { return true; }
}

//定义 Rectangle 类成员函数
Rectangle::Rectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
	this->x1 = x1; this->x2 = x2; this->x3 = x3; this->x4 = x4; this->y1 = y1; this->y2 = y2; this->y3 = y3; this->y4 = y4;
	point1.setPoint(x1, y1); point2.setPoint(x2, y2); point3.setPoint(x3, y3); point4.setPoint(x4, y4);
}
Rectangle::Rectangle(Point point1, Point point2, Point point3, Point point4) {
	this->point1 = point1; this->point2 = point2; this->point3 = point3; this->point4 = point4;
	this->x1 = point1.getX(); this->y1 = point1.getY(); this->x2 = point2.getX(); this->y2 = point2.getY(); this->x3 = point1.getX(); this->y3 = point3.getY(); this->x4 = point4.getX(); this->y4 = point4.getY();
};
float Rectangle::area()const {
	float s1 = 0.5 * abs(this->x1 * this->y2 + this->x2 * this->y3 + this->x3 * this->y1 - this->x1 * this->y3 - this->x2 * this->y1 - this->x3 * this->y2);
	float s2 = 0.5 * abs(this->x1 * this->y3 + this->x3 * this->y4 + this->x4 * this->y1 - this->x1 * this->y4 - this->x3 * this->y1 - this->x4 * this->y3);
	return s1 + s2;
}
std::ostream& operator <<(std::ostream& output, const Rectangle& rec)
{
	output << "[" << rec.x1 << "," << rec.y1 << "]" << " " << "[" << rec.x2 << "," << rec.y2 << "]" << " ""[" << rec.x3 << "," << rec.y3 << "]" << " " << "[" << rec.x4 << "," << rec.y4 << "]";
	return output;
}
bool Rectangle::IsValid() {
	Rectangle rec = *this;
	float x[4] = { 0 }; x[0] = rec.getArrayX()[0]; x[1] = rec.getArrayX()[1]; x[2] = rec.getArrayX()[2]; x[3] = rec.getArrayX()[3]; float y[4] = { 0 }; y[0] = rec.getArrayY()[0]; y[1] = rec.getArrayY()[1]; y[2] = rec.getArrayY()[2]; y[3] = rec.getArrayY()[3]; float eps = 1e-6; float x_c = 0.25 * (x[0] + x[1] + x[2] + x[3]); float y_c = 0.25 * (y[0] + y[1] + y[2] + y[3]);
	float a = sqrt((x_c - x[0]) * (x_c - x[0]) + (y_c - y[0]) * (y_c - y[0])); float b = sqrt((x_c - x[1]) * (x_c - x[1]) + (y_c - y[1]) * (y_c - y[1])); float c = sqrt((x_c - x[2]) * (x_c - x[2]) + (y_c - y[2]) * (y_c - y[2])); float d = sqrt((x_c - x[3]) * (x_c - x[3]) + (y_c - y[3]) * (y_c - y[3]));
	if (a - b <= eps && a - c <= eps && a - d <= eps && b - c <= eps && b - d <= eps && c - d <= eps) { return true; }
	else { return false; }
}


int main(void)
{
	Point point(3.2, 4.5);
	Point point1(2.4, 3.7);
	Point point2(5.1, 3.7);
	Point point3(2.4, 7.9);
	Point point4(5.1, 7.9);
	Point point_1(1.8, 4.2);
	Point point_2(4.6, 9.3);
	Point point_3(7.2, 5.6);
	float r = 5.6;
	Circle circle(2.4, 1.2, 5.6);
	Triangle triangle(1.8, 4.2, 4.6, 9.3, 7.2, 5.6);
	Rectangle rectangle(2.4, 3.7, 5.1, 3.7, 2.4, 7.9, 5.1, 7.9);
	////
	// 输入请用,隔开。
	// 示例:  1,1,1 +enter
	//        1,1,2,2,3,3,+enter
	//        1,1,2,1,1,7,2,7+enter
	////
	//float a = 0, b = 0;
	//std::cout << "请输入圆的圆心与半径[a,b],R=r:";
	//scanf_s("%f,%f,%f", &a, &b, &r);
	//point.setPoint(a, b);
	//Circle circle(point, r);
	//float x1 = 0, x2 = 0, x3 = 0, x4 = 0, y1 = 0, y2 = 0, y3 = 0, y4 = 0;
	//std::cout << "请输入三角形的三个点[x1,y1],[x2,y2],[x3,y3]:";
	//scanf_s("%f,%f,%f,%f,%f,%f", &x1, &y1, &x2, &y2, &x3, &y3);
	//point_1.setPoint(x1, y1); point_2.setPoint(x2, y2); point_3.setPoint(x3, y3);
	//Triangle triangle(point_1, point_2, point_3);
	//std::cout << "请输入矩形形的三个点[x1,y1],[x2,y2],[x3,y3],[x4,y4]:";
	//scanf_s("%f,%f,%f,%f,%f,%f,%f,%f", &x1, &y1, &x2, &y2, &x3, &y3, &x4, &y4);
	//point1.setPoint(x1, y1); point2.setPoint(x2, y2); point3.setPoint(x3, y3); point4.setPoint(x4, y4);
	//Rectangle rectangle(point1, point2, point3, point4);

	//point.shapeName();
	//std::cout << point << std::endl;

	circle.shapeName();
	std::cout << circle << std::endl;
	triangle.shapeName();
	std::cout << triangle << std::endl;
	rectangle.shapeName();
	std::cout << rectangle << std::endl;
	std::cout << "area:" << "\n";
	std::cout << "Circle:" << circle.area() << std::endl << "Triangle:" << triangle.area() << std::endl << "Rectangle:" << rectangle.area() << std::endl;

	int valid1 = 0, valid2 = 0;
	if (triangle.IsValid()) { std::cout << "三点能构成三角形" << std::endl; valid1 = 1; }
	else { std::cout << "三点构不成三角形" << std::endl; valid1 = 0; }
	if (rectangle.IsValid()) { std::cout << "三点能构成矩形" << std::endl; valid2 = 1; }
	else { std::cout << "三点构不成矩形" << std::endl; valid2 = 0; }
	/*
	float sumofarea = 0;
	Shape* pt = &point;
	sumofarea += pt->area();
	pt = &circle;
	sumofarea += pt->area();
	pt = &triangle;
	sumofarea += pt->area();
	pt = &rectangle;
	sumofarea += pt->area();
	std::cout << "Sum of Area: " << sumofarea << std::endl;
	*/

	if (valid1 == 0 || valid2 == 0) { return -1; }
	const int numShapes = 4;
	Shape* shapes[numShapes];
	shapes[0] = &point;
	shapes[1] = &circle;
	shapes[2] = &triangle;
	shapes[3] = &rectangle;
	float sumOfArea = 0;
	for (int i = 0; i < numShapes; i++) {
		sumOfArea += shapes[i]->area();
	}
	std::cout << "Sum of areas: " << sumOfArea << std::endl;
	return 0;
}



/*
Point 1: (1.8, 4.2)
Point 2: (4.6, 9.3)
Point 3: (7.2, 5.6)

Point 1: (2.4, 3.7)
Point 2: (5.1, 3.7)
Point 3: (5.1, 7.9)
Point 4: (2.4, 7.9)
*/
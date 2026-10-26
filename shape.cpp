/* Shape Area and Perimeter Calculator
   OOPS concepts: Inheritance, Virtual functions, Function overriding,
   Runtime polymorphism, Classes and objects, Constructors, Encapsulation */

#include <iostream>
#include <cmath>
using namespace std;

const double PI = 3.14159265;

/* Base class (abstract): common interface for all shapes */
class Shape {
public:
    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual const char *getName() = 0;

    void display()
    {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << "Shape     : " << getName() << endl;
        cout << "Area      : " << area() << endl;
        cout << "Perimeter : " << perimeter() << endl;
    }

    virtual ~Shape() {}
};

/* Derived class 1 */
class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) { radius = r; }
    double area() { return PI * radius * radius; }
    double perimeter() { return 2 * PI * radius; }
    const char *getName() { return "Circle"; }
};

/* Derived class 2 */
class Rectangle : public Shape {
private:
    double length, width;
public:
    Rectangle(double l, double w) { length = l; width = w; }
    double area() { return length * width; }
    double perimeter() { return 2 * (length + width); }
    const char *getName() { return "Rectangle"; }
};

/* Derived class 3 */
class Triangle : public Shape {
private:
    double a, b, c;
public:
    Triangle(double x, double y, double z) { a = x; b = y; c = z; }
    double area()                       /* Heron's formula */
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }
    double perimeter() { return a + b + c; }
    const char *getName() { return "Triangle"; }
};

/* Input validation: keeps asking until a positive number is entered */
double readPositive(const char *msg)
{
    double v;
    while (1) {
        cout << msg;
        if (cin >> v && v > 0) {
            cin.ignore(1000, '\n');
            return v;
        }
        cout << "Invalid input. Enter a number greater than 0.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

int validTriangle(double a, double b, double c)
{
    return (a + b > c && a + c > b && b + c > a);
}

/* Each function returns a base-class pointer (runtime polymorphism) */
Shape *inputCircle()
{
    double r = readPositive("Enter radius: ");
    return new Circle(r);
}

Shape *inputRectangle()
{
    double l = readPositive("Enter length: ");
    double w = readPositive("Enter width : ");
    return new Rectangle(l, w);
}

Shape *inputTriangle()
{
    double a, b, c;
    do {
        a = readPositive("Enter side 1: ");
        b = readPositive("Enter side 2: ");
        c = readPositive("Enter side 3: ");
        if (!validTriangle(a, b, c))
            cout << "Invalid triangle: sum of any two sides must be greater than the third.\n";
    } while (!validTriangle(a, b, c));
    return new Triangle(a, b, c);
}

int main()
{
    Shape *s;
    Shape *arr[3];
    int choice, i;

    do {
        cout << "\n===== SHAPE CALCULATOR =====\n";
        cout << "1. Circle\n";
        cout << "2. Rectangle\n";
        cout << "3. Triangle\n";
        cout << "4. All three shapes (base-class pointer array)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            choice = -1;
        }
        cin.ignore(1000, '\n');

        switch (choice) {
        case 1:
            s = inputCircle();
            s->display();
            delete s;
            break;
        case 2:
            s = inputRectangle();
            s->display();
            delete s;
            break;
        case 3:
            s = inputTriangle();
            s->display();
            delete s;
            break;
        case 4:
            cout << "-- Circle --\n";
            arr[0] = inputCircle();
            cout << "-- Rectangle --\n";
            arr[1] = inputRectangle();
            cout << "-- Triangle --\n";
            arr[2] = inputTriangle();
            cout << endl;
            for (i = 0; i < 3; i++) {
                arr[i]->display();      /* same call, different behaviour */
                cout << endl;
                delete arr[i];
            }
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Enter 0 to 4.\n";
        }
    } while (choice != 0);

    return 0;
}

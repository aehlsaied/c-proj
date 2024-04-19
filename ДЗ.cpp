#include <cmath>

class Point {
public:
    virtual void draw() const = 0;
    virtual void erase() const = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void rotate(double angle) = 0;
};

class TwoDimensionalPoint : public Point {
private:
    int x, y;
public:
    TwoDimensionalPoint(int x, int y) : x(x), y(y) {}

    void draw() const override {
        std::cout << "Draw point at (" << x << ", " << y << ")" << std::endl;
    }

    void erase() const override {
        std::cout << "Erase point at (" << x << ", " << y << ")" << std::endl;
    }

    void move(int dx, int dy) override {
        x += dx;
        y += dy;
        std::cout << "Move point to (" << x << ", " << y << ")" << std::endl;
    }

    void rotate(double angle) override {
        double radian = angle * M_PI / 180;
        int newX = round(x * cos(radian) - y * sin(radian));
        int newY = round(x * sin(radian) + y * cos(radian));
        x = newX;
        y = newY;
        std::cout << "Rotate point to (" << x << ", " << y << ")" << std::endl;
    }
};


int main() {
    TwoDimensionalPoint p(1, 1);
    p.draw();
    p.move(2, 3);
    p.rotate(45);
    p.erase();

    return 0;
}


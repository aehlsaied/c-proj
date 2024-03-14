#include <iostream>

class vect {
public:
    int dim;
    double* b;
    int num;
    static int count;

    vect(int d) : dim(d), num(count++) {
        b = new double[dim];
        std::cout << "Создан вектор " << num << " размерности " << dim << std::endl;
    }

    vect(const vect& other) : dim(other.dim), num(count++) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = other.b[i];
        }
        std::cout << "Скопирован вектор " << other.num << " вектор " << num << std::endl;
    }

    ~vect() {
        delete[] b;
        std::cout << "Уничтожен вектор " << num << std::endl;
    }

    friend vect operator+(const vect& v1, const vect& v2);
    friend vect operator*(double k, const vect& v);
    vect& operator=(const vect& other);
    friend std::ostream& operator<<(std::ostream& os, const vect& v);

};

int vect::count = 0;

vect operator+(const vect& v1, const vect& v2) {
    vect result(v1.dim);
    for (int i = 0; i < v1.dim; i++) {
        result.b[i] = v1.b[i] + v2.b[i];
    }
    std::cout << "Выполнено сложение векторов " << v1.num << " и " << v2.num << " вектор " << result.num << std::endl;
    return result;
}

vect operator*(double k, const vect& v) {
    vect result(v.dim);
    for (int i = 0; i < v.dim; i++) {
        result.b[i] = k * v.b[i];
    }
    std::cout << "Выполнено умножение вектора " << v.num << " на скаляр " << k << " вектор " << result.num << std::endl;
    return result;
}

vect& vect::operator=(const vect& other) {
    if (this != &other) {
        delete[] b;
        dim = other.dim;
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = other.b[i];
        }
    }
    std::cout << "Выполнено присваивание вектору " << other.num << " вектор " << num << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const vect& v) {
    os << "Вектор " << v.num << " (" << v.dim << "-мерный): ";
    for (int i = 0; i < v.dim; i++) {
        os << v.b[i] << " ";
    }
    return os;
}

class matr {
public:
    int dim;
    double* a;
    int num;
    static int count;

    matr(int d) : dim(d), num(count++) {
        a = new double[dim * dim];
        std::cout << "Создана матрица " << num << " размерности " << dim << "x" << dim << std::endl;
    }

    matr(const matr& other) : dim(other.dim), num(count++) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = other.a[i];
        }
        std::cout << "Скопирована матрица " << other.num << " в матрицу " << num << std::endl;
    }

    ~matr() {
        delete[] a;
        std::cout << "Уничтожена матрица " << num << std::endl;
    }

    friend matr operator+(const matr& m1, const matr& m2);
    friend matr operator*(const matr& m1, const matr& m2);
    matr& operator=(const matr& other);
    friend std::ostream& operator<<(std::ostream& os, const matr& m);
};

int matr::count = 0;

matr operator+(const matr& m1, const matr& m2) {
    matr result(m1.dim);
    for (int i = 0; i < m1.dim * m1.dim; i++) {
        result.a[i] = m1.a[i] + m2.a[i];
    }
    std::cout << "Выполнено сложение матриц " << m1.num << " и " << m2.num << " матрица " << result.num << std::endl;
    return result;
}

matr operator*(const matr& m1, const matr& m2) {
    matr result(m1.dim);
    for (int i = 0; i < m1.dim; i++) {
        for (int j = 0; j < m1.dim; j++) {
            result.a[i * m1.dim + j] = 0;
            for (int k = 0; k < m1.dim; k++) {
                result.a[i * m1.dim + j] += m1.a[i * m1.dim + k] * m2.a[k * m1.dim + j];
            }
        }
    }
    std::cout << "Выполнено умножение матрицы " << m1.num << " на матрицу " << m2.num << " матрица " << result.num << std::endl;
    return result;
}

matr& matr::operator=(const matr& other) {
    if (this != &other) {
        delete[] a;
        dim = other.dim;
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = other.a[i];
        }
    }
    std::cout << "Выполнено присваивание матрице " << other.num << " матрица " << num << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const matr& m) {
    os << "Матрица " << m.num << " (" << m.dim << "x" << m.dim << "): " << std::endl;
    for (int i = 0; i < m.dim; i++) {
        for (int j = 0; j < m.dim; j++) {
            os << m.a[i * m.dim + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

int main() {
    vect v1(3);
    v1.b[0] = 1.0;
    v1.b[1] = 2.0;
    v1.b[2] = 3.0;

    vect v2(v1);

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    vect v3 = v1 + v2;
    std::cout << v3 << std::endl;

    matr m1(2);
    m1.a[0] = 1.0; m1.a[1] = 2.0;
    m1.a[2] = 3.0; m1.a[3] = 4.0;

    matr m2(m1);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    matr m3 = m1 + m2;
    std::cout << m3 << std::endl;

    return 0;
}

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

struct Car {
    std::string licensePlate;
    std::string make;
    std::string model;
    int year;
    std::string owner;

    friend std::ostream& operator<<(std::ostream& os, const Car& car) {
        os << car.licensePlate << " " << car.make << " " << car.model << " "
           << car.year << " " << car.owner;
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Car& car) {
        is >> car.licensePlate >> car.make >> car.model >> car.year >> car.owner;
        return is;
    }

    std::string toString() const {
        std::ostringstream oss;
        oss << "License Plate: " << licensePlate << ", Make: " << make
            << ", Model: " << model << ", Year: " << year
            << ", Owner: " << owner;
        return oss.str();
    }
};

class CarRegistry {
private:
    std::vector<Car> cars;
    std::string filename;

public:
    CarRegistry(const std::string& file) : filename(file) {
        loadFromFile();
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        Car car;
        while (file >> car) {
            cars.push_back(car);
        }
    }

    void saveToFile() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        for (const auto& car : cars) {
            file << car << "\n";
        }
    }

    void addCar(const Car& car) {
        cars.push_back(car);
    }

    bool editCar(const std::string& licensePlate, const Car& updatedCar) {
        for (auto& car : cars) {
            if (car.licensePlate == licensePlate) {
                car = updatedCar;
                return true;
            }
        }
        return false;
    }

    bool deleteCar(const std::string& licensePlate) {
        for (auto it = cars.begin(); it != cars.end(); ++it) {
            if (it->licensePlate == licensePlate) {
                cars.erase(it);
                return true;
            }
        }
        return false;
    }

    void searchCar(const std::string& licensePlate) const {
        for (const auto& car : cars) {
            if (car.licensePlate == licensePlate) {
                std::cout << car.toString() << std::endl;
                return;
            }
        }
        std::cout << "Car with license plate " << licensePlate << " not found." << std::endl;
    }

    void listAllCars() const {
        for (const auto& car : cars) {
            std::cout << car.toString() << std::endl;
        }
    }
};

void showMenu() {
    std::cout << "\nMenu:\n"
              << "1. Add car\n"
              << "2. Edit car\n"
              << "3. Delete car\n"
              << "4. Search car\n"
              << "5. List all cars\n"
              << "6. Exit\n";
}

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Car inputCar() {
    Car car;
    std::cout << "Enter license plate: ";
    std::cin >> car.licensePlate;
    std::cout << "Enter make: ";
    std::cin >> car.make;
    std::cout << "Enter model: ";
    std::cin >> car.model;
    std::cout << "Enter year: ";
    std::cin >> car.year;
    std::cout << "Enter owner: ";
    std::cin >> car.owner;
    clearInput();  // Clear the input buffer to avoid issues with further inputs
    return car;
}

int main() {
    CarRegistry registry("cars.txt");
    int choice;

    do {
        showMenu();
        std::cout << "Enter choice: ";
        std::cin >> choice;
        clearInput();  // Clear the input buffer

        switch (choice) {
            case 1: {
                Car car = inputCar();
                registry.addCar(car);
                break;
            }
            case 2: {
                std::string licensePlate;
                std::cout << "Enter license plate of the car to edit: ";
                std::cin >> licensePlate;
                clearInput();  // Clear the input buffer
                Car updatedCar = inputCar();
                updatedCar.licensePlate = licensePlate;  // Maintain the same license plate
                if (!registry.editCar(licensePlate, updatedCar)) {
                    std::cout << "Car not found." << std::endl;
                }
                break;
            }
            case 3: {
                std::string licensePlate;
                std::cout << "Enter license plate of the car to delete: ";
                std::cin >> licensePlate;
                clearInput();  // Clear the input buffer
                if (!registry.deleteCar(licensePlate)) {
                    std::cout << "Car not found." << std::endl;
                }
                break;
            }
            case 4: {
                std::string licensePlate;
                std::cout << "Enter license plate to search: ";
                std::cin >> licensePlate;
                clearInput();  // Clear the input buffer
                registry.searchCar(licensePlate);
                break;
            }
            case 5:
                registry.listAllCars();
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (choice != 6);

    registry.saveToFile();

    return 0;
}
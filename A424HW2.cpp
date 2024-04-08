#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <chrono>
#include <thread>


class Sensor {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~Sensor() {}

    
    virtual void gatherData() const = 0;

    
    virtual void processData() const = 0;
};

class AerospaceControlSystem {
private:
    std::vector<Sensor*> sensors;

public:
    // A new sensor appears...
    void addSensor(Sensor* sensor) {
        sensors.push_back(sensor);
    }

    // point the missile
    void monitorAndAdjust() {
        for (Sensor* sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
            std::cout << "Adjusting controls based on sensor data." << std::endl;
        }
    }
};
// fun little wiggly blade
class AoASensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Angle of Attack (AoA) Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Angle of Attack (AoA) Sensor." << std::endl;
    }
};
// just dont touch it
class FlightSpeedSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Flight Speed Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Flight Speed Sensor." << std::endl;
    }
};
//in radar altimiters we trust
class AltitudeSensor : public Sensor {
public:
    void gatherData() const override {
        std::cout << "Gathering data from Altitude Sensor." << std::endl;
    }

    void processData() const override {
        std::cout << "Processing data from Altitude Sensor." << std::endl;
    }
};

int main() {
    AerospaceControlSystem ctrlSys;

    // factory time
    ctrlSys.addSensor(new AoASensor());
    ctrlSys.addSensor(new FlightSpeedSensor());
    ctrlSys.addSensor(new AltitudeSensor());

    // point the "aircraft" (its a missile)
    ctrlSys.monitorAndAdjust();

    return 0;

}

// part 2

// Define a structure for a Robot
struct Robot {
    int id;
};

// Define a structure for a Tool
struct Tool {
    char id;
};

// Function to simulate task execution by a robot
void executeTask(const Robot& robot1, const Tool& tool1, const Tool& tool2, const Robot& robot2) {
    // Simulate grabbing tools
    std::cout << "Robot " << robot1.id << " is grabbing tools " << tool1.id << " and " << tool2.id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Robot " << robot2.id << " is grabbing tools " << tool1.id << " and " << tool2.id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Simulate performing task
    std::cout << "Robots " << robot1.id << " and " << robot2.id << " are performing their task" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Simulate replacing tools
    std::cout << "Robot " << robot1.id << " is replacing tools " << tool1.id << " and " << tool2.id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Robot " << robot2.id << " is replacing tools " << tool1.id << " and " << tool2.id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
    // Define robots and tools
    Robot robots[5] = {{1}, {2}, {3}, {4}, {5}};
    Tool tools[5] = {{'A'}, {'B'}, {'C'}, {'D'}, {'E'}};

    // Execute tasks sequentially
    executeTask(robots[0], tools[0], tools[1], robots[2]); // Task 1: Robots 1 and 3
    executeTask(robots[1], tools[1], tools[2], robots[3]); // Task 2: Robots 2 and 4
    executeTask(robots[4], tools[4], tools[0], robots[0]); // Task 3: Robots 5 and 1

    return 0;
}

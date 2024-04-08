/ Define a structure for a Robot
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
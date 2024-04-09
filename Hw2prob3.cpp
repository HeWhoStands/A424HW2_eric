#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

using namespace std;

mutex mtx;
queue<int> ATC_queue;
queue<int> landing_queue;

void approachingPlanes() {
    // First vector [1, 2, 3]
    mtx.lock();
    ATC_queue.push(1);
    ATC_queue.push(2);
    ATC_queue.push(3);
    mtx.unlock();
    cout << "Approaching planes: 1, 2, 3" << endl;

    this_thread::sleep_for(chrono::seconds(1)); // Wait for 1 second
 // Second vector [4, 5, 6, 7]
    mtx.lock();
    ATC_queue.push(4);
    ATC_queue.push(5);
    ATC_queue.push(6);
    ATC_queue.push(7);
    mtx.unlock();
    cout << "Approaching planes: 4, 5, 6, 7" << endl;

    this_thread::sleep_for(chrono::seconds(1)); // Simulating time for planes to approach
   
    mtx.lock();
    ATC_queue.push(8);
    ATC_queue.push(9);
    ATC_queue.push(10);
    mtx.unlock();
    cout << "Approaching planes: 8, 9, 10" << endl;


}




void landingPlanes() {
    vector<int> diverted; // Store diverted planes

    while (true) {
        // Push planes from ATC queue to landing queue
        mtx.lock();
        while (!ATC_queue.empty() && landing_queue.size() < 3) {
            int planeToLand = ATC_queue.front();
            ATC_queue.pop();
            landing_queue.push(planeToLand);
            cout << "Plane " << planeToLand << "  queued for landing" << endl;
        }
        mtx.unlock();

        // Divert planes if landing queue is full
        mtx.lock();
        if (landing_queue.size() >= 3) {
            while (!ATC_queue.empty()) {
                int planeToDivert = ATC_queue.front();
                ATC_queue.pop();
                diverted.push_back(planeToDivert);
                cout << "Plane " << planeToDivert << " diverted and forgotten" << endl;
            }
        }
        mtx.unlock();

      
    }
}

void landingProcess() {
    while (true) {
        // Land the first plane in the landing queue
        mtx.lock();
        if (!landing_queue.empty()) {
            int planeToLand = landing_queue.front();
            landing_queue.pop();
            mtx.unlock();
            cout << "Landing plane " << planeToLand << endl;
        } else {
            mtx.unlock();
        }

        this_thread::sleep_for(chrono::seconds(1)); // Simulating time for landing
    }
}

int main() {
    thread t1(approachingPlanes);
    thread t2(landingPlanes);
    thread t3(landingProcess);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}

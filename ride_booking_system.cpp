#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class Vehicle 
{
public:
    virtual float calculateDistanceFare(float distance) = 0;
    virtual float calculateDurationFare(float distance) = 0;
    virtual int getBaseFare() = 0;
    virtual string getVehicleType() = 0;
};
// Derived class for Car
class Car : public Vehicle {
public:
    int getBaseFare() override {
        return 50;
    }
    string getVehicleType() override {
        return "Car";
    }
    float calculateDistanceFare(float distance) override {
        return 25 * distance;
    }
    float calculateDurationFare(float distance) override {
        return 2 * distance;
    }
};
// Derived class for Motorcycle
class Motorcycle : public Vehicle {
public:
    int getBaseFare() override {
        return 30;
    }
    string getVehicleType() override {
        return "Motorcycle";
    }
    float calculateDistanceFare(float distance) override {
        return 15 * distance;
    }
    float calculateDurationFare(float distance) override {
        return 2 * (distance / 70) * 60;
    }
};
// Derived class for Scooty
class Scooty : public Vehicle {
public:
    int getBaseFare() override {
        return 25;
    }
    string getVehicleType() override {
        return "Scooty";
    }
    float calculateDistanceFare(float distance) override {
        return 12 * distance;
    }
    float calculateDurationFare(float distance) override {
        return 2 * distance * 2.5;
    }
};
// Derived class for Auto
class Auto : public Vehicle {
public:
    int getBaseFare() override {
        return 20;
    }
    string getVehicleType() override {
        return "Auto";
    }
    float calculateDistanceFare(float distance) override {
        return 10 * distance;
    }
    float calculateDurationFare(float distance) override {
        return 1.5 * distance;
    }
};
// Ride class to manage ride details
class Ride {
private:
    Vehicle* vehicle;
    int rideType, promo, paymentMode;
    float distance, totalFare, promoFare, onlineDiscount, grandTotal;
    string dateTime;
public:
    static const int MAX_HISTORY = 100;  // Fixed array size for history
    static int rideCount;              // Count of rides stored
    struct RideHistory 
    {
        string vehicleType;
        string rideType;
        float distance;
        string dateTime;
    };
    static RideHistory rideHistory[MAX_HISTORY]; 
    void displayVehicleMenu() 
    {
        cout << "Available Vehicles:" << endl;
        if (rideType == 1) { 
            cout << "1. Car" << endl;
            cout << "2. Motorcycle" << endl;
            cout << "3. Scooty" << endl;
            cout << "4. Auto" << endl;
        } else { 
            if (distance > 5 && distance < 25) {
                cout << "1. Car" << endl;
                cout << "2. Motorcycle" << endl;
                cout << "3. Scooty" << endl;
            } else if (distance >= 25 && distance < 38) {
                cout << "1. Car" << endl;
                cout << "2. Motorcycle" << endl;
            } else if (distance >= 38 && distance < 50) {
                cout << "1. Car" << endl;
            } else {
                cout << "No shared vehicles available for the selected distance. Exiting..." << endl;
                exit(0);
            }
        }
    }
    void displayPromoMenu() 
    {
        cout << "\nAvailable Promo Codes:" << endl;
        cout << "1. Flat 50 Rupees discount" << endl;
        cout << "2. 20% discount" << endl;
        cout << "3. 25% discount but max 60 Rupees" << endl;
    }
    void displayPaymentMenu() 
    {
        cout << "\nPayment Modes:" << endl;
        cout << "1. Online payment" << endl;
        cout << "2. Offline payment" << endl;
    }
    void inputDetails() {
        cout << "\nRide Type:\n1. Private\n2. Shared\n";
        do {
            cout << "Choose [1 or 2]: ";
            cin >> rideType;
        } while (rideType < 1 || rideType > 2);
        cout << "Enter distance to travel (in kilometers): ";
        cin >> distance;
        if (rideType == 2 && (distance <= 5 || distance >= 50)) {
            cout << "No shared vehicles available for the selected distance. Exiting..." << endl;
            exit(0);
        }
        int vehicleChoice;
        displayVehicleMenu();
        do {
            cout << "Choose your vehicle: ";
            cin >> vehicleChoice;
        } while ((rideType == 1 && (vehicleChoice < 1 || vehicleChoice > 4)) || (rideType == 2 && (vehicleChoice < 1 || vehicleChoice > 3)));

        if (vehicleChoice == 1)
            vehicle = new Car();
        else if (vehicleChoice == 2)
            vehicle = new Motorcycle();
        else if (vehicleChoice == 3)
            vehicle = new Scooty();
        else if (rideType == 1 && vehicleChoice == 4)
            vehicle = new Auto();

        displayPromoMenu();
        do {
            cout << "Choose your promo [1-3]: ";
            cin >> promo;
        } while (promo < 1 || promo > 3);

        displayPaymentMenu();
        do {
            cout << "Choose payment mode [1 or 2]: ";
            cin >> paymentMode;
        } while (paymentMode < 1 || paymentMode > 2);
    }

    void calculateFare() {
        float baseFare = vehicle->getBaseFare();
        float distanceFare = vehicle->calculateDistanceFare(distance);
        float durationFare = vehicle->calculateDurationFare(distance);
        totalFare = baseFare + distanceFare + durationFare;
        if (rideType == 2) {
            totalFare *= 0.7;
        }
        switch (promo) {
        case 1:
            promoFare = 50;
            break;
        case 2:
            promoFare = totalFare * 0.2;
            break;
        case 3:
            promoFare = (totalFare * 0.25 < 60) ? totalFare * 0.25 : 60;
            break;
        }
        onlineDiscount = (paymentMode == 1) ? promoFare * 0.1 : 0;
        grandTotal = totalFare - promoFare - onlineDiscount;
        time_t now = time(0);
        char* dt = ctime(&now);
        dateTime = string(dt);
    }
    void displayBill() {
        cout << "\n----- Generated Bill -----" << endl;
        cout << "Vehicle Type: " << vehicle->getVehicleType() << endl;
        cout << "Ride Type: " << (rideType == 1 ? "Private" : "Shared") << endl;
        cout << "Base Fare: " << vehicle->getBaseFare() << " Rupees" << endl;
        cout << "Distance Fare: " << vehicle->calculateDistanceFare(distance) << " Rupees" << endl;
        cout << "Duration Fare: " << vehicle->calculateDurationFare(distance) << " Rupees" << endl;
        if (rideType == 2) {
            cout << "Shared Ride Discount: 30% Applied" << endl;
        }
        cout << "Total Fare: " << totalFare << " Rupees" << endl;
        cout << "Promo Discount: " << promoFare << " Rupees" << endl;
        cout << "Online Payment Discount: " << onlineDiscount << " Rupees" << endl;
        cout << "Grand Total: " << grandTotal << " Rupees" << endl;
        if (rideCount < MAX_HISTORY) {
            rideHistory[rideCount++] = {vehicle->getVehicleType(), rideType == 1 ? "Private" : "Shared", distance, dateTime};
        } else {
            cout << "Ride history storage is full. Cannot save this ride." << endl;
        }

        delete vehicle;
    }

    static void displayHistory() {
        if (rideCount == 0) {
            cout << "No previous rides found." << endl;
            return;
        }
        cout << "\n----- Ride History -----" << endl;
        for (int i = 0; i < rideCount; ++i) {
            cout << "Vehicle: " << rideHistory[i].vehicleType << endl;
            cout << "Ride Type: " << rideHistory[i].rideType << endl;
            cout << "Distance: " << rideHistory[i].distance << " km" << endl;
            cout << "Date & Time: " << rideHistory[i].dateTime << endl;
            cout << "------------------------" << endl;
        }
    }
};
Ride::RideHistory Ride::rideHistory[MAX_HISTORY];
int Ride::rideCount = 0;
class Customer 
{
private:
    string name, email;
    string phone;
    int reviewPoints;
    string writtenReview;
    bool isValidEmail(const string& email) {
        // Email must contain exactly one '@', at least one '.' after '@', and valid characters
        int atCount = 0;
        int dotAfterAt = 0;
        for (size_t i = 0; i < email.length(); i++) 
        {
            char c = email[i];
            if (c == '@') {
                atCount++;
                // Count dots after '@'
                for (size_t j = i + 1; j < email.length(); j++) {
                    if (email[j] == '.') dotAfterAt++;
                }
            }
        }
        return (atCount == 1 && dotAfterAt >= 1 && email.find('@') > 0 && email[email.length() - 1] != '.');
    }
    bool isValidPhone(const string& phone) {
        // Check length and ensure all characters are digits
        if (phone.length() != 10) return false;
        for (char c : phone) {
            if (c < '0' || c > '9') return false;
        }
        return true;
    }
public:
    void signUp() 
    {
        cout << "Enter your Name: ";
        cin >> name;
        // Email validation
        do {
            cout << "Enter your Email: ";
            cin >> email;
            if (!isValidEmail(email)) {
                cout << "Invalid email format. Please try again." << endl;
            }
        } while (!isValidEmail(email));

        // Phone number validation
        do {
            cout << "Enter your Phone Number (10 digits): ";
            cin >> phone;
            if (!isValidPhone(phone)) {
                cout << "Invalid phone number. Please enter a 10-digit number." << endl;
            }
        } while (!isValidPhone(phone));

        reviewPoints = 0;
        writtenReview = "";
    }

    void provideReview() {
        cout << "\nProvide review in points (0-5): ";
        cin >> reviewPoints;

        if (reviewPoints <= 5) {
            cout << "Review Points: " << reviewPoints << "/5" << endl;
            cout << "Provide written review: ";
            cin.ignore(); // Handle newline character
            getline(cin, writtenReview);
            cout << "Written Review: " << writtenReview << endl;
        } else {
            cout << "Invalid input. Review should be between 0 and 5 points." << endl;
            provideReview(); // Recursive call for re-input
        }
    }

    void displayCustomerDetails() {
        cout << "\n----- Customer Details -----" << endl;
        cout << "Name: " << name << endl;
        cout << "Email: " << email << endl;
        cout << "Phone: " << phone << endl;
    }
};

int main() {
    cout << "***** Welcome to Chalo Ride-Booking & Sharing Service *****" << endl;
    // Customer signup
    Customer customer;
    customer.signUp();

    char continueBooking;
    do {
        // Ride booking
        Ride ride;
        ride.inputDetails();
        ride.calculateFare();
        ride.displayBill();
        // View ride history
        char historyChoice;
        cout << "\nWould you like to view your previous ride history? (y/n): ";
        cin >> historyChoice;
        if (historyChoice == 'y' || historyChoice == 'Y') {
            Ride::displayHistory();
        }

        // Customer review
        char reviewChoice;
        cout << "Do you want to provide a review for your ride? (y/n): ";
        cin >> reviewChoice;
        if (reviewChoice == 'y' || reviewChoice == 'Y') {
            customer.provideReview();
            customer.displayCustomerDetails();
        }
        
        // Check if the user wants to book another ride
        cout << "\nWould you like to book another ride? (y/n): ";
        cin >> continueBooking;
    } while (continueBooking == 'y' || continueBooking == 'Y');
    cout << "\nThank you for using Chalo Ride-Booking & Sharing Service. Have a great day!" << endl;
    return 0;
}

# Chalo-Ride-Booking-Sharing-System
This C++ code is for a ride-booking and ride-sharing application named Chalo Ride-Booking &amp; Sharing Service. It allows a customer to book rides using different types of vehicles, apply promo codes, choose a payment method, and see the final bill.

1. Vehicle Classes
Base class: Vehicle – This is an abstract class with pure virtual functions for fare calculation.
Derived classes:
Car, Motorcycle, Scooty, and Auto – Each has different fare calculation formulas based on distance and time.

2. Ride Class
Handles all ride-related functions like:
Inputting ride details:
Choose ride type: Private or Shared
Enter travel distance
Select a suitable vehicle based on ride type and distance
Apply a promo code (flat ₹50, 20%, or 25% up to ₹60)
Choose payment mode (Online or Offline)
Fare Calculation:
Adds base fare, distance fare, and time fare
Applies shared ride discount (30%)
Applies promo discount and online payment discount
Bill Display:
Shows a breakdown of all charges and discounts
Displays the total payable amount
Saves each ride in ride history
Ride History:
Maintains and displays a list of up to 100 past rides

3. Customer Class
Handles customer profile:
Takes name, email, and phone number with proper validation
Lets users give reviews (points out of 5 and written feedback)
Displays customer details with their review

4. main() Function
The main user interaction flow:
Customer signs up
Then enters a loop:
Books a ride
Sees the ride summary
Views previous ride history (if they want)
Gives a review (optional)
Can book another ride or exit



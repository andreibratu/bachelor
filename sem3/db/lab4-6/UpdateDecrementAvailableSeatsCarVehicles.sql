/* 
Do not count driver's seat as available 
to passengers for car vehicles
*/

UPDATE Vehicles
SET [NumberSeats] = [NumberSeats] - 1
WHERE VehicleType = 'car';
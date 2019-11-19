/* Find all non-car vehicles that have not been used for rides */

/* e, f */

SELECT Id, VehicleType
FROM Vehicles
WHERE VehicleType
  IN (SELECT VehicleType FROM Vehicles WHERE VehicleType != 'car')
  AND NOT EXISTS (SELECT * FROM Rides WHERE Vehicles.Id = Rides.VehicleId)

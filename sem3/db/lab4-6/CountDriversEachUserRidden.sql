/* Count with how many unique drivers each user has ridden */

SELECT Users.IdentityDocument, FirstName, LastName, COUNT(DISTINCT(Vehicles.UserId)) AS Drivers
FROM Users
JOIN UserRideBridge ON Users.IdentityDocument = UserRideBridge.UserId
JOIN Rides ON Rides.RideId = UserRideBridge.RideId
JOIN Vehicles ON Rides.VehicleId = Vehicles.Id
WHERE Vehicles.VehicleType = 'car'
GROUP BY Users.IdentityDocument, FirstName, LastName;
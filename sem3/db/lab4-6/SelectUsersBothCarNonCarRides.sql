/* Select users that rode with both cars and non-car vehicles */

/* b, d */ 

SELECT IdentityDocument, FirstName, LastName
FROM Users
JOIN UserRideBridge ON Users.IdentityDocument = UserRideBridge.UserId
JOIN (SELECT * FROM Vehicles WHERE Vehicles.UserId IS NULL) AS NonCarRides ON UserRideBridge.RideId = NonCarRides.Id
INTERSECT
SELECT IdentityDocument, FirstName, LastName
FROM Users
JOIN UserRideBridge ON Users.IdentityDocument = UserRideBridge.UserId
JOIN (SELECT * FROM Vehicles WHERE Vehicles.UserId IS NOT NULL) AS CarRides ON UserRideBridge.RideId = CarRides.Id

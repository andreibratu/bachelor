/* Select all drivers that have not registered a car yet */

/* c, e, i */

SELECT IdentityDocument, FirstName, LastName, VehicleCount FROM (
	SELECT Users.IdentityDocument, FirstName, LastName, COUNT(Vehicles.UserId) AS VehicleCount
	FROM Users
	FULL JOIN Vehicles ON Users.IdentityDocument = Vehicles.UserId
	WHERE Users.IsDriver = 1
	GROUP BY Users.IdentityDocument, IdentityDocument, FirstName, LastName) 
AS DriverVehicleCount
WHERE VehicleCount = 0

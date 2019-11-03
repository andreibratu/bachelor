/* Select all drivers that have not registered a car yet */

SELECT IdentityDocument, FirstName, LastName
FROM Users
WHERE IsDriver = 1 AND IdentityDocument != ANY (SELECT UserId FROM Vehicles);
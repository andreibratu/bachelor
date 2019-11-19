/* Select all drivers that have not registered a car yet */

/* c, e, i */

SELECT IdentityDocument, FirstName, LastName
FROM Users
WHERE IsDriver = 1
EXCEPT
SELECT IdentityDocument, FirstName, LastName
FROM Users
WHERE IdentityDocument = ANY (SELECT UserId FROM Vehicles);

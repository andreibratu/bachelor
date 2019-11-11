/* Select all drivers that have not registered a car yet */

/* c, e, i */

SELECT IdentityDocument, FirstName, LastName
FROM Users
WHERE IsDriver = 1
EXCEPT
SELECT IdentityDocument, FirstName, LastName
FROM Users
WHERE (
	SELECT COUNT(Vehicles.UserId)
	FROM Users
	FULL JOIN Vehicles ON Users.IdentityDocument = Vehicles.UserId
	WHERE Users.IdentityDocument = IdentityDocument
) = 0;

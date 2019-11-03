/* Find all users that have not used delivery service */

SELECT FirstName, LastName
FROM Users
WHERE Users.IdentityDocument NOT IN (
	SELECT UserId FROM UserDeliveryBridge
);
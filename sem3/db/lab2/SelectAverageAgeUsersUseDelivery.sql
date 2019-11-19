/* Find average age of users using delivery service */

/* f */

SELECT AVG(DATEDIFF(MONTH, Users.BirthDate, GETDATE()) / 12) AS AverageUserAge
FROM Users
WHERE EXISTS (SELECT * FROM UserDeliveryBridge WHERE Users.IdentityDocument = UserDeliveryBridge.UserId)

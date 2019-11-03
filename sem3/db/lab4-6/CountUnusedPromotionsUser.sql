/* Count how many unused promotions each user has */

SELECT FirstName, LastName, COUNT(*) AS UnusedPromotions
FROM Users INNER JOIN Promotions ON Users.IdentityDocument = Promotions.UserIdentityDocument
WHERE RideId IS NULL AND Promotions.ExpirationDate < GETDATE()
GROUP BY IdentityDocument, FirstName, LastName;

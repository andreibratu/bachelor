/*
List all users that have only received PERCENT type promotions.
*/

/* d */

SELECT FirstName, LastName
FROM Users JOIN Promotions ON Users.IdentityDocument = Promotions.UserIdentityDocument
WHERE Promotions.PromotionType = 'PER'
GROUP BY FirstName, LastName;

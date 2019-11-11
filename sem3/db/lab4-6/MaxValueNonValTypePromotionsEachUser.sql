/* Find maximum value of all non-value type promotions given to each user */
/* h */

SELECT Users.IdentityDocument, PromotionType, MAX(Promotions.Amount) AS MaxPromotionAmount FROM Users
JOIN Promotions ON Users.IdentityDocument = Promotions.UserIdentityDocument
GROUP BY Users.IdentityDocument, Promotions.PromotionType
HAVING PromotionType IN (SELECT PromotionType FROM Promotions WHERE PromotionType != 'VAL')
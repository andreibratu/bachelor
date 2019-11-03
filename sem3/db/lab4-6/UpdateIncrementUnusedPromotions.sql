/* Increase discount value for all unused and expired percent type promotions */

UPDATE Promotions
SET [Amount] = [Amount] + 5
WHERE PromotionType = 'PER' AND RideId IS NULL AND ExpirationDate < GETDATE();
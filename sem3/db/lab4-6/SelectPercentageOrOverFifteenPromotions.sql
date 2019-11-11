/*
Select all percentage off promotions
or those above 15 in promotional value
*/
/* a */
SELECT PromotionId, Amount, PromotionType, RideId
FROM Promotions
WHERE PromotionType = 'PER' OR Amount > 15;

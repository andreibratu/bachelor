/* Select restaurants that are either fast_food or close after 20 */

SELECT RestaurantName, RestaurantType, ClosingHour
FROM Restaurants
WHERE RestaurantType = 'fast_food'
UNION
SELECT RestaurantName, RestaurantType, ClosingHour
FROM Restaurants
WHERE CONVERT(int, ClosingHour) >= 20;
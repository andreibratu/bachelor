/* Select all restaurants that have menus available */

/* f */

SELECT RestaurantId, RestaurantName FROM Restaurants
WHERE EXISTS (SELECT * FROM Menus WHERE RestaurantId = Menus.RestaurantID)

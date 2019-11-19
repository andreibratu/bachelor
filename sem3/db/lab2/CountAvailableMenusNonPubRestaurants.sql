/* Calculate how many menus are avialable from non-pub type of Restaurants */
/* h */

SELECT RestaurantName, COUNT(MenuId) AS MenusAvailable from Restaurants
JOIN Menus ON Restaurants.RestaurantId = Menus.RestaurantID
GROUP BY RestaurantName, RestaurantType
HAVING RestaurantType NOT IN (SELECT RestaurantType FROM Restaurants WHERE RestaurantType = 'pub')
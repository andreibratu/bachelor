/* Find all restaurants that have no delivery request registered */

SELECT RestaurantName
FROM Deliveries
JOIN MenuDeliveryBridge ON Deliveries.DeliveryId = MenuDeliveryBridge.DeliveryId
RIGHT JOIN Menus ON Menus.MenuId = MenuDeliveryBridge.MenuId
JOIN Restaurants ON Menus.RestaurantID = Restaurants.RestaurantId
GROUP BY RestaurantName
HAVING COUNT(Deliveries.DeliveryId) = 0;
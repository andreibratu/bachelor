/* Count how many times each user has ordered a menu from delivery */
/* d */

SELECT IdentityDocument, MenuDeliveryBridge.MenuQuantity, Menus.MenuId
FROM Users
JOIN UserDeliveryBridge ON Users.IdentityDocument = UserDeliveryBridge.UserId
JOIN MenuDeliveryBridge ON UserDeliveryBridge.DeliveryId = MenuDeliveryBridge.DeliveryId
JOIN Menus ON Menus.MenuId = MenuDeliveryBridge.MenuId
/* Find all coffee delivery items that cost more than 8 */
/* g */
SELECT MenuContent 
FROM (SELECT * FROM Menus WHERE MenuContent LIKE '_%Coffee') As CoffeeMenus
WHERE Price >= 8

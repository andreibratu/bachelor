/* Find all coffee delivery items that cost more than 8 */

SELECT * FROM Menus
WHERE Price >= 8 AND MenuContent LIKE '_%Coffee';
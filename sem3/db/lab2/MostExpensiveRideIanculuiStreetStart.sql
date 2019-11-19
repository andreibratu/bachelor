/* Find most expensive ride that started from Iancului street */
/* i */

SELECT *
FROM (SELECT * FROM Rides WHERE StartAddress LIKE 'Iancului_%') AS IanculuiRides
WHERE Fare >= ALL(SELECT Fare FROM (SELECT * FROM Rides WHERE StartAddress LIKE 'Iancului_%') AS Aux);
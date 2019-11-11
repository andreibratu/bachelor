/* Count number of rides for each of the most spacious vehicles in the fleet rewrite */
/* i */

SELECT Vehicles.Id, COUNT(RideId) AS Rides
FROM Rides
JOIN Vehicles ON Vehicles.Id = Rides.RideId
WHERE NumberSeats = (SELECT MAX(NumberSeats) FROM Vehicles)
GROUP BY Vehicles.Id
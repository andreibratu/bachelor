/* Count number of rides for each of the most spacious vehicles in the fleet */
/* i */

SELECT Vehicles.Id, COUNT(RideId) AS Rides
FROM Rides
JOIN Vehicles ON Vehicles.Id = Rides.RideId
WHERE NumberSeats >= ALL(SELECT NumberSeats FROM Vehicles)
GROUP BY Vehicles.Id
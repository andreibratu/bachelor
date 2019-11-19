/* Delete all'buggy' rides that took too much to complete */

DELETE FROM Rides
WHERE DATEDIFF(HOUR, EndTime, StartTime) > 1;
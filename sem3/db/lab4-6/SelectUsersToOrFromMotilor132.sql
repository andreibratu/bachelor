/* Select all users that had rides to or from Motilor132 address */
/* i */

SELECT *
FROM Users
JOIN UserRideBridge ON Users.IdentityDocument = UserRideBridge.UserId
JOIN Rides ON UserRideBridge.RideId = Rides.RideId
WHERE Rides.RideId = ANY (SELECT RideId FROM Rides WHERE StartAddress = 'Motilor 132' OR EndAddress = 'Motilor 132');

CREATE TABLE Vehicles(
	VehicleId INT PRIMARY KEY,
	VehicleType VARCHAR(10) NOT NULL CHECK (VehicleType in ('car', 'scooter', 'bicyle')),
	NumberSeats INT NOT NULL CHECK (NumberSeats in (1, 2, 5)),
	UserId char(8) FOREIGN KEY REFERENCES Users(IdentityDocument) NOT NULL
);
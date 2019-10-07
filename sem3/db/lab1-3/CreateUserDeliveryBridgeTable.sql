CREATE TABLE UserDeliveryBridge(
	UserId CHAR(8) FOREIGN KEY REFERENCES Users(IdentityDocument) NOT NULL,
	RideId INT FOREIGN KEY REFERENCES Deliveries(DeliveryId) NOT NULL
);
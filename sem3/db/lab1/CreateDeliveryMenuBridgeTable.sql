CREATE TABLE MenuDeliveryBridge(
	DeliveryId INT FOREIGN KEY REFERENCES Deliveries(DeliveryId) NOT NULL,
	MenuId INT FOREIGN KEY REFERENCES Menus(MenuId) NOT NULL,
	PRIMARY KEY (DeliveryId, MenuId)
);
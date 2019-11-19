CREATE TABLE Promotions(
	PromotionId INT PRIMARY KEY,
	Amount FLOAT NOT NULL,
	PromotionType CHAR(3) NOT NULL CHECK(PromotionType in ('PER', 'VAL')),
	UserIdentityDocument CHAR(8) NOT NULL FOREIGN KEY REFERENCES Users(IdentityDocument)
);
CREATE OR ALTER VIEW TestView
AS
	SELECT Ta.a1, Ta.a2, Tb.b1, Tb.b2 FROM Ta
	INNER JOIN Tc ON Ta.aid = Tc.aid
	INNER JOIN Tb ON Tc.bid = Tb.bid
	WHERE Ta.a2 < 500 OR Tb.b2 > 26
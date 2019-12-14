CREATE OR ALTER VIEW TableABGroupView
AS
	SELECT TableA.foo, TableB.bar
	FROM TableA INNER JOIN TableABBridge ON TableA.id = TableABBridge.ida INNER JOIN Tableb ON TableABBridge.idb = TableB.id
	GROUP BY TableA.foo, TableB.bar


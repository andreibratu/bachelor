CREATE TABLE Producers(
	p_id INT PRIMARY KEY,
	first_name VARCHAR(200) NOT NULL,
	last_name VARCHAR(200) NOT NULL,
	nationality VARCHAR(200) NOT NULL,
	awards INT NOT NULL,
);

CREATE TABLE Categories(
	mc_id INT PRIMARY KEY,
	cat_name VARCHAR(200) NOT NULL,
	cat_descr VARCHAR(200) NOT NULL
);

CREATE TABLE Cinemas(
	c_id INT PRIMARY KEY,
	c_name VARCHAR(200) NOT NULL,
	location VARCHAR(200) NOT NULL,
	seats INT NOT NULL
);

CREATE TABLE Movies(
	m_id INT PRIMARY KEY,
	title VARCHAR(200) NOT NULL,
	p_id INT FOREIGN KEY REFERENCES Producers(p_id),
	mc_id INT FOREIGN KEY REFERENCES Categories(mc_id)
);

CREATE TABLE Schedule(
	m_id INT FOREIGN KEY REFERENCES Movies(m_id) ON DELETE CASCADE,
	c_id INT FOREIGN KEY REFERENCES Cinemas(c_id) ON DELETE CASCADE,
	PRIMARY KEY (m_id, c_id),
	start_time CHAR(4) NOT NULL, -- format 10AM, 04PM
	sold_tickets INT NOT NULL
);
CREATE TABLE tree (
  node_id INT NOT NULL PRIMARY KEY, 
  parent_id INT,
  FOREIGN KEY (parent_id) REFERENCES tree (node_id)
  ON DELETE SET NULL
);

CREATE TABLE geom_table (
	geom_id SERIAL NOT NULL PRIMARY KEY,
	node_id INT,
	LOD INT DEFAULT NULL,
	geom bytea DEFAULT NULL,
	FOREIGN KEY (node_id) REFERENCES tree(node_id)
	ON DELETE SET NULL
);

CREATE TABLE block_root (
	block_root_id INT NOT NULL PRIMARY KEY,
	node_id INT,
	depth INT,
	FOREIGN KEY (node_id) REFERENCES tree(node_id)
	ON DELETE SET NULL
);
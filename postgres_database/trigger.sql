CREATE OR REPLACE FUNCTION tree_insert_limit() RETURNS TRIGGER AS $$
BEGIN
    IF (SELECT COUNT(parent_id) FROM tree WHERE parent_id = NEW.parent_id) >= 8 THEN
      RAISE SQLSTATE '45000'
      USING MESSAGE = 
        'The number of descendant nodes in the tree has been exceeded';
     END IF;
RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER t_tree_insert_limit
BEFORE INSERT ON tree FOR EACH ROW EXECUTE PROCEDURE tree_insert_limit();
CREATE OR REPLACE FUNCTION tree_output(block_id integer)
RETURNS TABLE(node INT, parent INT, LOD_identifier INT, geometry bytea)
LANGUAGE plpgsql
AS $$
BEGIN

   RETURN QUERY WITH RECURSIVE r AS (
    SELECT T.node_id, T.parent_id, G.LOD, G.geom, 1 AS depth
    FROM tree T INNER JOIN geom_table G ON T.node_id = G.node_id
    WHERE T.node_id = (SELECT node_id FROM block_root WHERE block_root_id = block_id)

    UNION 

    SELECT T1.node_id, T1.parent_id, G.LOD, G.geom, r.depth + 1 AS depth
    FROM
        tree T1 INNER JOIN r R ON T1.parent_id = R.node_id INNER JOIN geom_table G ON T1.node_id = G.node_id
	)
    SELECT node_id, parent_id, LOD, geom
	FROM r WHERE depth <= (SELECT depth FROM block_root WHERE block_root_id = block_id);

END;
$$;
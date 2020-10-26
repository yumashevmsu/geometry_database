CREATE OR REPLACE PROCEDURE create_new_node(node integer, parent integer)
LANGUAGE plpgsql
AS $$
BEGIN

   INSERT INTO tree(node_id, parent_id) VALUES (node, parent);

END;
$$;

CREATE OR REPLACE PROCEDURE create_new_geometry(node integer, LOD_ integer, geom_ bytea)
LANGUAGE plpgsql
AS $$
BEGIN

   INSERT INTO geom_table(node_id, LOD, geom) VALUES (node, LOD_, geom_);

END;
$$;

CREATE OR REPLACE PROCEDURE create_new_block(block_id_ integer, node_ integer, depth_ integer)
LANGUAGE plpgsql
AS $$
BEGIN

   INSERT INTO block_root(block_root_id, node_id, depth) VALUES (block_id_, node_, depth_);

END;
$$;

CREATE OR REPLACE PROCEDURE delete_node(node integer)
LANGUAGE plpgsql
AS $$
BEGIN

   DELETE FROM tree WHERE node_id = node;

END;
$$;

CREATE OR REPLACE PROCEDURE delete_geometry(LOD_ integer)
LANGUAGE plpgsql
AS $$
BEGIN

   DELETE FROM geom_table WHERE LOD = LOD_;

END;
$$;

CREATE OR REPLACE PROCEDURE delete_block(block_id_ integer)
LANGUAGE plpgsql
AS $$
BEGIN

   DELETE FROM block_root WHERE block_root_id = block_id_;

END;
$$;


CREATE DATABASE IF NOT EXISTS ctf;
USE ctf;

create table if not exists ip_log
(
	uuid varchar(36) not null
		primary key,
	current_ip varchar(256) null,
	last_ip varchar(256) null
)
;

CREATE DATABASE IF NOT EXISTS F4l9_D4t4B45e;
USE F4l9_D4t4B45e;

create table if not exists F4l9_t4b1e
(
	F4l9_C01uMn varchar(256) null
)
;



INSERT INTO F4l9_t4b1e VALUES ('flag{G1zj1n_W4nt5_4_91r1_Fr1end}');

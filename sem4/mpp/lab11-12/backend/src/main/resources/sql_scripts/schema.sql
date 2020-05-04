drop table if exists RENTAL;
drop table if exists MOVIE;
drop table if exists CLIENT;

create table CLIENT (
                        id identity primary key,
                        name varchar(100) not null,
                        address varchar(100) not null
);

create table MOVIE (
                       id identity primary key,
                       title varchar(100) not null,
                       genre enum('comedy', 'action', 'thriller', 'documentary', 'horror') not null,
                       year int
);

create table RENTAL (
                        id identity primary key,
                        client_id bigint not null,
                        movie_id bigint not null,
                        start_date date not null,
                        end_date date,
                        foreign key (client_id) references client(id) on delete cascade,
                        foreign key (movie_id) references movie(id) on delete cascade
);

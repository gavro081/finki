select distinct a.artistic_name, a.nationality from author a
join book_promotion bp on a.author_id = bp.author_id
join publisher p on p.publisher_id = bp.publisher_id
where rating > 6 and p.name like 'New%';
order by rating

select * from author 
except 
select a.author_id, a.artistic_name, a.nationality from author a
join book_promotion bp on a.author_id = bp.author_id;

select * from author 
except 
select a.author_id, a.artistic_name, a.nationality from author a
join book_promotion bp on a.author_id = bp.author_id;

select a.author_id, artistic_name, nationality from author a
join publisher_promotion pp on a.author_id = pp.author_id
join publisher p on p.publisher_id = pp.publisher_id
where p.publisher_id in 
(select publisher_id from publisher except select publisher_id from publisher_sponsor);

select artistic_name as name, 'Author' as type from author a
join book_promotion bp on bp.author_id = a.author_id
where rating > 4
union
select name as name, 'Publisher' as type from publisher p
join publisher_promotion pp on pp.publisher_id = p.publisher_id
where start_date >= '2024-01-01' and end_date < '2025-01-01';

select hf.date, f.name from held_fair hf
join fair f on f.fair_id = hf.fair_id
join location l on l.location_id = f.location_id
where l.capacity < 500 and l.type = 'OUTDOOR'
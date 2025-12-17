-- 1.
select distinct a.author_id, a.artistic_name, count(*) as number_of_fairs 
from Author a 
join Book_Promotion bp
on bp.author_id = a.author_id and hf.date = bp.date
join Held_Fair hf
on hf.fair_id = bp.fair_id
where bp.rating < 6
group by a.author_id, a.artistic_name
having count(*) >= 2

-- 2.
select f.name as fiar_name, l.name as location_name, count(bp.book_title) as book_count
from Fair f
join Location l
on f.location_id = l.location_id
join Book_Promotion bp
on bp.fair_id = f.fair_id
where l.capacity > 1000
group by l.name, f.fair_id
order by book_count asc

-- 3.
select distinct bp.book_title 
from Book_Promotion bp
join Publisher p
on p.publisher_id = bp.publisher_id
join Publisher_Sponsor ps
on ps.publisher_id = p.publisher_id
group by bp.book_title, p.publisher_id
having count(ps.sponsor) > 3
order by bp.book_title asc;

-- 4.
select a.author_id, a.artistic_name
from Author a
join Publisher_Promotion pp
on pp.author_id = a.author_id
join Publisher_Sponsor ps 
on ps.publisher_id = pp.publisher_id
group by a.author_id, pp.publisher_id
having count(ps.sponsor) = (
    select max(sponsor_count)
    from (
        select count(sponsor) as sponsor_count
        from Publisher_Sponsor
        group by publisher_id
    )
)

-- 5.
select book_title 
from Book_Promotion bp
join Fair f
on f.fair_id = bp.fair_id
join Location l
on l.location_id = f.location_id
where 
l.type = 'INDOOR'
and l.capacity = (
    select max(capacity)
    from held_fair hf
    join fair f
    on f.fair_id = hf.fair_id
    join location l
    on l.location_id = f.location_id
    where l.type = 'INDOOR'
)
order by book_title asc

-- 6.
with help as (
    select 
    l.name as location_name, a.artistic_name as author_name,
    count(book_title) as number_of_books, avg(rating) as average_rating
    from location l
    join fair f on f.location_id = l.location_id
    join held_fair hf on hf.fair_id = f.fair_id
    join book_promotion bp on bp.fair_id = hf.fair_id and bp.date = hf.date 
    join author a on a.author_id = bp.author_id
    group by l.location_id, a.author_id
)

select * from help h1
where (
    select count(*)
    from help h2
    where h2.location_name = h1.location_name
    and h2.average_rating > h1.average_rating
) < 3
order by h1.location_name, h1.average_rating desc

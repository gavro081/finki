with winners as (
    select ime_trka as race, vozacki_broj as driver, count(*) as cnt from ucestvuva u
    where krajna_p = 1
    group by ime_trka, vozacki_broj
)
select race, driver from winners w where cnt = (
    select max(cnt) from winners w1 
    where w1.race = w.race 
);
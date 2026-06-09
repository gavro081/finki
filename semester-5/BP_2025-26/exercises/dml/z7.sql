with positive_tests as (
    select distinct l.id
    from lice l 
    join test t on t.id = l.id
    where t.rezultat = 'pozitiven' and t.datum like '2021-08%'
),
count_gt_2 as (
    select vd.id_lice
    from vakcinacija_datum vd
    group by vd.id_lice
    having count(*) >= 2
)
select 100.0 * (count(id) - count(id_lice)) / (count(id)) as procent 
from positive_tests p
left join count_gt_2 c on c.id_lice = p.id
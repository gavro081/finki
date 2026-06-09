with counts as (
    select count(*) as cnt
    from preporaka
    group by k_ime_od
)
select k_ime_na as k_ime, count(*) as dobieni_preporaki
from preporaka
where k_ime_na in (
    select k_ime_od
    from preporaka
    group by k_ime_od
    having count(*) = (select max(cnt) from counts)
)
group by k_ime_na;
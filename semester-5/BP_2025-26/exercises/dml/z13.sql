select
    f.ime,
    n.cena,
    n.kapacitet,
    count(distinct fo.datum_od) as broj_odrzuvanja,
    count(distinct fb.id_bend) as broj_bendovi
from festival f
join nastan n on n.id = f.id
left join festival_odrzuvanje fo on fo.id = f.id
left join festival_bend fb on fb.id_festival = f.id
group by f.id, f.ime, n.cena, n.kapacitet;
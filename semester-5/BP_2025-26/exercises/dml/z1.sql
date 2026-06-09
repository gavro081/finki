select distinct l.id
from lice l
join test t on t.id = l.id
join vakcinacija_datum vd on vd.id_lice = l.id
where t.rezultat = 'pozitiven' and vd.datum > t.datum
order by l.id;
select distinct m.ime, m.prezime
from muzicar m
join muzicar_instrument mi on mi.id_muzicar = m.id
join muzicar_bend mb on mb.id_muzicar = m.id
join koncert_muzicar_bend kmb on kmb.id_muzicar = m.id and kmb.id_bend = mb.id_bend
join koncert k on k.id = kmb.id_koncert
where mi.instrument = 'gitara' and k.datum > mb.datum_napustanje
order by m.ime;
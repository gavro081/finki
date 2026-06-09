select distinct v.vozacki_broj, v.ime, v.prezime, v.nacionalnost, v.datum_r 
from Ucestvuva u
join Trka t on u.ime_trka = t.ime
join Vozac v on v.vozacki_broj = u.vozacki_broj
where u.poeni >= 1 and t.krugovi < 70 and u.datum_trka like '2023%'
order by v.datum_r desc;
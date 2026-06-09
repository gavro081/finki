select distinct pk.k_ime, p.naslov
from premium_korisnik pk
join preporaka p on p.k_ime_na = pk.k_ime
join lista_zelbi lz on lz.k_ime = pk.k_ime and lz.naslov = p.naslov
where p.ocena > 3 and p.datum like '2021%'
order by pk.k_ime;
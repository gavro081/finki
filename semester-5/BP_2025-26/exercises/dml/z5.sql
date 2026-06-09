select distinct k.ime, k.prezime
from korisnik k
join premium_korisnik pk on pk.k_ime = k.k_ime
join preporaka p on p.k_ime_od = k.k_ime
join video_zapis vz on vz.naslov = p.naslov
where vz.vremetraenje > 120 and p.ocena >= 4
order by k.datum_reg;
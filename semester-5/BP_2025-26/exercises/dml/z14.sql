with avg_ocena as (
    select naslov, avg(ocena) as avg_ocena
    from preporaka
    group by naslov
)
select pr.ime, avg(ao.avg_ocena) as po_profil
from profil pr
join lista_zelbi lz on lz.k_ime = pr.k_ime and lz.ime = pr.ime
join avg_ocena ao on ao.naslov = lz.naslov
group by pr.k_ime, pr.ime;
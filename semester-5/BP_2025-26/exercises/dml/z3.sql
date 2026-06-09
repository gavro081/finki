select distinct k.ime, k.prezime
from korisnik k
join poseta p1 on p1.kor_ime = k.kor_ime
join poseta p2 on p2.kor_ime = k.kor_ime
join objekt o1 on o1.id_mesto = p1.id_mesto
join objekt o2 on o2.id_mesto = p2.id_mesto
join sosedi s on
    (s.grad1 = o1.id_grad and s.grad2 = o2.id_grad)
    or
    (s.grad1 = o2.id_grad and s.grad2 = o1.id_grad)
where p1.datum = p2.datum and p1.id_mesto <> p2.id_mesto
order by k.ime, k.prezime;
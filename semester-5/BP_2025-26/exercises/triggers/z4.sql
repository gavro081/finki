create trigger trg_grad_delete
after delete on Grad
for each row
begin
    update Sosedi
    set grad1 = NULL
    where grad1 = old.id_mesto;

    update Sosedi
    set grad2 = NULL
    where grad2 = old.id_mesto;
end;

create trigger trg_korisnik_delete
after delete on Korisnik
for each row
begin
    delete from Poseta
    where kor_ime = old.kor_ime;
end;
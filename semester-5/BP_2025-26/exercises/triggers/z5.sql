-- create trigger trg_broj_poseti
-- after insert on Poseta
-- for each row
-- when (
--     select count(*)
--     from Poseta p
--     where p.kor_ime = new.kor_ime
--       and p.id_mesto = new.id_mesto
-- ) = 1
-- begin
--     update Mesto
--     set broj_poseti = broj_poseti + 1
--     where id = new.id_mesto;
-- end;

create trigger trg_broj_poseti
after insert on Poseta
for each row
begin
    update Mesto
    set broj_poseti =
    (
        select count(distinct kor_ime)
        from Poseta p
        where p.id_mesto = new.id_mesto
    )
    where id = new.id_mesto;
end;
create trigger trg_prosechna_ocena
after insert on Preporaka
for each row
begin
    update Video_zapis
    set prosechna_ocena =
    (
        select avg(p.ocena)
        from Preporaka p
        where p.naslov = new.naslov
    )
    where naslov = new.naslov;
end;
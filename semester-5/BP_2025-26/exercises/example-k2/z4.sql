create trigger vozac_delete
before delete on Vozac
for each row
begin
    update Ucestvuva
    set vozacki_broj = null
    where vozacki_broj = old.vozacki_broj;
end;

create trigger tim_delete
before delete on Tim
for each row
begin
    delete from Ucestvuva
    where ime_tim = old.ime;
end;
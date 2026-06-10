create trigger trg_br_bendovi
after insert on Muzicar_bend
for each row
begin
    update Muzicar
    set br_bendovi = br_bendovi + 1
    where id = new.id_muzicar;
end;

-- create trigger trg_br_bendovi
-- after insert on Muzicar_bend
-- for each row
-- begin
--     update Muzicar
--     set br_bendovi =
--     (
--         select count(*)
--         from Muzicar_bend mb
--         where mb.id_muzicar = new.id_muzicar
--     )
--     where id = new.id_muzicar;
-- end;
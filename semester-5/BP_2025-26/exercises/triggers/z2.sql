create trigger trg_vakcinalen_status
after insert on Vakcinacija_datum
for each row
begin
    update lice
    set vakcinalen_status = 
    case 
        when
            (select count(*) from vakcinacija_datum vd where vd.id_lice = new.id_lice) = 1 
        then 'primena prva doza' 
        else 'primeni dve dozi'
    end
    where id = new.id_lice;
end;



-- create trigger trg_prva_doza
-- after insert on Vakcinacija_datum
-- for each row
-- when (
--     select count(*)
--     from Vakcinacija_datum vd
--     where vd.id_lice = new.id_lice
-- ) = 1
-- begin
--     update Lice
--     set vakcinalen_status = 'primena prva doza'
--     where id = new.id_lice;
-- end;

-- create trigger trg_vtora_doza
-- after insert on Vakcinacija_datum
-- for each row
-- when (
--     select count(*)
--     from Vakcinacija_datum vd
--     where vd.id_lice = new.id_lice
-- ) = 2
-- begin
--     update Lice
--     set vakcinalen_status = 'primeni dve dozi'
--     where id = new.id_lice;
-- end;
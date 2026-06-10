create trigger trg_celosno_imuniziran
after insert on Vakcinacija_datum
for each row
begin
    update Lice
    set celosno_imuniziran = 1
    where id = new.id_lice
      and (
            select count(*)
            from Vakcinacija_datum vd
            where vd.id_lice = new.id_lice
          ) >= 2;
end;
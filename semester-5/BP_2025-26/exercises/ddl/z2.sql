create table Test(
    id int,
    shifra text,
    tip text,
    datum text,
    rezultat text,
    laboratorija text,
    
    primary key(id, shifra),
    
    foreign key (id) references Lice(id)
        on update cascade on delete cascade,
        
    check(laboratorija <> 'lab-abc' or tip = 'seroloshki')
);

create table Vakcinacija (
    id_lice int,
    id_med_lice int,
    shifra_vakcina int,
    
    primary key(id_lice, id_med_lice, shifra_vakcina),
    
    foreign key (id_lice) references Lice(id)
        on update cascade on delete set default,
        
    foreign key (id_med_lice) references Med_lice(id)
        on update cascade on delete set default,
        
    foreign key (shifra_vakcina) references Vakcina(shifra)
        on update cascade on delete set default,
    
    check(id_lice != id_med_lice)
);

create table Vakcinacija_datum(
  id_lice int,
  id_med_lice int,
  shifra_vakcina int,
  datum text,
  
  primary key(id_lice, id_med_lice, shifra_vakcina, datum),
  
  foreign key(id_lice, id_med_lice, shifra_vakcina) 
    references Vakcinacija(id_lice, id_med_lice, shifra_vakcina)
    on update cascade
    on delete set null
);
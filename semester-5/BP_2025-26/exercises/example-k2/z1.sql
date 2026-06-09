create table Trka (
    ime text primary key,
    krugovi integer,
    pateka text,
    
    foreign key (pateka) references Pateka(ime)
        on update cascade on delete cascade,
        
    check (krugovi <= 80)
);

create table Odrzana_trka (
    ime text,
    datum text,
    vreme text,
    primary key (ime, datum),
    
    foreign key (ime) references Trka(ime)
        on update cascade on delete cascade
);

create table Ucestvuva (
    ID int primary key,
    vozacki_broj text,
    ime_tim text,
    ime_trka text,
    datum_trka text,
    pocetna_p integer,
    krajna_p integer,
    poeni float,
    
    foreign key (vozacki_broj) references Vozac(vozacki_broj)
        on update cascade on delete set null,
        
    foreign key (ime_tim) references Tim(ime)
        on update cascade on delete cascade,
        
    foreign key (ime_trka, datum_trka) references Odrzana_trka(ime, datum)
        on update cascade on delete cascade,
        
    check (krajna_p <= 10 or poeni = 0)
);
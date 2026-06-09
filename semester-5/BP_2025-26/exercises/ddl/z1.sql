create table Vraboten(
    ID text primary key,
    ime text,
    prezime text,
    datum_r text,
    datum_v text,
    obrazovanie text,
    plata int,
    
    check (datum_r < datum_v)
);

create table Shalterski_rabotnik(
    ID text primary key,
    
    foreign key (ID) references Vraboten(ID)
        on delete cascade on update cascade
);


create table Transakcija_shalter(
    ID text primary key,
    ID_v text,
    MBR_k text,
    MBR_k_s text,
    broj text,
    datum text,
    suma int,
    tip text,
    foreign key (ID_v) references Shalterski_rabotnik(ID)
        on update cascade on delete set null,
        
    foreign key (MBR_k) references Klient(MBR_k)
        on update cascade on delete cascade,
        
    foreign key (MBR_k_s, broj) references Smetka(MBR_k_s, broj)
        on update cascade on delete cascade,

    check (datum < '2020-12-30' or datum > '2021-01-14'),
    
    check (tip in ('isplata', 'uplata'))
)
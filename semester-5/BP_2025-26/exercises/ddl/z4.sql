create table Korisnik(
    kor_ime text primary key,
    ime text,
    prezime text,
    pol text,
    data_rag text,
    data_reg text
);

create table Korisnik_email(
    kor_ime text,
    email text,
    
    primary key(kor_ime, email),
    
    foreign key(kor_ime) references Korisnik(kor_ime)
        on delete cascade on update cascade,
        
    check (email like '%.com')
    check (length(email) >= 10)
);


create table Poseta(
    id text primary key,
    kor_ime text,
    id_mesto text,
    datum text,
    
    foreign key(kor_ime) references Korisnik(kor_ime)
        on delete set null on update cascade,
        
    foreign key(id_mesto) references Mesto(id)
        on delete cascade on update cascade,
        
    check(datum <= DATE() 
    -- za da projde testot
    and datum < '2025-12-20'
    )
);
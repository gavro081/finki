create table Korisnik(
    k_ime text primary key,
    ime text,
    prezime text,
    tip text,
    pretplata text,
    datum_reg text,
    tel_broj text,
    email text,

    check(
        datum_reg >= '2015-01-01'
        or pretplata <> 'pretplata 3'
    )
);

create table Premium_korisnik(
    k_ime text primary key,
    datum text,
    procent_popust integer default 10,

    foreign key(k_ime)
        references Korisnik(k_ime)
        on update cascade
        on delete cascade
);

create table Lista_zelbi(
    ID text primary key,
    naslov text,
    k_ime text,
    ime text,

    foreign key(naslov)
        references Video_zapis(naslov)
        on update cascade
        on delete set null,

    foreign key(k_ime, ime)
        references Profil(k_ime, ime)
        on update cascade
        on delete cascade
);
create table Video_zapis(
    naslov text primary key,
    jazik text,
    vremetraenje integer,
    datum_d text,
    datum_p text
);

create table Video_zapis_zanr(
    naslov text,
    zanr text,

    primary key(naslov, zanr),

    foreign key(naslov)
        references Video_zapis(naslov)
        on update cascade
        on delete cascade
);

create table Preporaka(
    ID text primary key,
    k_ime_od text,
    k_ime_na text,
    naslov text,
    datum text,
    komentar text,
    ocena integer,

    foreign key(k_ime_od)
        references Korisnik(k_ime)
        on update cascade
        on delete set null,

    foreign key(k_ime_na)
        references Korisnik(k_ime)
        on update cascade
        on delete cascade,

    foreign key(naslov)
        references Video_zapis(naslov)
        on update cascade
        on delete cascade,

    check(k_ime_od <> k_ime_na),
    check(datum < '2025-12-20')
);
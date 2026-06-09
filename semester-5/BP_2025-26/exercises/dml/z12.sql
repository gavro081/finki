with cte as (
select k.k_ime, vz.naslov, count(*) as broj from korisnik k
join preporaka p on p.k_ime_od=k.k_ime
join video_zapis vz on vz.naslov = p.naslov
group by k_ime, vz.naslov)

select k_ime, naslov, broj from cte t1
where not exists (select 1 from cte t2 where t1.k_ime == t2.k_ime and t1.broj < t2.broj);
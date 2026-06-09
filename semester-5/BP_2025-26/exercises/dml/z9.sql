select m.ime
from mesto m
where m.id = (
    select o.id_grad
    from poseta p
    join objekt o on o.id_mesto = p.id_mesto
    group by o.id_mesto, o.id_grad
    order by count(*) desc
    limit 1
);
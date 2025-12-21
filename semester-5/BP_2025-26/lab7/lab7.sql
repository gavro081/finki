-- 1.
create trigger on_removed_author
after delete on Author
for each row
begin
    delete from Book_Promotion
    where author_id=old.author_id;
end;


create trigger on_removed_author1
after delete on Publisher
for each row
begin
    update Book_Promotion
    set publisher_id=-1
    where publisher_id=old.publisher_id;
end;


-- 2.

create trigger on_delete
after delete on held_fair
for each row
begin
    delete from book_promotion
    where fair_id=old.fair_id and date=old.date;
end;

create trigger on_delete1
after delete on author
for each row
begin
    update book_promotion
    set author_id=-1
    where author_id=old.author_id;
end;


-- 3. 

create trigger on_add
after insert on book_promotion
for each row
begin
    update Author
    set num_fairs = num_fairs + 1
    where author_id = new.author_id;
end;


create trigger on_delete
after delete on book_promotion
for each row
begin
    update Author
    set num_fairs = num_fairs - 1
    where author_id = old.author_id;
end;

-- 4.

create trigger on_add
after insert on publisher_promotion
for each row
begin
    update Author
    set num_publishers = (
        select count(distinct publisher_id)
        from Publisher_Promotion
        where start_date like '2025%' and end_date like '2025%' and author_id=new.author_id
    )
    where author_id=new.author_id;
end;